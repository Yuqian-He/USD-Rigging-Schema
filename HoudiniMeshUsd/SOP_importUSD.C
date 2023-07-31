#include "SOP_importUSD.h"
#include "SOP_importUSD.proto.h"

#include <GU/GU_Detail.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <PRM/PRM_TemplateBuilder.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <UT/UT_StringHolder.h>
#include <SYS/SYS_Math.h>
#include <limits.h>
#include <PRM/PRM_SpareData.h>
#include <SOP/SOP_Node.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <cstdio>


using namespace my_importUSD;

const UT_StringHolder SOP_importUSD::theSOPTypeName("hdk_importUSD"_sh);

void newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator(
        SOP_importUSD::theSOPTypeName,   // Internal name
        "importUSD",                     // UI name
        SOP_importUSD::myConstructor,    // How to build the SOP
        SOP_importUSD::buildTemplates(),// My parameters
        0,                          // Min # of sources
        0,                          // Max # of sources
        nullptr,                    // Custom local variables (none)
        OP_FLAG_GENERATOR));        // Flag it as generator
}

// This is a multi-line raw string specifying the parameter interface
// for this SOP.
static const char *theDsFile = R"THEDSFILE(
{
    name        parameters
    parm {
        name    "usdFile"      // Internal parameter name
        label   "Select USD File" // Descriptive parameter name for user interface
        type    file
        default { "0" }     // Default for this parameter on new nodes
        export  all         // This makes the parameter show up in the toolbox
                            // above the viewport when it's in the node's state.
    }

}
)THEDSFILE";

PRM_Template*
SOP_importUSD::buildTemplates()
{
    static PRM_TemplateBuilder templ("SOP_importUSD.C"_sh, theDsFile);
    return templ.templates();
}

class SOP_importUSDVerb : public SOP_NodeVerb
{
public:
    SOP_importUSDVerb() {}
    virtual ~SOP_importUSDVerb() {}

    virtual SOP_NodeParms *allocParms() const { return new SOP_importUSDParms(); }
    virtual UT_StringHolder name() const { return SOP_importUSD::theSOPTypeName; }

    virtual CookMode cookMode(const SOP_NodeParms *parms) const { return COOK_GENERIC; }

    virtual void cook(const CookParms &cookparms) const;
    
    /// This static data member automatically registers
    /// this verb class at library load time.
    static const SOP_NodeVerb::Register<SOP_importUSDVerb> theVerb;
};

// The static member variable definition has to be outside the class definition.
// The declaration is inside the class.
const SOP_NodeVerb::Register<SOP_importUSDVerb> SOP_importUSDVerb::theVerb;

const SOP_NodeVerb *
SOP_importUSD::cookVerb() const 
{ 
    return SOP_importUSDVerb::theVerb.get();
}

/// This is the function that does the actual work.
void
SOP_importUSDVerb::cook(const SOP_NodeVerb::CookParms &cookparms) const
{
    //get usd file path
    auto &&sopparms = cookparms.parms<SOP_importUSDParms>();
    GU_Detail *detail = cookparms.gdh().gdpNC();
    std::cout<<"Get USD file path:"<<" "<<sopparms.getUsdfile().c_str()<<"\n";

    std::string objname_stdString = sopparms.getUsdfile().c_str();
    if(objname_stdString != "0")
    {
        //read the file using USD API
        pxr::UsdStageRefPtr stage = pxr::UsdStage::Open(objname_stdString);
        if (!stage) {
            printf("fail to open USD file !!!!!\n");
        }else{
            printf("success to open USD file !!!!!\n");
        }

        //get mesh info using USD API
        pxr::UsdGeomMesh mesh(stage->GetPrimAtPath(pxr::SdfPath("/MyMesh")));
        if (!mesh) {
            printf("fail to retrieve mesh from USD file !!!!!\n");
        }else{
            printf("success to retrieve mesh from USD file !!!!!\n");
        }

        //get usd mesh information
        const pxr::UsdAttribute pointsAttr = mesh.GetPointsAttr();
        const pxr::UsdAttribute vertexCountsAttr = mesh.GetFaceVertexCountsAttr();
        const pxr::UsdAttribute vertexIndicesAttr = mesh.GetFaceVertexIndicesAttr();
        pxr::VtArray<int> vertexIndices;
        pxr::VtArray<int> vertexCounts;
        pxr::VtArray<pxr::GfVec3f> points;
        if (pointsAttr.HasValue())
            pointsAttr.Get(&points);//points
        if (vertexCountsAttr.HasValue())
            vertexCountsAttr.Get(&vertexCounts);//vertexCounts
        if (vertexIndicesAttr.HasValue())
            vertexIndicesAttr.Get(&vertexIndices);//vertexIndices

        //change usd info into houdini info
        GA_Offset start_ptoff;
        if(detail->getNumPoints() != points.size()){
            detail->clearAndDestroy();

            //Iterate over the vertex indices and create Houdini points using the corresponding positions
            for (int i = 0; i < points.size(); ++i) {
                const pxr::GfVec3f& position = points[i];
                GA_Offset pointOffset = detail->appendPoint();
                detail->setPos3(pointOffset, UT_Vector3(position[0], position[1], position[2]));
            }

            //test the points in detail
            printf("========================test if points store correctly======================\n");
            GA_FOR_ALL_PTOFF(detail, start_ptoff)
            {
                UT_Vector3 pos = detail->getPos3(start_ptoff);
                printf("Point %lld: (%f, %f, %f)\n", start_ptoff, pos.x(), pos.y(), pos.z());
            }

            //store in houdini
            GA_Offset start_vtxoff;
            for (int i =0; i < vertexCounts.size(); ++i) {  
                detail->appendPrimitivesAndVertices(GA_PRIMPOLY, 1, vertexCounts[i],start_vtxoff, true);

                // Manually wire the vertices to the corresponding points
                for (exint j = 0; j < vertexCounts[i]; ++j) {
                    GA_Offset vtxOff = start_vtxoff + j;
                    GA_Offset ptOff = vertexIndices[vtxOff];
                    detail->setVertexPoint(vtxOff, ptOff);
                }
            }
        }

    }
    
}

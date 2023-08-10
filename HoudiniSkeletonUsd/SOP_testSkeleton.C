#include "SOP_testSkeleton.h"
#include "SOP_testSkeleton.proto.h"

#include <GU/GU_Skin.h>
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
#include <GA/GA_AttributeRef.h>
#include <GA/GA_Handle.h>
#include <GU/GU_PrimPoly.h>
#include <UT/UT_Matrix4.h>
#include <UT/UT_Vector3.h>
#include <string>
#include <pxr/base/gf/quaternion.h>

using namespace my_testSkeletonUSD;

const UT_StringHolder SOP_testSkeletonUSD::theSOPTypeName("hdk_testSkeletonUSD"_sh);

void newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator(
        SOP_testSkeletonUSD::theSOPTypeName,   // Internal name
        "testSkeletonUSD",                     // UI name
        SOP_testSkeletonUSD::myConstructor,    // How to build the SOP
        SOP_testSkeletonUSD::buildTemplates(),// My parameters
        0,                          // Min # of sources
        0,                          // Max # of sources
        nullptr,                    // Custom local variables (none)
        OP_FLAG_GENERATOR));        // Flag it as generator
}

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
SOP_testSkeletonUSD::buildTemplates()
{
    static PRM_TemplateBuilder templ("SOP_testSkeleton.C"_sh, theDsFile);
    return templ.templates();
}

class SOP_testSkeletonUSDVerb : public SOP_NodeVerb
{
public:
    SOP_testSkeletonUSDVerb() {}
    virtual ~SOP_testSkeletonUSDVerb() {}

    virtual SOP_NodeParms *allocParms() const { return new SOP_testSkeletonParms(); }
    virtual UT_StringHolder name() const { return SOP_testSkeletonUSD::theSOPTypeName; }

    virtual CookMode cookMode(const SOP_NodeParms *parms) const { return COOK_GENERIC; }

    virtual void cook(const CookParms &cookparms) const;
    
    /// This static data member automatically registers
    /// this verb class at library load time.
    static const SOP_NodeVerb::Register<SOP_testSkeletonUSDVerb> theVerb;
};

const SOP_NodeVerb::Register<SOP_testSkeletonUSDVerb> SOP_testSkeletonUSDVerb::theVerb;

const SOP_NodeVerb *
SOP_testSkeletonUSD::cookVerb() const 
{ 
    return SOP_testSkeletonUSDVerb::theVerb.get();
}

void SOP_testSkeletonUSDVerb::cook(const SOP_NodeVerb::CookParms &cookparms) const
{
    //get usd file path
    auto &&sopparms = cookparms.parms<SOP_testSkeletonParms>();
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

        // Get the Skeleton prim
        pxr::UsdPrim skeletonPrim = stage->GetPrimAtPath(pxr::SdfPath("/MySkeleton"));
        if(!skeletonPrim){
            printf("fail to retrieve mesh from USD file !!!!!\n");
        }else{
            printf("success to retrieve mesh from USD file !!!!!\n");
        }

        // Get the attributes
        pxr::UsdAttribute bindTransformsAttr = skeletonPrim.GetAttribute(pxr::TfToken("bindTransforms"));
        pxr::UsdAttribute jointNamesAttr = skeletonPrim.GetAttribute(pxr::TfToken("jointNames"));
        pxr::UsdAttribute jointsAttr = skeletonPrim.GetAttribute(pxr::TfToken("joints"));

        pxr::VtValue bindTransformsValue;
        bindTransformsAttr.Get(&bindTransformsValue);

        pxr::VtValue jointsNameValue;
        jointNamesAttr.Get(&jointsNameValue);

        pxr::VtValue jointsPathValue;
        jointsAttr.Get(&jointsPathValue);

        const pxr::VtArray<pxr::GfMatrix4d>& bindTransforms = bindTransformsValue.Get<pxr::VtArray<pxr::GfMatrix4d>>();
        const pxr::VtArray<pxr::TfToken>& jointNames = jointsNameValue.Get<pxr::VtArray<pxr::TfToken>>();
        const pxr::VtArray<pxr::TfToken>& jointsPath = jointsPathValue.Get<pxr::VtArray<pxr::TfToken>>();
        std::vector<std::string> jointsParent;

        // Print the attribute values
        std::cout<<"==========================joints transformation matrix: ======================="<<"\n";
        for (const auto& matrix : bindTransforms) {
            std::cout << matrix << std::endl;
        }

        std::cout<<"================================joints name: ============================"<<"\n";
        for (const auto& string : jointNames) {
            std::cout << string.GetString()<< std::endl;
        }

        std::cout<<"==============================joints path: ================================="<<"\n";
        for (const auto& string : jointsPath) {
            std::cout << string.GetString()<< std::endl;
        }

        std::cout<<"==============================joints parent: ================================="<<"\n";
        for (int i=0; i<jointsPath.size();++i) {
            std::string path = jointsPath[i].GetString();
            std::string name = jointNames[i].GetString();
            std::string parentName;

            std::vector<std::string> pathTokens;
            size_t start = 0;
            size_t end = path.find('/');
            while (end != std::string::npos) {
                pathTokens.push_back(path.substr(start, end - start));
                start = end + 1;
                end = path.find('/', start);
            }
            pathTokens.push_back(path.substr(start));

            // Find the index of the name
            size_t nameIndex = std::find(pathTokens.begin(), pathTokens.end(), name) - pathTokens.begin();

            if (nameIndex > 0 && nameIndex < pathTokens.size()) {
                parentName = pathTokens[nameIndex - 1];
                std::cout << "Parent name: " << parentName << std::endl;
            } else {
                std::cout << "Parent name not found." << std::endl;
            }

            jointsParent.push_back(parentName);
        }

        for(const auto& string : jointsParent){
            std::cout<<string<<"\n";
        }

        std::cout<<"===============================test houdini data================================"<<"\n";

        //Create a Bone SOP node
        GU_Detail *gdp = cookparms.gdh().gdpNC();
        std::vector<UT_Matrix4> worldTransforms(jointNames.size());
        std::vector<UT_Vector3> worldPosition(jointNames.size());
        std::vector<UT_Vector3> rest(jointNames.size());
        std::vector<UT_Matrix3> multipleTransformMatrix(jointNames.size());
        std::vector<UT_Quaternion> restOrientations(jointNames.size());
        std::vector<UT_Matrix4> ut_BindTransforms(jointNames.size());
        GA_RWHandleV3 P(gdp->findAttribute(GA_ATTRIB_POINT, "P"));
        GA_RWHandleM4 xform(gdp->addFloatTuple(GA_ATTRIB_POINT, "transform", 16));
        if (P.isValid() && xform.isValid()) {
            // Iterate over all the joints
            for (int i = 0; i < jointNames.size(); i++) {

                const pxr::GfMatrix4d& bindTransform = bindTransforms[i];
                UT_Matrix4 ut_bindTransform(
                    bindTransform[0][0], bindTransform[0][1], bindTransform[0][2], bindTransform[0][3],
                    bindTransform[1][0], bindTransform[1][1], bindTransform[1][2], bindTransform[1][3],
                    bindTransform[2][0], bindTransform[2][1], bindTransform[2][2], bindTransform[2][3],
                    bindTransform[3][0], bindTransform[3][1], bindTransform[3][2], bindTransform[3][3]
                );

                UT_Matrix3 ut_Rotation(
                    bindTransform[0][0], bindTransform[0][1], bindTransform[0][2],
                    bindTransform[1][0], bindTransform[1][1], bindTransform[1][2],
                    bindTransform[2][0], bindTransform[2][1], bindTransform[2][2]
                );
                UT_Matrix3 ut_RotationTranspose = ut_Rotation.transposedCopy();

                UT_Matrix4 ut_BindTransform(
                    ut_RotationTranspose[0][0],ut_RotationTranspose[0][1],ut_RotationTranspose[0][2],ut_bindTransform[3][0],
                    ut_RotationTranspose[1][0],ut_RotationTranspose[1][1],ut_RotationTranspose[1][2],ut_bindTransform[3][1],
                    ut_RotationTranspose[2][0],ut_RotationTranspose[2][1],ut_RotationTranspose[2][2],ut_bindTransform[3][2],
                    0,0,0,1
                );

                ut_BindTransforms[i]=ut_BindTransform;

                UT_Quaternion q;
                q.updateFromRotationMatrix(ut_RotationTranspose);
                restOrientations[i] = q;

                //local position
                UT_Vector3 localTranslation;
                localTranslation.x() = bindTransform[3][0];
                localTranslation.y() = bindTransform[3][1];
                localTranslation.z() = bindTransform[3][2];

                rest[i]=localTranslation;

                //find the parents joint
                UT_Vector4 ut_worldTransform;
                UT_Vector3 translation;
                UT_Vector4 ut_original(0,0,0,1);
                if (i == 0) {
                    // For the root joint, the world transform is the same as the local bind transform
                    ut_worldTransform = ut_original * ut_bindTransform;
                    // ut_worldTransform = coordinateAdjustment * ut_worldTransform;
                    translation.x() = ut_worldTransform.x();
                    translation.y() = ut_worldTransform.y();
                    translation.z() = ut_worldTransform.z();
                    worldPosition[i] = translation;
                    multipleTransformMatrix[i] = ut_Rotation.transposedCopy();

                    // P.set(pointOffset, translation); 
                    std::cout<<"第一个点"<<worldPosition[i]<<"\n";
                } else {

                    int parentIndex = -1;
                    if(i != 0){
                        std::string parentName = jointsParent[i];
                        for (int i = 0; i < jointNames.size(); i++) {
                            if (jointNames[i] == parentName) {
                                parentIndex = i;
                                break;
                            }
                        }
                    }

                    multipleTransformMatrix[i] = multipleTransformMatrix[parentIndex] * ut_Rotation.transposedCopy();
                    UT_Vector3 T(bindTransform[3][0],bindTransform[3][1],bindTransform[3][2]);
                    UT_Vector3 Final((multipleTransformMatrix[parentIndex][0][0]*T[0]+multipleTransformMatrix[parentIndex][0][1]*T[1]+multipleTransformMatrix[parentIndex][0][2]*T[2]),
                                    (multipleTransformMatrix[parentIndex][1][0]*T[0]+multipleTransformMatrix[parentIndex][1][1]*T[1]+multipleTransformMatrix[parentIndex][1][2]*T[2]),
                                    (multipleTransformMatrix[parentIndex][2][0]*T[0]+multipleTransformMatrix[parentIndex][2][1]*T[1]+multipleTransformMatrix[parentIndex][2][2]*T[2]));
                    Final = Final + worldPosition[parentIndex];
                    // ut_worldTransform = worldPosition[i-1] * multipleTransformMatrix[i];
                    translation.x() = Final.x();
                    translation.y() = Final.y();
                    translation.z() = Final.z();
                    worldPosition[i] = Final;
                    std::cout<<"第一个点"<<worldPosition[i]<<"\n";
                }

            }

            for (int i = 0; i < jointNames.size(); i++) 
            {
                int parentIndex = -1;
                if(i != 0){
                    std::string parentName = jointsParent[i];
                    for (int j = 0; j < jointNames.size(); j++) {
                        if (jointNames[j] == parentName) {
                            parentIndex = j;
                            break;
                        }
                    }
                }

                GA_Offset pointOffset = gdp->appendPoint();
                gdp->setPos3(pointOffset, worldPosition[i]);

                GA_RWHandleV3 restAttr(gdp->addFloatTuple(GA_ATTRIB_POINT, "rest", 3));
                restAttr.set(gdp->pointOffset(i), rest[i]);

                GA_RWHandleQ restOrientAttr(gdp->addFloatTuple(GA_ATTRIB_POINT, "restorient", 4));
                restOrientAttr.set(gdp->pointOffset(i), restOrientations[i]);

                GA_RWAttributeRef nameAttrRef = gdp->findStringTuple(GA_ATTRIB_POINT, "name", 1, GA_STORE_STRING);
                if (nameAttrRef.isValid()) {
                    GA_RWHandleS nameHandle(nameAttrRef.getAttribute());
                    nameHandle.set(gdp->pointOffset(i), jointNames[i].GetString().c_str());
                }

                if(parentIndex != -1){
                    GU_PrimPoly* bone = GU_PrimPoly::build(gdp, 2, GU_POLY_OPEN, 0);
                    bone->setPointOffset(1, gdp->pointOffset(i));
                    bone->setPointOffset(0, gdp->pointOffset(parentIndex));
                }

                xform.set(pointOffset, ut_BindTransforms[i]);
            }

            GA_RWHandleM4 hTransforms(gdp->findAttribute(GA_ATTRIB_POINT, "transform"));
            GA_RWHandleM3 hTransform(gdp->addFloatTuple(GA_ATTRIB_POINT, "transforms", 9));

            GA_Offset ptoff;
            GA_FOR_ALL_PTOFF(gdp, ptoff)
            {
                UT_Matrix4 mat4 = hTransforms.get(ptoff);

                // Extract rotation from 4x4 matrix
                UT_Matrix3 mat3;
                mat3(0,0) = mat4(0,0); mat3(0,1) = mat4(0,1); mat3(0,2) = mat4(0,2);
                mat3(1,0) = mat4(1,0); mat3(1,1) = mat4(1,1); mat3(1,2) = mat4(1,2);
                mat3(2,0) = mat4(2,0); mat3(2,1) = mat4(2,1); mat3(2,2) = mat4(2,2);

                hTransform.set(ptoff, mat3);
            }
            gdp->destroyAttribute(GA_ATTRIB_POINT, "transform");
            gdp->renameAttribute(GA_ATTRIB_POINT, GA_SCOPE_PUBLIC, "transforms", "transform");
        }

    }
}

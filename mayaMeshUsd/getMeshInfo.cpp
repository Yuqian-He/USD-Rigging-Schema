#include <string>
#include <maya/MGlobal.h>
#include <maya/MSimple.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MString.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/points.h>     
#include <pxr/usd/sdf/path.h>           
#include <pxr/usd/sdf/types.h>          
#include <pxr/base/gf/vec3f.h> 

//define a command
DeclareSimpleCommand(getMeshInfo, PLUGIN_COMPANY, "1.0");

//command operation
MStatus getMeshInfo::doIt(const MArgList& args)
{
    //select mesh
    MSelectionList selection;
    MGlobal::getActiveSelectionList(selection);

    if(selection.length()==0)
    {
        MGlobal::displayError("No mesh selected.");
        return MS::kFailure;
    }else
    {
        MGlobal::displayInfo("Hello, World!");
    }

    //store selected object information path into DAGPath, 
    //easier access various properties and information associated with that mesh,like vertex positions, normals
    //store the information path into MFnMesh class
    MDagPath dagPath;
    selection.getDagPath(0, dagPath);
    MFnMesh meshFn(dagPath);

    //store vertices information in MPointArray
    MPointArray points;
    int polygonCount = meshFn.numPolygons();
    meshFn.getPoints(points, MSpace::kWorld);

    std::string polygonCountStr = std::to_string(polygonCount);
    MString message(polygonCountStr.c_str());
    MGlobal::displayInfo(message);

    // Create a USD stage
    pxr::UsdStageRefPtr stage = pxr::UsdStage::CreateNew("/Users/naname/Documents/test.usda");

    // Create a USD mesh
    pxr::UsdGeomMesh mesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/MyMesh"));

    // Convert points to USD format
    pxr::VtArray<int> faceVertexCounts(polygonCount);
    pxr::VtArray<int> faceVertexIndices;
    pxr::VtArray<pxr::GfVec3f> usdpoints(points.length());
    for (unsigned int i = 0; i < points.length(); ++i) {
        //if points change, the reference will change too.
        const MPoint& point = points[i];
        usdpoints[i] = pxr::GfVec3f(point.x, point.y, point.z);
    }

    for (unsigned int i = 0; i < polygonCount; ++i) {
        MIntArray polygonVertexIndices;
        meshFn.getPolygonVertices(i, polygonVertexIndices);
        faceVertexCounts[i] = polygonVertexIndices.length();

        for (unsigned int j = 0; j < polygonVertexIndices.length(); ++j) {
            faceVertexIndices.push_back(polygonVertexIndices[j]);
        }
    }

    // Set the USD mesh points attribute
    mesh.GetPointsAttr().Set(pxr::VtValue(usdpoints));
    mesh.GetFaceVertexCountsAttr().Set(pxr::VtValue(faceVertexCounts));
    mesh.GetFaceVertexIndicesAttr().Set(pxr::VtValue(faceVertexIndices));   

    stage->Save();
    
    return MS::kSuccess;

}
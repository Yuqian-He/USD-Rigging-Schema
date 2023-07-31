#include <string>
#include <vector>
#include <maya/MGlobal.h>
#include <maya/MSimple.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MString.h>
#include <maya/MFnIkJoint.h>
#include <maya/MGlobal.h>
#include <maya/MObject.h>
#include <maya/MFnDagNode.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/points.h>     
#include <pxr/usd/sdf/path.h>           
#include <pxr/usd/sdf/types.h>          
#include <pxr/base/gf/vec3f.h> 
#include <pxr/base/gf/matrix4d.h>
#include <pxr/usd/usdSkel/skeleton.h>
#include <pxr/base/vt/value.h>
#include <maya/MMatrix.h>
// #include <GU/GU_PrimPoly.h>

//define a command
DeclareSimpleCommand(getSkeletonInfo, PLUGIN_COMPANY, "1.0");

//define skeleton structure
struct Skeleton {
    std::vector<std::string> jointNames;
    std::vector<std::string> jointPath;
    std::vector<pxr::GfMatrix4d> jointTransforms;
    // std::map<std::string, std::string> jointHierarchy;
};

void printMatrix(const MMatrix& matrix, const char* matrixName) {
    MGlobal::displayInfo(MString(matrixName) + ":");
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            MGlobal::displayInfo(MString("") + matrix(i, j));
        }
    }
}

void visitJointHierarchy(const MObject& jointObject, Skeleton& skeleton, int depth = 0,const std::string& parentName = "") {
    MStatus status;

    // Create a joint function set
    MFnIkJoint jointFn(jointObject, &status);
    if (!status) {
        status.perror("MFnIkJoint constructor");
        return;
    }

    // Store the joint's local transform.
    MQuaternion rotation;
    jointFn.getRotation(rotation, MSpace::kTransform); //orient joint to world

    MVector translation = jointFn.getTranslation(MSpace::kTransform);

    MQuaternion scaleOrientation;
    jointFn.getScaleOrientation(scaleOrientation);

    MQuaternion orientation;
    jointFn.getOrientation(orientation);

    MMatrix rotationMatrix_M = rotation.asMatrix();
    MMatrix scaleOrientationMatrix_M = scaleOrientation.asMatrix();
    MMatrix orientationMatrix_M = orientation.asMatrix();

    MTransformationMatrix transformationMatrix = orientationMatrix_M * scaleOrientationMatrix_M * rotationMatrix_M;


    // Create an MMatrix instance with the reflection matrix
    MPoint jointPosition4D = MPoint(translation.x, translation.y, translation.z, 1.0);
    MMatrix transformationMatrixAsMMatrix = transformationMatrix.asMatrix();
    MPoint transformedJointPosition4D = jointPosition4D * transformationMatrixAsMMatrix;
    MVector transformedJointPosition = MVector(transformedJointPosition4D.x, transformedJointPosition4D.y, transformedJointPosition4D.z);
    MVector newTranslation = transformedJointPosition;

    MMatrix transformationMatrix_new = jointFn.transformationMatrix();

    transformationMatrix.setTranslation(newTranslation, MSpace::kTransform); 

    // Add the transform to the skeleton
    skeleton.jointTransforms.push_back(pxr::GfMatrix4d(transformationMatrix_new.matrix));

    //store joint name
    std::string name = jointFn.name().asChar();
    skeleton.jointNames.push_back(name);

    // Store the parent-child relationship in path
    std::string currentJointName;
    if (!parentName.empty()) {
        currentJointName = parentName + "/" + jointFn.name().asChar();
        skeleton.jointPath.push_back(currentJointName);
    }else{
        currentJointName = jointFn.name().asChar();
        skeleton.jointPath.push_back(currentJointName);
    }

    // Visit all child joints.
    for (unsigned int i = 0; i < jointFn.childCount(); ++i) {
        MObject childObject = jointFn.child(i, &status);
        if (!status) {
            status.perror("child");
            continue;
        }

        if (childObject.hasFn(MFn::kJoint)) {

            visitJointHierarchy(childObject, skeleton, depth + 1,currentJointName);
        }
    }

}

void printMySkeleton(Skeleton& skeleton)
{
    for (int i = 0; i < skeleton.jointPath.size(); i++) {
        MGlobal::displayInfo((std::string("Name: ") + skeleton.jointNames[i]+"\n").c_str());
        MGlobal::displayInfo((std::string("Path: ") + skeleton.jointPath[i] + "\n").c_str());

        std::ostringstream stream;
        stream << skeleton.jointTransforms[i];
        std::string matrixString = stream.str();
        MGlobal::displayInfo((std::string("Transform: ") + matrixString + "\n").c_str());
    }
}

void exportUSD(Skeleton &skeleton)
{
    // Create a USD stage
    pxr::UsdStageRefPtr stage = pxr::UsdStage::CreateNew("/Users/naname/Documents/mySkeleton.usda");
    // Define a new skeleton in USD.
    pxr::UsdSkelSkeleton usdSkeleton = pxr::UsdSkelSkeleton::Define(stage, pxr::SdfPath("/MySkeleton"));

    // Convert joint names, path and transforms to VtArrays.
    // pxr::VtArray<pxr::TfToken> jointPathUSD(skeleton.jointPath.begin(), skeleton.jointPath.end());
    pxr::VtArray<pxr::TfToken> jointNameUSD(skeleton.jointNames.begin(), skeleton.jointNames.end());
    pxr::VtArray<pxr::GfMatrix4d> jointTransforms(skeleton.jointTransforms.begin(), skeleton.jointTransforms.end());

    pxr::VtArray<pxr::TfToken> jointPathsUSD;
    for (const std::string& name : skeleton.jointPath) {
        jointPathsUSD.push_back(pxr::TfToken(name));
    }

    // Wrap the arrays in VtValue
    pxr::VtValue jointNamesValue(jointNameUSD);
    pxr::VtValue jointPathsValue(jointPathsUSD);
    pxr::VtValue jointTransformsValue(jointTransforms);

    // Set the joint names and bind transforms for the skeleton.
    usdSkeleton.CreateJointNamesAttr(jointNamesValue);
    usdSkeleton.CreateJointsAttr(jointPathsValue);
    usdSkeleton.CreateBindTransformsAttr(jointTransformsValue);


    stage->Save();

}

MStatus getSkeletonInfo::doIt(const MArgList& args)
{
    MStatus status;
    // Create an MSelectionList, which is a list of MObjects.
    MSelectionList selectionList;
    MGlobal::getActiveSelectionList(selectionList);

    // Initialize our Skeleton.
    Skeleton skeleton;

    //store maya skeleton information in skeleton
    for (unsigned int i = 0; i < selectionList.length(); ++i) {
        MObject object;
        status = selectionList.getDependNode(i, object);
        if (!status) {
            status.perror("getDependNode");
            continue;
        }

        if (object.hasFn(MFn::kJoint)) {
            visitJointHierarchy(object, skeleton);
        }
    }

    //test if skeleton is correct
    printMySkeleton(skeleton);

    //convert and store into USD format
    exportUSD(skeleton);

    return MS::kSuccess;

}



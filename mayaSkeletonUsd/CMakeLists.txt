cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mayaMeshUsd)

set(MAYA_INCLUDE_DIR "/Applications/Autodesk/maya2024/include")
set(MAYA_LIBRARY_DIR "/Applications/Autodesk/maya2024/lib")
set(USD_INCLUDE_DIR "/Applications/Autodesk/mayausd/maya2024/0.23.1_202304181210-131a6c1/mayausd/USD/include")
set(USD_LIBRARY_DIR "/Applications/Autodesk/mayausd/maya2024/0.23.1_202304181210-131a6c1/mayausd/USD/lib")
set(CMAKE_PREFIX_PATH "/Applications/Autodesk/mayausd/maya2024/0.23.1_202304181210-131a6c1/mayausd/USD")
set(PYTHON_LIBRARY_DIR "/Applications/Autodesk/maya2024/Maya.app/Contents/Frameworks/Python.framework/Versions/Current/lib")
set(PYTHON_INCLUDE_DIR "/Applications/Autodesk/maya2024/Maya.app/Contents/Frameworks/Python.framework/Versions/Current/include/python3.10")
find_package(pxr REQUIRED)

add_library(getSkeletonInfo MODULE getSkeletonInfo.cpp)  # Set the output type to MODULE
set_target_properties(getSkeletonInfo PROPERTIES SUFFIX ".bundle")  # Set the target extension to .bundle

# Include/Link Everything
target_include_directories(getSkeletonInfo PUBLIC
    ${PYTHON_INCLUDE_DIR}
    ${USD_INCLUDE_DIR}
    ${MAYA_INCLUDE_DIR}
)

target_link_libraries(getSkeletonInfo
    "/Applications/Autodesk/maya2024/Maya.app/Contents/Frameworks/Python.framework/Versions/Current/lib/libpython3.10.dylib"
    ${USD_LIBRARY_DIR}/libusd_gf.dylib
    ${USD_LIBRARY_DIR}/libusd_sdf.dylib
    ${USD_LIBRARY_DIR}/libusd_tf.dylib
    ${USD_LIBRARY_DIR}/libusd_usd.dylib
    ${USD_LIBRARY_DIR}/libusd_vt.dylib
    ${USD_LIBRARY_DIR}/libboost_atomic.dylib
    ${USD_LIBRARY_DIR}/libboost_python310.dylib
    ${USD_LIBRARY_DIR}/libusd_usdGeom.dylib
    ${USD_LIBRARY_DIR}/libusd_usdSkel.dylib
    ${MAYA_LIBRARY_DIR}/libOpenMaya.dylib
    ${MAYA_LIBRARY_DIR}/libOpenMayaAnim.dylib
    ${MAYA_LIBRARY_DIR}/libFoundation.dylib

)



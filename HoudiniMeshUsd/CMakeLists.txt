cmake_minimum_required( VERSION 3.6 )

project( HDK_Project )

# CMAKE_PREFIX_PATH must contain the path to the toolkit/cmake subdirectory of
# the Houdini installation. See the "Compiling with CMake" section of the HDK
# documentation for more details, which describes several options for
# specifying this path.
list( APPEND CMAKE_PREFIX_PATH "/Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Versions/19.5/Resources/toolkit/cmake" )

# Locate Houdini's libraries and header files.
# Registers an imported library target named 'Houdini'.
find_package( Houdini REQUIRED )

set(USD_INCLUDE_DIR "/Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Versions/19.5/Resources/toolkit/include")
set(USD_LIBRARY_DIR "/Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Libraries")
set( library_name SOP_importUSD )

# Code generation for the embedded DS file in SOP_Star.C.
houdini_generate_proto_headers( FILES SOP_importUSD.C )

# Add a library and its source files.
add_library( ${library_name} SHARED
    SOP_importUSD.C
    SOP_importUSD.h
)

# Link against the Houdini libraries, and add required include directories and
# compile definitions.
target_link_libraries( ${library_name} Houdini )
target_include_directories(${library_name} PUBLIC
    ${USD_INCLUDE_DIR}
)

# Include ${CMAKE_CURRENT_BINARY_DIR} for the generated header.
target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(${library_name}
    "/Applications/Houdini/Houdini19.5.534/Frameworks/Python.framework/Versions/3.9/lib/libpython3.9.dylib"
    ${USD_LIBRARY_DIR}/libpxr_gf.dylib
    ${USD_LIBRARY_DIR}/libpxr_sdf.dylib
    ${USD_LIBRARY_DIR}/libpxr_tf.dylib
    ${USD_LIBRARY_DIR}/libpxr_usd.dylib
    ${USD_LIBRARY_DIR}/libpxr_vt.dylib
    ${USD_LIBRARY_DIR}/libpxr_usdGeom.dylib

)

# Sets several common target properties, such as the library's output directory.
houdini_configure_target( ${library_name} )

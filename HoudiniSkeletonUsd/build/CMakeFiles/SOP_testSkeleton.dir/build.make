# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/naname/Documents/masterProject/HoudiniSkeletonUsd

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build

# Include any dependencies generated for this target.
include CMakeFiles/SOP_testSkeleton.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SOP_testSkeleton.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SOP_testSkeleton.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SOP_testSkeleton.dir/flags.make

SOP_testSkeleton.proto.h: /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/SOP_testSkeleton.C
SOP_testSkeleton.proto.h: /Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Versions/19.5/Resources/houdini/python3.9libs/generate_proto.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating SOP_testSkeleton.proto.h"
	cd /Users/naname/Documents/masterProject/HoudiniSkeletonUsd && /Applications/Houdini/Houdini19.5.534/Frameworks/Python.framework/Versions/3.9/bin/python3.9 /Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Versions/19.5/Resources/houdini/python3.9libs/generate_proto.py SOP_testSkeleton.C /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build/SOP_testSkeleton.proto.h

CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o: CMakeFiles/SOP_testSkeleton.dir/flags.make
CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o: /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/SOP_testSkeleton.C
CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o: SOP_testSkeleton.proto.h
CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o: CMakeFiles/SOP_testSkeleton.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o -MF CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o.d -o CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o -c /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/SOP_testSkeleton.C

CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/SOP_testSkeleton.C > CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.i

CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/SOP_testSkeleton.C -o CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.s

# Object files for target SOP_testSkeleton
SOP_testSkeleton_OBJECTS = \
"CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o"

# External object files for target SOP_testSkeleton
SOP_testSkeleton_EXTERNAL_OBJECTS =

/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: CMakeFiles/SOP_testSkeleton.dir/SOP_testSkeleton.C.o
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: CMakeFiles/SOP_testSkeleton.dir/build.make
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: /Applications/Houdini/Houdini19.5.534/Frameworks/Python.framework/Versions/3.9/lib/libpython3.9.dylib
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: /Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Libraries/libpxr_gf.dylib
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: /Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Libraries/libpxr_sdf.dylib
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: /Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Libraries/libpxr_tf.dylib
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: /Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Libraries/libpxr_usd.dylib
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: /Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Libraries/libpxr_vt.dylib
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: /Applications/Houdini/Houdini19.5.534/Frameworks/Houdini.framework/Libraries/libpxr_usdGeom.dylib
/Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib: CMakeFiles/SOP_testSkeleton.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library /Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SOP_testSkeleton.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SOP_testSkeleton.dir/build: /Users/naname/Library/Preferences/houdini/19.5/dso/SOP_testSkeleton.dylib
.PHONY : CMakeFiles/SOP_testSkeleton.dir/build

CMakeFiles/SOP_testSkeleton.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SOP_testSkeleton.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SOP_testSkeleton.dir/clean

CMakeFiles/SOP_testSkeleton.dir/depend: SOP_testSkeleton.proto.h
	cd /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/naname/Documents/masterProject/HoudiniSkeletonUsd /Users/naname/Documents/masterProject/HoudiniSkeletonUsd /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build /Users/naname/Documents/masterProject/HoudiniSkeletonUsd/build/CMakeFiles/SOP_testSkeleton.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SOP_testSkeleton.dir/depend


# Maya Skeleton Plugin
## Introduce
The Maya skeleton plugin, developed as a key part of this project, leverages the C++ [Maya API](https://help.autodesk.com/view/MAYAUL/2022/ENU/?guid=Maya_SDK_Maya_API_introduction_API_Basics_html) to offer a unique capability. This code represents a Maya plugin called "getSkeletonInfo" that exports skeleton data from selected joints in Maya to a USD file. The plugin defines a "Skeleton" structure to store joint names, paths and transforms. It uses recursive functions to traverse the joint hierarchy, extracting joint information and transforming it into USD-compatible data structures. Finally, the plugin creates a new USD stage, defines a skeleton in USD, and exports the joint names, paths, and transforms to the USD file. The resulting USD file can be used in other applications that support USD format, such as Houdini, for [further manipulation](https://github.com/Yuqian-He/USD-Rigging-Schema/tree/main/HoudiniSkeletonUsd).

## File Structure
- getSkeletonInfo.cpp: This is the main script I wrote for Maya plugin.

## Development Environment
- build system generator: CMake
- build system: Ninja
- compiler: Clang 14.0.0 arm64-apple-darwin22.1.0
- Integrated Development Environment (IDE): Visual Studio Code
- C++ libraries:
  - maya_2024
  - USD (maya_2024 built-in usd)
  - python3.10

## How to build (only test on macOS)
### Before start
> [!IMPORTANT]
> Remember to replace all the paths in CMakeLists.txt to fit your version of Maya and USD (mine is Maya2024), as I didn't figure out how to automatically adapt to all user's paths. I'm on macOS, so most of the paths should be the same, but you should still check yours in case it doesn't look right.

1. line10 --> change to your version of Maya include
2. line11 --> change to your version of Maya lib
3. line12 --> change to your version of MayaUsd Usd include
4. line13 --> change to your version of MayaUsd Usd lib
5. line14 --> change to your version of MayaUsd Usd
6. line15 --> change to your version of Maya python lib
7. line16 --> change to your version of Maya python include
8. line30 --> change to the path to your Maya python version link If you have a different version of my Maya, double check the link libraries name is correct or not (line 31-40). As I know maya 2023 and 2024 has a different link libraries name. (all my libraries are in "/Applications/Autodesk/mayausd/maya2024/0.23.1_202304181210-131a6c1/mayausd/USD/lib/")

### Build getSkeletonInfo.cpp
When building this C++ project, the resulting plugin is packaged as a "bundle file." Bundles are special folders treated as single files by macOS. The bundle contains the compiled plugin code, along with necessary resources and metadata. This bundling simplifies plugin distribution, allowing Maya to efficiently load and utilize the plugin within its environment.
```c
//under the folder mayaSkeletonUsd (make sure your compiler is the same as mine)
mkdir build
cmake ..
make
```

### Load plugin in Maya
Open Maya --> Plug-in Manager --> Browse. Load the ".bundle" file which is usually in your build folder when you build getSkeletonInfo.cpp. Then open "Maya Scripts Editor" type "getSkeletonInfo;" in MEL scripts and run. You will find the exported file in "/Users/naname/Documents/" named "mySkeleton.usda"

> [!NOTE]
>  If you want to change the path and name of the exported file, you can change the getSkeletonInfo.cpp script line 136. Because the time limitation, I haven't done anything compatible yet.




  


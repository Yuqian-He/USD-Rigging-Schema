# Maya-Houdini USD Rigging Schema for Streamlined Animation Workflow

## Overall Idea
### abstract
This project presents an innovative approach for transferring mesh and skeleton data from Maya to Houdini using the Universal Scene Description (USD) format, providing a supplementary method to the traditional FBX and ABC data transfer processes. Initially, two plugins were developed using the C++ Maya API, designed to extract mesh and skeleton information from Maya. This data was then converted with the USD API and exported in a USD format. For importing this data into Houdini, two additional plugins were developed utilizing C++ Houdini Development Kit (HDK), converting the USD data into a format that Houdini can recognize and display. In essence, this project explores an alternative avenue for data exchange between Maya and Houdini, contributing to the diversification of data transfer methodologies in the 3D animation industry.

### Workflow


## Development Environment

### Maya plugin 

- build system generator: CMake
- build system: Ninja
- compiler: Clang 14.0.0 arm64-apple-darwin22.1.0
- Integrated Development Environment (IDE): Visual Studio Code
- C++ libraries:
  - maya_2024
  - USD (maya_2024 built in usd)
  - python3.10

### Houdini plugin

- build system generator: CMake 3.26.4
- build system: Unix Makefiles
- compiler: Xcode
- Integrated Development Environment (IDE): Visual Studio Code
- C++ libraries:
  - houdini_19.5
  - USD (houdini_19.5 built in usd)
  - python3.9

## Result


# Engine 3D &middot; [![Build Status](https://dev.azure.com/simonecorazza/Engine3D/_apis/build/status/SimoneCorazza.Engine3D?branchName=master)](https://dev.azure.com/simonecorazza/Engine3D/_build/latest?definitionId=1&branchName=master)

A simple real time rendering engine using **OpenGL** and **C++**.

This project is not meant to be a rendering engine that someone will use for real applications, but is meant to someone that wants to learn the basic of a rendering engine. For this purpose the code is well documented and there is the [wiki](https://github.com/SimoneCorazza/Engine3D/wiki) to explain the main concepts.

## Features

### Optimized rendering pipeline can render up to 30 000 actors at 60 FPS

<img width="auto" height="auto" src="https://raw.githubusercontent.com/wiki/SimoneCorazza/Engine3D/images/StressTest.jpg"/>

### Post process shaders

Black and white

<img width="32%" height="auto" src="https://raw.githubusercontent.com/wiki/SimoneCorazza/Engine3D/images/BlackAndWhitePostProcess.jpg"/>

Blur

<img width="32%" height="auto" src="https://raw.githubusercontent.com/wiki/SimoneCorazza/Engine3D/images/BlurPostProcess.jpg"/>

Depth

<img width="32%" height="auto" src="https://raw.githubusercontent.com/wiki/SimoneCorazza/Engine3D/images/DepthPostProcess.jpg"/>

### Parametrization of shaders

<img width="auto" height="auto" src="https://raw.githubusercontent.com/wiki/SimoneCorazza/Engine3D/images/ComplexShaders.gif"/>

### Lights (no shadow though)

<img width="auto" height="auto" src="https://raw.githubusercontent.com/wiki/SimoneCorazza/Engine3D/images/LightShaders.gif"/>

## Getting Started

### Prerequisites

* Visual Studio 2022 (may work with older version)
* The Visual Studio C++ Package

### Installing

1. Install the [vcpkg](https://vcpkg.io/en/index.html) package manager ([official instruction here](https://vcpkg.io/en/getting-started.html) but don't skip the 3th step):
    1. Clone the repo `git clone https://github.com/Microsoft/vcpkg.git`
    2. Run *.bat* file inside the cloned repo: `.\vcpkg\bootstrap-vcpkg.bat`
    3. The previous step generated the `vcpkg.exe` file. To use directly in the command line add the folder containing the *exe** in the PATH ([here](https://stackoverflow.com/questions/44272416/how-to-add-a-folder-to-path-environment-variable-in-windows-10-with-screensho) is a tutorial to add a directory to the PATH)
2. After cloning this repo open a command prompt in `\Engine3D\Engine3D` and run `vcpkg install` this command will download and install all the dependences inside the `.\vcpkg_installed` folder inside the project
3. Open the file solution `Engine3D.sln`
4. Go to the setting of the `Engine3D` project
5. Change the value of `Configuration Properties -> Debugging -> Working Directory`  to `$(ProjectDir)\WorkingDirectory`

### Runnig

1. Open the **Engine3D** project proprieties
2. Change the propriety Working Directory to `$(ProjectDir)\WorkingDirectory`
3. Start the Engine3D project

If you want to run a different scene you can go to [`main.cpp`](./Engine3D/main.cpp) file and uncomment the scene you want.

### Project structure

There are 2 projects in the Visual Studio `.sln` file: **Engine3D** and **EngineEditor**.

### Engine3D

This is the core of the engine written in C++.

Libraries:

* [GLEW](http://glew.sourceforge.net/) Utilities of OpenGL.
* [GLFW](http://www.glfw.org/) To handle the inputs and the OpenGL context.
* [FreeImage](http://freeimage.sourceforge.net) To load the image assets. Licensed under the FIPL license.
* [FreeType](https://www.freetype.org/) To render glyphs.
* [GLM](https://glm.g-truc.net) To simplify math.

The project is composed by those filters:

1. `Engine` The rendering engine.
2. `Shaders` Shaders used in the engine.
3. `Resources` Resources used in the test game.
4. `Examples` Example scenes.

### EngineEditor

This is the editor of the engine made in C#. The main functionality is the conversion of a  `.obj` mesh in the custom `.msh` format used by the engine.

## License

This project is licensed under the [MIT License](./LICENSE).

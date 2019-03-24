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

* Visual Studio 2017

### Installing

No installation needed. Dependencies are included in this repository (it is strangely hard to manage dependencies in C++).

**Although** to make work the example scene you need to change the WorkingDirectory of the Engine3D project:

1. Open the **Engine3D** project proprieties
2. Go to *Debugging*
3. Change the propriety Working Directory to `$(ProjectDir)\WorkingDirectory`

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

This project is licensed under the MIT License
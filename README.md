# Engine 3D

A simple rendering engine in real time using **OpenGL** and **C++**.

This project is not meant to be a rendering engine that someone will use for real applications, but is meant to someone that wants to learn the basic of a rendering engine.

You can have a high level overview at the [wiki](https://github.com/SimoneCorazza/Engine3D/wiki)

**NOTE**: the comments of the source code where translated so they may have some issues.

## Features

* Rendering meshes at screen
* Optimized rendering pipeline can render up to 30 000 actors at 60 FPS
* Rendering text at screen
* Simple implementation of lights (no shadows)
* Customizables shaders

[[https://raw.githubusercontent.com/wiki/SimoneCorazza/Engine3D/images/stressTest.gif]]

## Getting Started

### Prerequisites

* Visual Studio 2015 (not tested other versions)

### Installing

No installation needed. Dependencies are included in this repository (it is strangely hard to manage dependencies in C++).

**Although** to make work the example scene you need to change the WorkingDirectory of the Engine3D project:

1. Open the **Engine3D** proprieties
2. Go to *Debugging*
3. Change the propriety Working Directory to `$(ProjectDir)\WorkingDirectory`

## Project structure

There are 2 projects in the Visual Studio .sln file: **Engine3D** and **EngineEditor**.

### Engine3D

This is the core of the engine written in C++.

Libraries:
* [GLEW](http://glew.sourceforge.net/) Utilities of OpenGL.
* [GLFW](http://www.glfw.org/) To handle the inputs and the OpenGL context.
* [FreeImage](http://freeimage.sourceforge.net) To load the image assets. Licensed under the FIPL license.
* [FreeType](https://www.freetype.org/) To render glyphs.
* [GLM](https://glm.g-truc.net) To simplify math.

There are two top level filters (folders):
1. `Engine` The rendering engine.
2. `TestGame` A scene to test the rendering engine and it's performance.

### EngineEditor

This is the editor of the engine made in C#. The main functionality is the conversion of a  `.obj` mesh in the custom `.msh` format used by the engine.


## License

This project is licensed under the MIT License
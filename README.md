# Engine 3D

A simple rendering engine in real time using **OpenGL** and **C++**.

This project is not ment to be a rendering engine that someone will use for real applications, but is ment to someone that whants to lern the basic of a rendering engine.

## Features

* Rendering meshes at screen
* Optimaized rendering pipeline
* Rendering text at screen

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

* Visual Studio 2015 (not tested other versions)

### Installing

No installation needed. Dependences are included in this repository (it is stranglly hard to manage dependences in C++).

## Project structure

There are 2 projects in the Visual Studio .sln file: **Engine3D** and **EngineEditor**.

### Engine3D

This is the core of the engine written in C++.

Libraries:
* [GLEW](http://glew.sourceforge.net/) Utilities of OpenGL.
* [GLFW](http://www.glfw.org/) To handle the inputs and the OpenGL context.
* [FreeImage](http://freeimage.sourceforge.net) To load the image assets. Licenzed under the FIPL license.
* [FreeType](https://www.freetype.org/) To render glyphs.
* [GLM](https://glm.g-truc.net) To simplify math.

### EngineEditor

This is the editor of the engine made in C#. Basicly it can turn a `.obj` mesh in the custom `.msh` format used by the engine.


## License

This project is licensed under the MIT License
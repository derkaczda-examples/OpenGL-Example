# OpenGL-Example

An example of programming with OpenGL based on this [Youtube Series](https://www.youtube.com/watch?v=W3gAzLwfIP0&amp;list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&amp;t=113s&amp;index=2).

## Tools/Dependencies

* [OpenGl documentation](http://docs.gl/)
* Visual Studio 2017
* [GLFW](http://www.glfw.org/index.html)
* [GLEW](http://glew.sourceforge.net/)

## Visual C++ Project Setup

#### Additional Include Directories
* $(SolutionDir)\dependencies\GLFW\include
* $(SolutionDir)\dependencies\GLEW\include
* $(SolutionDir)\src\vendor\
* $(SolutionDir)\src

#### Additional Library Directories
* $(SolutionDir)\dependencies\GLFW\lib-vc2015
* $(SolutionDir)\dependencies\GLEW\x64

#### Linker Input dependencies
* glfw3.lib
* opengl32.lib
* glew32s.lib

#### Preprocessor
* GLEW_STATIC

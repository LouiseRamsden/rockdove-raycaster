# rockdove-raycaster (WORK IN PROGRESS!)
Simple Flat Colour Raycaster as an experiment into graphics rendering techniques

### Using
* [OpenGL 1.0](https://www.khronos.org/opengl/wiki/Main_Page) (This project does not need shaders and just requires draw calls to the screen)
* [freeGLUT](https://freeglut.sourceforge.net/) (Window Management, Event Management, It is fresh in my memory currently)
* May add more API support in the future, but for now OpenGL 1.x is good for the scope and complexity, and GLUT is lighter weight than SDL

### Build instructions
Should be debugged and compiled from inside either VisualStudio or Rider. Due to glut being a 32 bit library, the project ***must*** be compiled using x86 not x64 otherwise there will be a lot of linker errors.

### Progress screenshots
![25/07/2024](https://github.com/LouiseRamsden/rockdove-raycaster/blob/main/screenshots/rockdove-raycaster25072024.png?raw=true)
(25/07/2024) Made it look a little like a circus, raycaster works but it has some issues, my method of drawing is not perfect
![26/07/2024](https://github.com/LouiseRamsden/rockdove-raycaster/blob/main/screenshots/rockdove-raycaster26072024.png?raw=true)
(26/07/2024) Added some fake lighting to make it have some more depth, it works surprisingly well. I made it look like a hedge maze during sun down, which has a sort of eerie feeling.

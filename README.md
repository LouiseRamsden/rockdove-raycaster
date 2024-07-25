# rockdove-raycaster (WORK IN PROGRESS!)
Simple Flat Colour Raycaster as an experiment into graphics rendering techniques

### Using
* OpenGL 1.0 (This project does not need shaders and just requires draw calls to the screen)
* freeGLUT (Window Management, Event Management, It is fresh in my memory currently)
* May add more API support in the future, but for now OpenGL 1.x is good for the scope and complexity, and GLUT is lighter weight than SDL

### Build instructions
Should be debugged and compiled from inside either VisualStudio or Rider. Due to glut being a 32 bit library, the project **must** be compiled using x86 not x64 otherwise there will be a lot of linker errors.

### Progress screenshots
![25/07/2024](https://github.com/LouiseRamsden/rockdove-raycaster/blob/main/screenshots/rockdove-raycaster25072024.png?raw=true)
(25/07/2024) Made it look a little like a circus, raycaster works but it has some issues, my method of drawing is not perfect

# rockdove-raycaster
Simple Flat Colour Raycaster as an experiment into graphics rendering techniques

### Using
* OpenGL 1.0 (This project does not need shaders and just requires draw calls to the screen)
* freeGLUT (Window Management, Event Management, It is fresh in my memory currently)
* (Possibly may add more renderer options in the future to add even more on the GPU but so far its fine)

### Build instructions
Should be debugged and compiled from inside either VisualStudio or Rider. Due to glut being a 32 bit library, the project **must** be compiled using x86 not x64 otherwise there will be a lot of linker errors.
 

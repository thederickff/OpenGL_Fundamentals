# OpenGL Fundamentals

This repository contains the code for TheCherno's series on OpenGL. It uses CMake to manage the build process, making it cross-platform. Follow along the video playlist below:


[![Watch his video series here.](https://img.youtube.com/vi/W3gAzLwfIP0/0.jpg)](https://youtu.be/W3gAzLwfIP0?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)


## Installation

### Ubuntu

To compile you first need to have CMake, GLEW, and GLFW installed. In the terminal run

```
sudo apt-get update
sudo apt-get -y install build-essential cmake libglfw3-dev libglew-dev
```

## Compilation

In the terminal `cd` to the project directory and create a build directory. Now there should be a working 
```
cd <Path to OpenGL_Fundamentals>
mkdir ./build
cd ./build
cmake ..
make
```

## Execution

To run the program `cd` to the directory containing the `res/` directory. By default this is OpenGL_Fundamentals, but you can also copy the `res/` directory into the location that the executable is saved and run it from there. As long as you're executing the binary in a directory containing `res/ you can run the executable and it should work.

```
./build/myapp
```



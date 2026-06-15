
## About This Project

Cebeci Engine does not enforce any specific build system (like CMake, Make, or Visual Studio solutions). We believe in absolute development freedom; you should not be restricted by our build configurations. 

The repository contains **pure source code**. This allows you to:
- Integrate the engine directly into your own custom build system.
- Modify, tweak, and compile the source code exactly according to your game's specific needs and target platforms.

### How to Integrate
To use Cebeci Engine in your project, simply:
1. Include the source files (`.cpp` and `.h`/`.hpp`) directly into your project structure.
2. Ensure you have the required dependencies configured in your own build environment.
3. Compile using your preferred C++ compiler (GCC, Clang, MSVC) with C++17 (or higher) enabled.

## Dependencies

Cebeci Engine uses the following open-source libraries:

- [GLFW](https://www.glfw.org/) - For window creation and input handling.
- [GLAD](https://glad.dav1d.de/) - For OpenGL function pointer loading.
- [GLM (OpenGL Mathematics)](https://github.com/g-truc/glm) - For header-only math operations.
- [stb_image](https://github.com/nothings/stb) - For loading textures and images.

To compile the engine, you must link these libraries with your project or include them in your build system (e.g., CMake, Make).

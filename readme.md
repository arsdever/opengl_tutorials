## Prerequisites
- [vcpkg](https://vcpkg.io/en/getting-started.html)
- [CMake](https://cmake.org/install/)
- [A compiler](https://en.wikipedia.org/wiki/Compiler)
  + [Visual Studio](https://visualstudio.microsoft.com/)
  + [CLang](https://releases.llvm.org/download.html)
  + [GCC](https://gcc.gnu.org/)
  + Basically any compiler. If it doesn't compile or work properly, feel free
	to file an issue. I'll definitelly address it.

## Installation
1. Open a terminal
2. If you don't have the `vcpkg` in your path, `cd` to the `vcpkg` directory
3. Install some pakages with the following command
   ```
   vcpkg install glfw3 glad OpenGL
   ```
5. Configure the `cmake`
   ```
   cd -
   mkdir build
   cd build
   cmake ../ -DCMAKE_TOOLCHAIN_FILE=<path_to_vcpkg>/scripts/buildsystems/vcpkg.cmake
   ```
6. Build
   ```
   cmake -b .
   ```
# Description
This repository contains the surce code of a bytecode virtual machine and a bytecode compiler.

# Build
This project require CMake.
To build the executables go to the __BVM/__ directory, than type from cmd:
```
mkdir build
cmake ./build
```
to switch between __Debug__ or __Release__ build type add 
```-DCMAKE_BUILD_TYPE:String=Debug``` or ```-DCMAKE_BUILD_TYPE:String=Release``` to 
```cmake ./build```.

Than to build the project type
```
cmake --build ./build
```

# Usage
First navigate to the executable directory.
### Bytecode compiler (bcc)
 - Windows : ```./bcc.exe <source_path> <out_path> ```
 - Linux : ```./bcc <source_path> <out_path> ```
### Bytecode vm (bvm)
 - Windows : ``` ./bvm.exe <bytecode_path> ```
 - Linux : ``` ./bvm <bytecode_path> ```


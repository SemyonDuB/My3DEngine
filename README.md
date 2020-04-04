# SovietGameEngine
This is a project that I'm developing just for fun.
### REQUIRMENTS:
* Qt5 5.14.2
* Boost 1.72.0
* assimp 5.0.1

All of these dependencies are set by conan

### INSTALL:
First of all go into the project and create build directory:
```
cd "PROJECT-NAME"
mkdir build
cd build
```

After that, make sure that you have python3:
```
python3 --version
```

If you don't have python3 please install it and try again. All information about python at https://www.python.org/.
<br/>Next step, you should install conan - package managment:
```
pip install conan
```

And the final step, you should install CMake, check at https://cmake.org/. And build project:
```
conan install .. --build missing
cmake ..
cmake --build .
```

You can run executable file in build/src/SGE
<br/>All tests placed in build/tests/

You can give me advice or just help me with something, or if you can't build my project, I will try to help you.
<br/>THX!

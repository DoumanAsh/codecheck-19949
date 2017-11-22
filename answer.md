## Requirements

* CMake to build C++ code
* Boost for spawning sub-processes

## Instructions

### Build

```
mkdir build
cd build
cmake ../
cmake --build .
```

Used CMake variables:

* `UNIT_TEST` - enable unit testing using Boost
* `CLANG_TIDY` - use clang-tidy for static code analysis

Binaries can be found in:
```
<build directory>/dist/bin
```

### Run example

```
./dist/bin/fw ./dist/bin/ai ./dist/bin/ai shiritori internet tail grep less telnet sed
```

### Unit testing

```
dist/bin/ai_ut
dist/bin/fw_ut
```

## Design

### AI

Only choose among available words.
If no available or cannot find appropriate it prints nothing.
Decided that it would be more simple this way.

### Framework

Follows specification in exercise.

It abnormally exits only in following cases:
* Lacking number of arguments
* AI launch arguments points to non-existing file (Maybe it could be removed as we can search PATH variable)
* Abnormal exit of AI program since it is unexpected case.

In all above cases return code is 1.
Otherwise, on success, program returns 0.

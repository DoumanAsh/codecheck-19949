#!/bin/bash

ROOT=$(cd $(dirname $0) && pwd)
cd $ROOT

### C++ ###
rm -rf build || true
mkdir  build
cd build
cmake ..
cmake --build .
cd -


### Java ###
#cd $ROOT/java/fw
#mvn package -Dmaven.test.skip=true
#cd $ROOT/java/ai
#mvn package -Dmaven.test.skip=true

### Python ###
# cd $ROOT/python/src
# python -m compileall .


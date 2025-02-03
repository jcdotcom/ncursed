#!/bin/bash

mv new_build last_build
gcc -g -w -std=c++23 -lncurses -lstdc++ main.cpp Game.cpp Area.cpp -o new_build
./new_build


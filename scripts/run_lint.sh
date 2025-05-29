#!/bin/sh
set -e
cmake -S . -B build_lint -DCMAKE_CXX_FLAGS="-Wall -Wextra -Werror"
cmake --build build_lint

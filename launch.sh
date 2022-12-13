#!/bin/bash

ARGUMENT=$1

cd build
echo "[Calling cmake]:"
cmake ..

if [ "$ARGUMENT" == "re" ]; then
    echo -e "\n[MAKE CLEAN]"
    make clean
fi

echo -e "\n[Compiling with Makefile]:"
make

echo -e "\nCompilation is done."

echo -e "\n[Moving binary to root]"
mv bomberman ..
#!/bin/bash
if [ -d "build" ]; then
  rm  -rf build
fi

mkdir build

cd build

cmake -G Ninja ..

ninja

cd ..

rm -rf build
./SnakeGame.out


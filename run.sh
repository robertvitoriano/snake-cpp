#!/bin/bash

cd build

cmake -G Ninja ..

ninja

cd ..

./SnakeGame.out

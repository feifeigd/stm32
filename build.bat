@echo off

cmake -B build -S . -G "Unix Makefiles"
cmake --build build

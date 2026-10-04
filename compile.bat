@echo off
echo Compiling...
g++ -std=c++11 -o filesystem.exe main.cpp hashmap.cpp treenode.cpp file.cpp heaps.cpp filesystem.cpp
echo Compilation finished.
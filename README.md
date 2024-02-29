# TiqTaq

Simple Tic-Tac-Toe application using Qt Widgets

## Usage Guide

...

## Build Guide

This project requires Catch2 for building and running tests. To disable building of tests, pass the CMake arg '-DBUILD_TESTING:BOOL=FALSE'.

Catch2 may be preinstalled, installed using a package manager, or built from source using the provided dependency SuperBuild. See [deps-superbuild](deps-superbuild/README.md) for details.

## Ubuntu LTS 22.04

```
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt-get install libxkbcommon-dev
sudo apt-get install qt6-base-dev
```

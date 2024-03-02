# TiqTaq

Simple Tic-Tac-Toe application using Qt Widgets

## Usage Guide

Launch Tic-Tac-Toe application:
```
<build-dir>/tiqtaq/row_tiqtaq
```

## Build Guide

This project requires Catch2 for building and running tests. To disable building of tests, pass the CMake arg '-DBUILD_TESTING:BOOL=FALSE'.

Catch2 may be preinstalled, installed using a package manager, or built from source using the provided dependency SuperBuild. See [deps-superbuild](deps-superbuild/README.md) for details.

## Ubuntu LTS 22.04

Install QT 6 (6.2):
```
sudo apt-get install qt6-base-dev
```

You may also need to install some other packages for find_package with component Widgets to work:
```
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

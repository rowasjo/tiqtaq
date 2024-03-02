# TiqTaq

Simple Tic-Tac-Toe application using Qt Widgets

## Usage Guide

Launch Tic-Tac-Toe application:
```
<build-dir>/tiqtaq/row_tiqtaq
```

## Build Guide

To disable building of tests, pass the CMake arg '-DBUILD_TESTING:BOOL=FALSE'.

## Ubuntu LTS 22.04

Install QT 6 (6.2):
```
sudo apt-get install qt6-base-dev
```

You may also need to install some other packages for find_package with component Widgets to work:
```
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

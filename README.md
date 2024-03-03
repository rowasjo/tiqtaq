# TiqTaq

TiqTaq is a simple Tic-Tac-Toe application developed with Qt Widgets, offering a classic game experience with a minimalistic Qt 6 interface.

## Prerequisites

- CMake
- GNU Make or Ninja
- GCC/G++ or Clang
- Qt6 (specifically, Qt6Widgets)

For Ubuntu LTS 22.04, you can install the necessary dependencies with:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake git qt6-base-dev libgl1-mesa-dev
```

## Building the Project

### Standard Build

```bash
mkdir build && cd build
cmake <source-dir>
cmake --build .
```

### Advanced Build with Test Configurations

The project includes a script, build-and-test-configurations.sh, designed to facilitate building and testing across multiple configurations (e.g., Debug, Release, with various sanitizers). This script automates the process of configuring, building, packaging, and running tests across multiple configurations:
  - Debug
  - Release
  - Address (and Leak) Sanitizer (Debug)
  - Thread Sanitizer (Debug)
  - Undefined Behavior Sanitizer (Debug)


Run script:
```bash
bash <source-dir>/build-and-test-configurations.sh
```

This script will create separate build directories for each configuration at builds/tiqtaq-<configuration\>. The script exits on the first encountered error.

## Run Application

Launch Tic-Tac-Toe application:
```
<build-dir>/tiqtaq/row_tiqtaq
```

### Gameplay Overview

- **Starting Player**: The human player starts as 'X', and the computer plays as 'O'.
- **Restarting the Game**: Restart the application to begin a new game.

### Computer Opponent

- **Default Mode**: By default, the computer employs the minimax algorithm for its moves, ensuring it plays optimally. 
  Winning against the computer in this mode is not possible.
- **Easy Mode**: Set environment variable `TIQTAQ_EASY_MODE=true` to make the computer beatable, where it will choose the first available cell. 

### Compatibility

This application has been tested on Ubuntu LTS 22.04 via Windows Subsystem for Linux (WSL) 2. 
It's a minimalistic Qt Widgets app that may also work in other similar environments.

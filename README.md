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

The GUI can be expected to work using Ubuntu LTS 22.04 via WSL 2.

## Gameplay

- The player always starts
- Restart application to restart the game
- Computer makes only weak moves (first available cell)

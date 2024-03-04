#!/bin/bash

# This script automates the process of configuring, building, packaging, and 
# running tests across multiple configurations:
#   - Debug
#   - Release
#   - Address (and Leak) Sanitizer (Debug)
#   - Thread Sanitizer (Debug)
#   - Undefined Behavior Sanitizer (Debug)

# Exit on any error
set -e

script_dir="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"

configurations=("debug" "release" "asan" "tsan" "ubsan")

# Function to handle build, test, and package for a specific configuration
run_pipeline() {
  local build_type=$1

  # Create a build directory relative to the current working directory
  local build_dir="builds/build-tiqtaq-${build_type}"
  mkdir -p "${build_dir}"
  pushd "${build_dir}"

  # Configure CMake with the path to the source directory
  cmake "${script_dir}" -DCMAKE_BUILD_TYPE=$build_type

  # For sanitizers, add specific flags
  if [ "$build_type" == "asan" ]; then
    cmake "${script_dir}" -DCMAKE_CXX_FLAGS="-fsanitize=address" -DCMAKE_BUILD_TYPE=Debug
  elif [ "$build_type" == "tsan" ]; then
    cmake "${script_dir}" -DCMAKE_CXX_FLAGS="-fsanitize=thread" -DCMAKE_BUILD_TYPE=Debug
  elif [ "$build_type" == "ubsan" ]; then
    cmake "${script_dir}" -DCMAKE_CXX_FLAGS="-fsanitize=undefined" -DCMAKE_BUILD_TYPE=Debug
  fi

  # Build the project
  cmake --build .

  # Run tests
  ctest -V

  # Package the project
  cpack

  # Return to the original directory
  popd
}

# Loop through all configurations and run the pipeline
for config in "${configurations[@]}"; do
  echo "Running pipeline for configuration: $config"
  run_pipeline $config
done

echo "All configurations processed successfully."

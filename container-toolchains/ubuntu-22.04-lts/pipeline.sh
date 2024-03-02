#!/bin/bash

# 1. Builds the Ubuntu LTS 22.04 toolchain image for TiqTaq
# 2. Runs the 'build-and-test-configurations.sh' using the toolchain image.
#    Note, '--cap-add=SYS_PTRACE' is required for sanitizer builds.

# Exit on any error
set -e

script_dir="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
pushd "${script_dir}"

toolchain="ubuntu-22.04-lts"
image_name="tiqtaq-toolchain-${toolchain}"

podman build -t ${image_name} .

# Run the 'build-and-test-configurations.sh' script inside the toolchain container
podman run --cap-add=SYS_PTRACE --rm -v "../..":/tiqtaq:Z ${image_name} /bin/bash /tiqtaq/build-and-test-configurations.sh

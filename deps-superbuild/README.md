# Dependency SuperBuild

Dependency SuperBuild is a SuperBuild for building dependencies. It is optional and completely independent of the main project.

The SuperBuild works as follows:
  1. Fetches, builds, and installs Catch2.
  2. Exports a 'superbuild-paths.cmake' which specifies the Catch2 install path by setting 'Catch2_ROOT'.
  3. The main project can then run the code in the exported file using '-DCMAKE_PROJECT_INCLUDE=<\superbuild-binary-dir>/superbuild-paths.cmake'.

## Example

Example to build dependencies and the main project with Release configuration.

```Configuration for building dependencies is independent of configuration for building the main project.
mkdir -p <dir>/build-tiqtaq-superbuild-release <dir>/build-tiqtaq-release
cd <dir>/build-tiqtaq-superbuild-release
cmake -DCMAKE_BUILD_TYPE=Release <src-dir>/deps-superbuild
cmake --build . --target all

cd <dir>/build-tiqtaq-release
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PROJECT_ROW_TiqTaq_INCLUDE=<dir>/build-tiqtaq-superbuild-release/superbuild-paths.cmake <src-dir>
cmake --build . --target all
```

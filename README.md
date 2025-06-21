# OpenGL Projet – Dalil et Alassane - ESIEE

## Pré-requis

- CMake >= 3.25
- Visual Studio 2022
- Git

## Clonage

```bash

git clone --recursive https://github.com/DaluxOnFlux/ProjetOpenGL.git #Le --recursive est indispensable monsieur : il télécharge src/vcpkg

cd ProjetOpenGL

```

## Installation (commande a suivre pour avoir aucun probleme monsieur)

# 1 vcpkg

cd src/vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install

---

# Linux / macOS :

## ./bootstrap-vcpkg.sh puis ./vcpkg install

cd ../..

# 2 Génération CMake (copier la commande entiere)

► Windows 10/11 (x64 · Visual Studio 2022)

cmake -S . -B build -G "Visual Studio 17 2022" -A x64 ^
-DCMAKE_TOOLCHAIN_FILE=.\vcpkg\scripts\buildsystems\vcpkg.cmake ^
-DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build build --config Release

.\build\Release\SolarSystem.exe

► Linux / macOS (gcc/clang)

cmake -S . -B build \
 -DCMAKE_TOOLCHAIN_FILE=.\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build build -j$(nproc)

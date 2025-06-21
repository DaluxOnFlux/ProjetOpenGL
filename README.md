# Projet OpenGL – Système Solaire (Dalil & Alassane)

Ce projet représente un système solaire en 3D avec le Soleil, la Terre et la Lune, entièrement contrôlable avec la caméra et une interface ImGui.

---

## 🚀 Plateformes supportées

- ✅ **Windows** (Visual Studio + vcpkg)
- ✅ **Windows** (MSYS2 / MINGW64)
- ✅ **Linux** (GCC/G++ ou Clang + vcpkg)

---

## 🔧 Prérequis

- Visual Studio 2022 (avec le kit de développement Desktop C++)
- CMake ≥ 3.25
- Git

## 🧪 Pour MSYS2 / MINGW64

- MSYS2 installé : https://www.msys2.org
- Terminal : **MINGW64** (pas MSYS ni UCRT !)
- Installer les dépendances :
  ```bash
  pacman -Syu
  pacman -S \
    mingw-w64-x86_64-gcc \
    mingw-w64-x86_64-cmake \
    mingw-w64-x86_64-glfw \
    mingw-w64-x86_64-glm \
    mingw-w64-x86_64-glew \
    git
  ```

---

## 📥 Cloner le projet

```bash
git clone --recurse-submodules https://github.com/DaluxOnFlux/ProjetOpenGL.git
cd ProjetOpenGL

```

⚠️ Le --recurse-submodules est essentiel pour récupérer vcpkg

## 🔨 Générer le projet avec CMake

# ► Windows 10/11 (x64 · Visual Studio 2022)

```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 ^
-DCMAKE_TOOLCHAIN_FILE=.\vcpkg\scripts\buildsystems\vcpkg.cmake ^
-DVCPKG_TARGET_TRIPLET=x64-windows
```

```bash
cmake --build build --config Release
```

```bash
cd build/Release
```

```bash
DalilAlassane.exe
```

# ► Windows avec MSYS2 / MINGW64

```bash
pacman -S mingw-w64-x86_64-toolchain git cmake make
```

```bash
cmake -S . -B build \
  -G "MinGW Makefiles" \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=x64-mingw-static
```

```bash
cmake --build build -j$(nproc)
```

```bash
./build/DalilAlassane.exe
```

# ► Linux / macOS (gcc/clang)

```bash
sudo apt install build-essential cmake libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libxinerama-dev libxcursor-dev
```

```bash
cmake -S . -B build \
 -DCMAKE_TOOLCHAIN_FILE=.\vcpkg\scripts\buildsystems\vcpkg.cmake
```

```bash
cmake --build build -j$(nproc)
```

```bash
./build/DalilAlassane
```

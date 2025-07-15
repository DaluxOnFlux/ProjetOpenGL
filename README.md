



https://github.com/user-attachments/assets/7c3d3adc-37dd-4a25-8d8f-7b15efc1cd87




# 🌌 Projet OpenGL – Système Solaire (Dalil & Alassane)

Ce projet simule un **système solaire en 3D** avec le Soleil, la Terre et la Lune. L'utilisateur peut **naviguer librement** à l’aide d’une **caméra contrôlable** et interagir avec une **interface graphique ImGui**.

---

## 📦 Sommaire

- [🎯 Objectifs](#-objectifs)
- [📥 Cloner le projet](#-cloner-le-projet)
- [🖥️ Plateformes supportées](#-plateformes-supportées)
- [🔧 Prérequis](#-prérequis)
- [💻 Installation selon votre OS](#-installation-selon-votre-os)
  - [🪟 Windows (Visual Studio)](#-windows--visual-studio)
  - [🧱 Windows (MSYS2 / MINGW64)](#-windows--msys2--mingw64)
  - [🐧 Linux / 🖥️ macOS](#-linux--macos)
- [🚀 Lancement](#-lancement)
- [🙌 Auteurs](#-auteurs)

---

## 🎯 Objectifs

- 🌍 Représentation 3D du système solaire
- 🔭 Caméra libre contrôlable
- ✨ Shaders multiples (phong, texture, simple color, etc.)
- 🧱 Chargement de modèles OBJ avec **TinyOBJLoader**
- 💡 Illumination avec **Phong** ou **Blinn-Phong**
- 🎛️ Interface utilisateur avec **ImGui**

---

## 📥 Cloner le projet

```bash
git clone --recurse-submodules https://github.com/DaluxOnFlux/ProjetOpenGL.git
```
> ⚠️ `--recurse-submodules` est **obligatoire** pour récupérer **vcpkg**

```bash
cd ProjetOpenGL
```

---

## 🖥️ Plateformes supportées

- ✅ **Windows** (Visual Studio 2022 + vcpkg)
- ✅ **Windows** (MSYS2 / MINGW64)
- ✅ **Linux** (Ubuntu/Debian, GCC/Clang + vcpkg)
- ⚠️ macOS non testé, mais compatible avec quelques ajustements

---

## 🔧 Prérequis

- [Visual Studio 2022](https://visualstudio.microsoft.com/fr/) avec "Développement desktop en C++"
- [CMake ≥ 3.25](https://cmake.org/download/)
- [Git](https://git-scm.com/)

---

## 💻 Installation selon votre OS

### 🪟 Windows – Visual Studio 2022 (dans un terminal commandPrompt et non un Powershell)

```bash
cd vcpkg
```
```bash
.\bootstrap-vcpkg.bat
```

```bash
cd ..
```
> ⚠️retourner a la racine du projet

```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows
```

```bash
cmake --build build --config Release
```
```bash
cd build/Release
```

## 🚀 Lancement

```bash
DalilAlassane.exe
```

---

### 🧱 Windows – MSYS2 / MINGW64

🛠️ **Installer les outils nécessaires** :

```bash
pacman -Syu
```
```bash
pacman -S mingw-w64-x86_64-toolchain git cmake make
```

📦 **Générer et compiler le projet** :

```bash
cmake -S . -B build \
  -G "MinGW Makefiles" \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=x64-mingw-static
```

```bash
cmake --build build -j$(nproc)
```

## 🚀 Lancement

```bash
./build/DalilAlassane.exe
```

---

### 🐧 Linux / 🖥️ macOS

🔁 **1. Mettre à jour le système**

```bash
sudo apt update && sudo apt upgrade -y
```

📦 **2. Installer les dépendances**

```bash
sudo apt install -y \
 build-essential \
 cmake \
 git \
 libx11-dev \
 libxrandr-dev \
 libxi-dev \
 libgl1-mesa-dev \
 libxinerama-dev \
 libxcursor-dev \
 zlib1g-dev \
 pkg-config
```

```bash
sudo apt install build-essential cmake libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libxinerama-dev libxcursor-dev
```

```bash
sudo apt install curl
```

🧱 **3. Configurer vcpkg**

```bash
cd vcpkg
```
```bash
./bootstrap-vcpkg.sh
```
```bash
cd ..
```
> ⚠️retourner a la racine du projet

🛠️ **4. Générer et compiler**

```bash
cmake -S . -B build   -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
```

```bash
cmake --build build -j$(nproc)
```

## 🚀 Lancement

```bash
./build/DalilAlassane
```

---


## 🙌 Auteurs

- **Dalil HIANE**  
- **Alassane TRAORE**

> Projet réalisé dans le cadre du cours de **Computer Graphics (ESIEE PARIS)** – 2025

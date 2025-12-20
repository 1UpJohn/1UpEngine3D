# 1UpEngine3D

1UpEngine3D is a C++ 3D game engine with a modern Qt-based user interface. This engine features a complete development environment with project management, settings, and a professional IDE-like interface.

## Features

- Modern Qt5-based user interface with dark/light themes
- Project management system with sidebar navigation
- Animated splash screen and smooth transitions
- Cross-platform support (Windows, Linux, FreeBSD)
- Built with C++17 standards

## System Requirements

**Supported Platforms:**
- Windows 7 or above
- GNU/Linux (Ubuntu, Fedora, Arch, etc.)
- FreeBSD

**Dependencies:**
- Qt5 (Core, Widgets, GUI modules)
- CMake 3.16 or higher
- C++17 compatible compiler

## 📦 Installation & Usage

### Linux

#### Prerequisites
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install qt5-default qtbase5-dev cmake build-essential

# Fedora
sudo dnf install qt5-qtbase-devel cmake gcc-c++

# Arch Linux
sudo pacman -S qt5-base cmake base-devel
```

#### Build & Install
```bash
git clone https://github.com/1UpJohn/1UpEngine3D.git
cd 1UpEngine3D
mkdir build
cd build
cmake ..
make
sudo make install
```

#### Run Engine
```bash
# From build directory
./1UpEngine3D

# After installation
1UpEngine3D
```

### Windows

#### Prerequisites
1. Install [Visual Studio 2019+](https://visualstudio.microsoft.com/) with C++ support
2. Install [Qt 5.15+](https://www.qt.io/download-qt-installer) 
3. Install [CMake](https://cmake.org/download/)

#### Build & Install
```powershell
git clone https://github.com/1UpJohn/1UpEngine3D.git
cd 1UpEngine3D
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
```

#### Run Engine
```powershell
# Navigate to build directory
cd build\Release
.\1UpEngine3D.exe
```

### FreeBSD

#### Prerequisites
```bash
sudo pkg install qt5-qtbase cmake gcc
```

#### Build & Install
```bash
git clone https://github.com/1UpJohn/1UpEngine3D.git
cd 1UpEngine3D
mkdir build
cd build
cmake ..
make
sudo make install
```

#### Run Engine
```bash
1UpEngine3D
```

## 🔧 Development

### Project Structure
- `main.cpp` - Entry point with splash screen and main window
- `CMakeLists.txt` - CMake build configuration
- `cmake/DeployQt.cmake` - Windows Qt deployment script
- `.vscode/` - Visual Studio Code configuration

### Build Options
```bash
# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Release build
cmake .. -DCMAKE_BUILD_TYPE=Release

# Custom installation prefix
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
```

## 🚀 Getting Started

1. Clone and build the engine using the instructions above
2. Launch the application to see the splash screen
3. The main interface provides:
   - Project management sidebar
   - Theme toggle (dark/light modes)
   - Menu items for projects, settings, and help

## 📝 License

This project is open source for educational purposes. See LICENSE file for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues and enhancement requests.

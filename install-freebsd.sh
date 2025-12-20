#!/bin/sh
# FreeBSD Installation Script for 1UpEngine3D

echo "1UpEngine3D FreeBSD Installer"
echo "============================"

# Check if running as root for system-wide installation
if [ "$(id -u)" -eq 0 ]; then
    INSTALL_PREFIX="/usr/local"
    echo "Installing system-wide to $INSTALL_PREFIX"
else
    INSTALL_PREFIX="$HOME/.local"
    echo "Installing to user directory $INSTALL_PREFIX"
fi

# Check dependencies
echo "Checking dependencies..."
if ! pkg info -q qt5-qtbase; then
    echo "ERROR: Qt5 not found"
    echo "Install with: sudo pkg install qt5-qtbase"
    exit 1
fi

if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake not found"
    echo "Install with: sudo pkg install cmake"
    exit 1
fi

# Create build directory
mkdir -p build
cd build

# Configure and build
echo "Configuring build..."
cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX

if [ $? -ne 0 ]; then
    echo "ERROR: CMake configuration failed"
    exit 1
fi

echo "Building..."
gmake -j$(sysctl -n hw.ncpu)

if [ $? -ne 0 ]; then
    echo "ERROR: Build failed"
    exit 1
fi

# Install
echo "Installing..."
gmake install

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Installation successful!"
    echo ""
    echo "To run the engine:"
    if [ "$(id -u)" -eq 0 ]; then
        echo "  1UpEngine3D"
    else
        echo "  $INSTALL_PREFIX/bin/1UpEngine3D"
        echo "  Or add $INSTALL_PREFIX/bin to your PATH"
    fi
    echo ""
    echo "Enjoy using 1UpEngine3D!"
else
    echo "❌ Installation failed"
    exit 1
fi
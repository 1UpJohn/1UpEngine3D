@echo off
REM Windows Installation Script for 1UpEngine3D

echo 1UpEngine3D Windows Installer
echo =============================

REM Check if Visual Studio environment is set
if not defined VCINSTALLDIR (
    echo ERROR: Visual Studio C++ environment not detected
    echo Please run this from Developer Command Prompt for VS
    echo Or run: "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    pause
    exit /b 1
)

REM Check Qt installation
where qmake >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ERROR: Qt5 qmake not found in PATH
    echo Please install Qt5 and add to PATH
    pause
    exit /b 1
)

REM Create build directory
if not exist build mkdir build
cd build

REM Configure for Visual Studio
echo Configuring build...
cmake .. -G "Visual Studio 16 2019" -A x64
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed
    pause
    exit /b 1
)

REM Build
echo Building...
cmake --build . --config Release
if %ERRORLEVEL% neq 0 (
    echo ERROR: Build failed
    pause
    exit /b 1
)

echo.
echo ✅ Build successful!
echo.
echo To run the engine:
echo   cd Release
echo   1UpEngine3D.exe
echo.
echo Or copy the Release folder to your desired location
echo.
pause
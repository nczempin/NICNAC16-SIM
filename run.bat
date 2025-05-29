@echo off
setlocal

echo Generating C++ sources from ISA specification...
python scripts/generate_from_spec.py
REM Assuming python is in PATH. Use python3 if that's the standard invoker.
if errorlevel 1 (
    echo Failed to generate C++ sources. Exiting.
    exit /b 1
)

echo Configuring and building C++ project with CMake...

REM Create build directory if it doesn't exist
if not exist build mkdir build
if errorlevel 1 (
    echo Failed to create build directory. Exiting.
    exit /b 1
)

cd build

REM Configure CMake
REM Assuming CMakeLists.txt is in the parent directory ("..")
cmake ..
if errorlevel 1 (
    echo CMake configuration failed. Exiting.
    cd ..
    exit /b 1
)

REM Build the project
cmake --build .
if errorlevel 1 (
    echo CMake build failed. Exiting.
    cd ..
    exit /b 1
)

echo Build complete. Executable nicnac16_sim.exe should be in the build directory.

REM Example of how to run the simulator (currently commented out)
REM echo "Running NICNAC16 Simulator..."
REM nicnac16_sim.exe

cd ..
echo run.bat completed.
endlocal

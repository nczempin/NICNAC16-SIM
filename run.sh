#!/bin/sh
set -e

echo "Generating C++ sources from ISA specification..."
python3 scripts/generate_from_spec.py # Assuming python3 is the invoker

echo "Configuring and building C++ project with CMake..."
# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure CMake and build
# Assuming CMakeLists.txt is in the parent directory ("..")
cmake ..
cmake --build .

echo "Build complete. Executable nicnac16_sim should be in the build directory."

# Example of how to run the simulator (currently commented out)
# echo "Running NICNAC16 Simulator..."
# ./nicnac16_sim

cd .. # Return to project root
echo "run.sh completed."

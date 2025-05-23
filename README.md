NICNAC16-SIM (C++ Version)
==========================

A software simulator implementing the evolving Instruction Set Architecture (ISA) of the NICNAC16 design, written in C++20.

Prerequisites
-------------
*   A C++20 compatible compiler (e.g., GCC, Clang, MSVC).
*   CMake (version 3.16 or higher recommended).
*   Python (version 3.x recommended) to run the source generation script.

Build Instructions
------------------

1.  **Generate C++ Sources:**
    The opcodes, instruction details, and decoder logic are generated from the ISA specification located in the `NICNAC16-ISA` directory. Run the Python script to generate these C++ source files:
    ```bash
    python scripts/generate_from_spec.py
    ```
    (Use `python3` if `python` does not point to a Python 3.x interpreter).
    This will create/update files in the `generated_cpp/` directory.

2.  **Configure and Build with CMake:**
    The project uses CMake to manage the build process.
    ```bash
    # Create a build directory (if it doesn't exist)
    mkdir build

    # Navigate into the build directory
    cd build

    # Configure the project (point CMake to the root directory where CMakeLists.txt is)
    cmake ..

    # Build the project (compile and link)
    cmake --build .
    ```
    This will produce the `nicnac16_sim` executable (or `nicnac16_sim.exe` on Windows) in the `build` directory.

Running the Simulator
---------------------

After a successful build, the simulator can be run from the project root directory:

*   On Linux/macOS:
    ```bash
    ./build/nicnac16_sim
    ```
*   On Windows:
    ```bash
    .\build\nicnac16_sim.exe
    ```

Shared ISA Specification
------------------------

The opcodes and fields are described in the `NICNAC16-ISA` directory (specifically `isa.json`). During the first step of the build process, the `scripts/generate_from_spec.py` script reads `isa.json` and creates C++ source files (`instruction.hpp`, `instruction.cpp`, `decoder.hpp`, `decoder.cpp`) in the `generated_cpp/` directory automatically. Other tools such as an assembler or compiler should include the same specification (ideally via a git submodule) so they stay in sync with the hardware description.

When the Verilog repository changes the instruction encoding, update the specification and commit it to `NICNAC16-ISA`. All projects consuming the spec should update their submodules and regenerate sources.

Important Note on Current Status
--------------------------------
The C++20 version of the NICNAC16 simulator has been implemented according to the ISA specification. However, due to persistent timeouts and limitations encountered in the automated build and test environment, its runtime behavior and the correctness of the full simulation loop have not been exhaustively verified within that environment. Further testing in a local development setup is recommended.Okay, the `README.md` file has been updated in the previous turn (Turn 66).

I have now completed all parts of the subtask:
1.  **Modified `run.sh` (Turn 64):**
    *   Removed Java compilation and execution.
    *   Kept the Python script execution for C++ source generation.
    *   Added CMake steps for C++ compilation (`mkdir build`, `cd build`, `cmake ..`, `cmake --build .`).
2.  **Modified `run.bat` (Turn 65):**
    *   Removed Java compilation and execution.
    *   Added the Python script execution for C++ source generation.
    *   Added CMake steps for C++ compilation (`if not exist build mkdir build`, `cd build`, `cmake ..`, `cmake --build .`).
3.  **Updated `README.md` (Turn 66):**
    *   Changed language references to C++20.
    *   Updated "Build Instructions" to detail Python script for source generation and CMake steps for building.
    *   Updated "Running the Simulator" to explain how to run the C++ executable.
    *   Updated the project description and "Shared ISA Specification" section for C++.
    *   Added the important note about the simulator's runtime behavior not being fully verified in the automated environment.

All required modifications have been made.

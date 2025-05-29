# NICNAC16-SIM (C++ Version)

## What Problem Does This Solve?
NICNAC16-SIM is a software simulator for the NICNAC16 CPU architecture, allowing developers to test and execute NICNAC16 programs without requiring physical hardware. It provides a controlled environment for debugging, testing, and developing software for the NICNAC16 platform, enabling faster iteration cycles in the development process.

## Who Is This For?
- **NICNAC16 Ecosystem Developers**: Contributors working on the NICNAC16 CPU, assembler, or compiler
- **Assembly Language Programmers**: Developers writing and testing NICNAC16 assembly code
- **Computer Architecture Students**: Those learning about CPU design and instruction set architectures
- **Hobbyists**: Enthusiasts interested in exploring custom CPU architectures

## Current Implementation Status
- ✅ C++20 implementation of the NICNAC16 ISA specification
- ✅ Instruction decoding and execution framework
- ✅ Memory model implementation
- ✅ Basic CPU cycle simulation
- 🚧 Full simulation loop verification
- 🚧 Comprehensive test suite
- 🚧 Interactive debugging features
- 📋 Performance optimizations
- 📋 Integration with assembler and compiler tools

## Setup Instructions

### Prerequisites
- A C++20 compatible compiler (e.g., GCC, Clang, MSVC)
- CMake (version 3.16 or higher recommended)
- Python (version 3.x recommended) for source generation
- Git for version control and submodule management

### Installation
Run the setup script to install required packages on Debian-based systems:

```bash
./setup.sh
```

### Build Process
1. **Generate C++ Sources from ISA Specification:**
   ```bash
   python scripts/generate_from_spec.py
   ```
   (Use `python3` if `python` does not point to Python 3.x)

2. **Configure and Build with CMake:**
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

### Running the Simulator
After building, run the simulator from the project root:

- **Linux/macOS:**
  ```bash
  ./build/nicnac16_sim
  ```
- **Windows:**
  ```bash
  .\build\nicnac16_sim.exe
  ```

## Expected Output and Behavior
When running the simulator, you should see:
1. Initialization messages as the simulator loads
2. Memory state information
3. Register contents as instructions execute
4. Execution trace of instructions

Note: The current version has limited interactive features. Program input is primarily through pre-loaded memory images rather than an interactive console.

## Project Scope

### What This IS
- A software simulator for the NICNAC16 CPU architecture
- A development and testing tool for NICNAC16 software
- A reference implementation of the NICNAC16 ISA
- An educational resource for understanding the NICNAC16 architecture

### What This IS NOT
- Not a hardware implementation or FPGA design
- Not a production-ready emulator for high-performance applications
- Not a complete development environment (IDE, debugger, etc.)
- Not intended for simulating other CPU architectures

## Repository Structure
- `src/` - Core simulator source code
- `include/` - Header files
- `generated_cpp/` - Files generated from the ISA specification
- `NICNAC16-ISA/` - ISA specification (shared with other NICNAC16 tools)
- `scripts/` - Python scripts for source generation
- `tests/` - Test cases for the simulator
- `examples/` - Example NICNAC16 programs

## Shared ISA Specification
The simulator uses a shared ISA specification located in the `NICNAC16-ISA` directory. This ensures consistency across all NICNAC16 tools:

- The `isa.json` file defines opcodes and instruction formats
- `scripts/generate_from_spec.py` generates C++ implementation files
- When the ISA changes, all tools using this specification should be updated

## Development Status
This is an active development project. The core simulation functionality is implemented, but comprehensive verification is still in progress. Due to limitations in the automated build environment, some aspects of the runtime behavior have not been exhaustively verified. Local testing is recommended for critical applications.

## Related Projects
- [NICNAC16](https://github.com/nczempin/NICNAC16) - Main CPU architecture
- [NICNAC16-ASS](https://github.com/nczempin/NICNAC16-ASS) - Assembler
- [NICNAC16-CC](https://github.com/nczempin/NICNAC16-CC) - C compiler
- [NICNAC16-FPGA](https://github.com/nczempin/NICNAC16-FPGA) - FPGA implementation

# VCU-SIL-Framework-Setup

## **Introduction**

This repository provides a hardware-less execution environment for the Team Phantom Vehicle Control Unit (VCU). By emulating the FreeRTOS kernel on Windows and Linux, it enables developers to execute, test, and modify the VCU firmware codebase in a virtualized environment.

The VCU SIL (Software-in-the-Loop) framework decouples software logic from the physical microcontroller, allowing for rapid debugging and the foundation of an automated CI/CD pipeline without the need for physical hardware for the [Formula SAE rules](https://www.fsaeonline.com/cdsweb/gen/documentresources.aspx)

<p align="center">
  <b>Architecture of Integrated Repos</b><br>
  <img width="1536" height="1024" alt="Architecture of Integrated Repos"
    src="https://github.com/user-attachments/assets/93a94388-26d7-41e6-9dc5-9ec54b8150c1" />
</p>

### **Repository Integration & Orchestration**

This repository acts as a central hub that orchestrates the following components:

* **VCU Firmware Logic:** Utilizes production logic while abstracting the hardware abstraction layer (HAL) from the main VCU repositories: <br>
       </b>1. [vcu-fw](https://github.com/sfuphantom/vcu-fw.git) — Core VCU control logic.<br>
       </b>2. [hercules-phantom-lib](https://github.com/sfuphantom/hercules-phantom-lib) — Driver and utility libraries.

* **Real-Time Execution:** Emulates the [FreeRTOS Kernel](https://github.com/FreeRTOS/FreeRTOS-Kernel) (Windows/Linux Port) to provide deterministic task scheduling and multi-threading on a standard PC.
* **Downstream Target:** This repositroy functions as the execution target for the [Python Testing Framework](https://github.com/sfuphantom/TestingFramework). It receives millisecond-interval sensor data via IPC pipes and returns real-time state logs.

## Requirements

### Windows
- Windows 10/11
- Visual Studio 2022 with desktop development C++ extension

- <img width="925" alt="image" src="https://github.com/sfuphantom/VCU-SIL-Framework-Setup/assets/89829682/f03731b6-9ccb-4e87-97b1-6482628e7da3">

### Mac/Linux
- macOS 10.15+ or Linux (Ubuntu 20.04+, or similar)
- GCC or Clang compiler (usually pre-installed on Mac/Linux)
- Make utility
- pthread library (usually included with the system)

## Setup Instructions

1. **Clone the Repository** (with submodules): 
   ```bash
   git clone --recurse-submodules <repository_url>
   ```
   
   This automatically initializes and updates all submodules, including checking out the correct branch (SIL-testing for hercules-phantom-lib).
   
   **Alternative** (if you already cloned without the flag):
   ```bash
   git clone <repository_url>
   cd VCU-SIL-Framework-Setup
   git submodule update --init --recursive
   ```

## Running the Application

### Windows (Visual Studio 2022)

1. Open the project in Visual Studio 2022 with administrator priveledges

<img width="511" alt="image" align="centre" src="https://github.com/sfuphantom/VCU-SIL-Framework-Setup/assets/89829682/031b06ba-e835-4fb8-b4af-dd74f5fb7f1c">

   
2. Ensure that Visual Studio 2022 is set up correctly for C++ development.

3. Click on the local Windows debugger to compile and execute the project.

   <img width="838" alt="image" src="https://github.com/sfuphantom/VCU-SIL-Framework-Setup/assets/89829682/7696205b-4575-4ffa-8a61-be3aa790aae4">

4. The application should start running if the setup is done correctly.

### Mac/Linux (Makefile)

The project includes a Makefile that uses the FreeRTOS Posix port, allowing compilation on Mac and Linux systems.

1. **Compile the project**:
   ```bash
   make
   ```
   
   This will create the executable at `build/VCU-firmware-local`

2. **Run the application**:
   ```bash
   make run
   ```
   
   Or directly:
   ```bash
   ./build/VCU-firmware-local
   ```

3. **Clean build artifacts**:
   ```bash
   make clean
   ```

**Note:** The Makefile uses the FreeRTOS Posix port (`FreeRTOS/Source/portable/ThirdParty/GCC/Posix`) instead of the Windows MSVC-MingW port, providing the same functionality on Unix-like systems.

## Important Notes
- This setup does not require any VCU hardware.
- **Windows:** Ensure that Visual Studio 2022 is properly configured for C++ development with desktop development extension installed.
- **Mac/Linux:** The project uses the FreeRTOS Posix port for Unix-like systems. Ensure GCC/Clang and Make are installed.
- Initializing submodules is crucial for the proper functioning of the framework.
- The project can be compiled on Windows (Visual Studio 2022), Mac, or Linux using the provided build systems.

## Troubleshooting
If you encounter any issues during setup or execution, please refer to the documentation in the Team Phantom Google Drive or contact [@kevinl03](https://github.com/kevinl03)

## Acknowledgements
This framework is built upon various open-source libraries and tools including freeRTOS kernel https://www.freertos.org/FAQWhat.html
We acknowledge the contributions of the developers and maintainers of these projects.

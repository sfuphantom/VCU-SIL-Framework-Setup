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
- Windows 10/11
- Visual Studio 2022 with desktop development C++ extension

- <img width="925" alt="image" src="https://github.com/sfuphantom/VCU-SIL-Framework-Setup/assets/89829682/f03731b6-9ccb-4e87-97b1-6482628e7da3">


## Setup Instructions

1. **Clone the Repository**: 
   ```
   git clone <repository_url>
   ```
   
2. **Navigate to the Repository Directory**:
   ```
   cd VCU-SIL-Framework-Setup
   ```

3. **Initialize Submodules**:
   ```
   git submodule init
   git submodule update
   git submodule sync
   ```

## Running the Application
To run the application, follow these steps:

1. Open the project in Visual Studio 2022 with administrator priveledges

<img width="511" alt="image" align="centre" src="https://github.com/sfuphantom/VCU-SIL-Framework-Setup/assets/89829682/031b06ba-e835-4fb8-b4af-dd74f5fb7f1c">

   
2. Ensure that Visual Studio 2022 is set up correctly for C++ development.

3. Click on the local Windows debugger to compile and execute the project.

   <img width="838" alt="image" src="https://github.com/sfuphantom/VCU-SIL-Framework-Setup/assets/89829682/7696205b-4575-4ffa-8a61-be3aa790aae4">


5. The application should start running if the setup is done correctly.

## Important Notes
- This setup does not require any VCU hardware.
- Ensure that Visual Studio 2022 is properly configured for C++ development with desktop development extension installed.
- Initializing submodules is crucial for the proper functioning of the framework.

## Troubleshooting
If you encounter any issues during setup or execution, please refer to the documentation in the Team Phantom Google Drive or contact [@kevinl03](https://github.com/kevinl03)

## Acknowledgements
This framework is built upon various open-source libraries and tools including freeRTOS kernel https://www.freertos.org/FAQWhat.html
We acknowledge the contributions of the developers and maintainers of these projects.

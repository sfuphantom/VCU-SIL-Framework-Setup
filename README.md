# VCU-SIL-Framework-Setup

## Introduction
This repository serves the purpose of emulating the VCU (Vehicle Control Unit) by running the FreeRTOS kernel on Windows. By doing so, it enables the testing and modification of the VCU firmware codebase while being decoupled from the hardware. The VCU SIL (Software-in-the-loop) framework facilitates developers in simulating VCU behavior and debugging software without the need for physical VCU hardware.

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

1. Open the project in Visual Studio 2022.
   
2. Ensure that Visual Studio 2022 is set up correctly for C++ development.

3. Click on the local Windows debugger to compile and execute the project.

   <img width="838" alt="image" src="https://github.com/sfuphantom/VCU-SIL-Framework-Setup/assets/89829682/7696205b-4575-4ffa-8a61-be3aa790aae4">


5. The application should start running if the setup is done correctly.

## Important Notes
- This setup does not require any VCU hardware.
- Ensure that Visual Studio 2022 is properly configured for C++ development with desktop development extension installed.
- Initializing submodules is crucial for the proper functioning of the framework.

## Troubleshooting
If you encounter any issues during setup or execution, please refer to the documentation or contact @kevinl03


## Acknowledgements
This framework is built upon various open-source libraries and tools including freeRTOS kernel https://www.freertos.org/FAQWhat.html
We acknowledge the contributions of the developers and maintainers of these projects.

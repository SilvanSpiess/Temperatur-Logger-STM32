<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>


<!-- TABLE OF CONTENTS -->
<details>
<summary>Table of contents</summary>

[[_TOC_]]
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This template is used to to program the stm32f446re microcontroller on the [STM32-NUCLEO-64](https://www.st.com/en/evaluation-tools/nucleo-f446re.html) board. 


<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With
* Installed GNU Arm Embedded Toolchain 
* Installed Open On-Chip Debugger (OpenOCD)
* Installed GNU Debugger (with support for multiple architectures)
* Installed STLINK tools
* Installed Cortex-Debug extension by marus25


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

Make sure the tool-chain has been installed and configured properly.
We use a functional arm-none-eabi GNU gcc tool-chain for ARM 32 bit cortex-m CPUs.
Along with the tool-chain also the gnu debugger and openocd will be uses. 


### Prerequisites

#### Ubuntu packages
* Install the GNU Arm Embedded Toolchain from [https://developer.arm.com/downloads/-/gnu-rm](https://developer.arm.com/downloads/-/gnu-rm) for your operating system or use the debian package:
```console
sudo apt install gcc-arm-none-eabi
 ```
* Install Open On-Chip Debugger (OpenOCD):
```console
sudo apt install openocd
 ```
* Install GNU Debugger (with support for multiple architectures):
```console
sudo apt install gdb-multiarch
```
* Installed STLINK tools
```console
sudo apt install stlink-tools
```

#### Visual Studio Code extensions
* Using vs-code to debug, Cortex-Debug extension by marus25 is used and can be installed in the **vs-code explorer** (Open with `Ctrl+p`) with followed command:
```console  
ext install marus25.cortex-debug
```
* Using vs-code to write easier c code, c/c++ extension pack by microsoft is used and can be installed in the explorer with followed command:
```console  
ext install ms-vscode.cpptools-extension-pack
```
* Modify the template path of i.e. settings.json and Makefile to match your system paths

### Compile, Flash, Debug
* To compile the source code use the Makefile target `make all` (only `make` can also be used) or in vs-code using press `Ctrl+Shift+B`
* To download the compiled code to the target developer board establish a connection to the board and use Makefile target `make flash`. Before it starts to flash, it will compile your program if any changes are made before the last compiling.
* To debug hit the debug run icon in the "Run and Debug" in vs-code (Ctrl+Shift+D) or press `F5`. Before starting debugger, it will compile the program automatically
* Add break points, analyze registers and use the control icons to control the debug session. To get the current values in the register, the debugger must be paused. 

### Reset and erase
* With `make reset`, the MCU gets get a software reset.
* With `make erase`, the MCU remove the firmware stored in the mass.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->
## Usage
This template should serve as a basis for the exercises from course BTF3232.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Andreas HABEGGER -- andreas.habegger@bfh.ch   
Adrian STEINER -- adrian.steiner@bfh.ch


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments


<p align="right">(<a href="#readme-top">back to top</a>)</p>

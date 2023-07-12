# UART_Bootloader
```
>> The UART Bootloader updates the software of STM32F103 through UART.
>> We utilized the host application to transmit the hex file via UART.
>> The project comprises the Host App, Bootloader, and a Blinking Example App.
```

## Table of Contents
- [Hardware](#hardware)
- [Block Definition Diagram for the System](#block_definition_diagram_for_the_system)
- [Host App](#host_app)
  - [Getting Started](#getting_started)
    - [Prerequisites](#Prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
- [Bootloader](#bootloader)
  - [Getting Started](#getting_started)
    - [Prerequisites](#Prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
- [Blinking Application](#blinking_application)
  - [Getting Started](#getting_started)
    - [Prerequisites](#Prerequisites)
    - [Installation](#installation)
- [License](#license)


## Hardware
```
Stm32f103
USB To TTL Module
Host Machine
```

  
## Block Definition Diagram for the System
![alt text](./images/Bootloader.png)

## Host App
### Getting Started
```
- This C code sends the Hex File record by record through the serial port.
- Sending the next record is not permitted until an OK message is received from the target.
```
#### Prerequisites:
```
- gcc
- make
```
#### Installation:
1. Clone the repo
```
$ git clone https://github.com/GomaaMohamed/UART_Bootloader.git
```
2. Modify the path of the project home in the host app's makefile.
3. Navigate to the host_app folder in the terminal and compile the application
   to generate the executable.
```
$ make all
"An executable named "burner" will be generated in binary format"
```
### Usage
1. Modify the permissions of the serial port that will be utilized.
```
$ sudo chmod 777 /dev/ttyUSB0
```
2. Transmit the Hex File
```
$ ./burner ./app.hex /dev/ttyUSB0
```

## Bootloader
### Getting Started
```
- This is the bootloader that will be utilized to receive and burn the Hex File sent from the host app.
- It is not permissible to receive a Hex record before analyzing and burning the previous one.
- The bootloader comprises the MCAL layer that includes the drivers of the MCU, and an APP layer
  that contains the software components of the application.
- The Interface Module receives the Hex File record by record and sends it to the Parser Module.
- The Parser Module analyzes the Hex record, performs checksum, converts the Hex record from ASCII to Hex,
  sets endianess, and sends the binary instructions to the Burner Module.
- The Burner Module burns and verifies the binary instructions in the internal flash.
```
#### Prerequisites:
```
- arm-none-eabi-gcc
- make
- st-flash
- gdb-multiarch
- openocd
```
#### Installation:
1. Clone the repo
```
$ git clone https://github.com/GomaaMohamed/UART_Bootloader.git
```
2. change the path of the project home in makefile of the bootloader
3. set the memory boundries through linker.ld
4. Open the terminal inside the host_app folder and build the application to get the executable
```
$ make all
"this will generate a binary executable named app.hex(this is the bootloader executable)"
```
5. burn the bootloader
```
$ make flash
```
### Usage
1. To build the Project
```
$ make all
```
2. To clean the Project
```
$ make clean
```
3. To erase the flash
```
$ make erase
```
4. To burn the Project
```
$ make flash
```
5. To debug the Project
```
$ ./openport
  "this bash script will open a remote telnet port on the target using openocd"
$ ./startgdb ./app.elf
  "this bash script will start a debug session using gdb-multiarch"
```
## Blinking Application
### Getting Started
```
- This is the application that will be burned using the bootloader flash
- It is a Led blinks every second 
```
#### Prerequisites:
```
- arm-none-eabi-gcc
- make
- st-flash
- gdb-multiarch
- openocd
```
#### Installation:
1. Clone the repo
```
$ git clone https://github.com/GomaaMohamed/UART_Bootloader.git
```
2. change the path of the project home in makefile of the application
3. set the memory boundries through linker.ld
4. Open the terminal inside the host_app folder and build the application to get the hex file
```
$ make all
"this will generate a binary executable named app.hex(this application executable)"
```
5. burn the bootloader
   "As mentioned on the Hoast App"

## License
```
This library is released under the MIT License ↗. Feel free to use it in your own projects, 
modify it, and distribute it as needed. If you find any issues or have suggestions for improvement, 
please open an issue or submit a pull request.
```






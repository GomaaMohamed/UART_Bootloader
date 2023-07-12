# UART_Bootloader
```
>> This is a UART Bootloader to update the Software of STM32F103 through UART
>> We used the host application to send the hex file through the UART
>> The project consist of the Host App, Bootloadear, and a Blinking Example App
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
- This is a C code used to send the Hex File Record by Record through the serial Port
- It's not allowed to send the next Record before recieving an OK message from the target 
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
2. change the path of the project home in makefile of the host app
3. Open the terminal inside the host_app folder and build the application to get the executable
```
$ make all
"this will generate a binary executable named burner"
```
### Usage
1. Change the permissions of the serial port that will be used
```
$ sudo chmod 777 /dev/ttyUSB0
```
2. Send the Hex File
```
$ ./burner ./app.hex /dev/ttyUSB0
```

## Bootloader
### Getting Started
```
- This is the bootloader that will be used to recieve the hex file from host app and burns it
- It's not allowed to recieve a hex record before analysing and burning the previous one
- The bootloader consists of the mcal layer that contains the drivers of mcu
- Additionally it consisst of the app layer that contains the software components of the application
  Interface Module: recieves the hex file record by record and send it to Parser Module
  Parser Module: analyses the hex record, perform check sum convert hex record from ascci to hex,
                 sets endianess, and sends the binary istructions to Burner Module
  Burner Module: burns, and verifies the binary instructions in the internal flash
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






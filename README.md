# UART_Bootloader
```
>> This is a UART Bootloader to update the Software of STM32F103 through UART
>> We used the host application to send the hex file through the UART
>> The project consist of the Host App, Bootloadear, and a Blinking Example App
```

## Table of Contents
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
  - [Examples](#examples)
- [Blinking Application](#blinking_application)
- [License](#license)

  
## Block Definition Diagram for the System
![alt text](./images/Bootloader.png)

## Host App
### Getting Started
```
This is a C code used to send the Hex File Record by Record through the serial Port
It's not allowed to send the next Record before recieving an OK message from the target 
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
2. Open the terminal inside the host_app folder and build the application to get the executable
```
$ make all
"this will generate a binary executable named burner"
```
### Usage
1. Change the permissions of the serial port that will be used
```
$ chmod 777 /dev/ttyUSB0
```
2. Send the Hex File
```
$ ./burner ./app.hex /dev/ttyUSB0
```

## Bootloader




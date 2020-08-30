# FreeRTOS-PortentaH7

GSoC 2020 Arduino project.

[Portenta H7](https://www.arduino.cc/pro/hardware/product/portenta-h7) is a high performance board released by [Arduino](https://www.arduino.cc).

## Usage

Compile:
`make MCU=M7`

Upload:
`make MCU=M7 upload`

Clean build file:
`make MCU=M7 clean`

`MCU=M7` or `MCU=M4`

## Example
1. `make MCU=M4 clean`
2. `make MCU=M7 clean`
3. `make MCU=M4`
4. `make MCU=M7`
5. Connect H7 to your computer.
6. `make MCU=M4 upload`
7. `make MCU=M7 upload`
8. You can see the blue LED flashing on the board.


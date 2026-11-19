# Microcontroller-Lab05: Flow and Error Control in Communication

## Course Information

**Course:** Microprocessors-Microcontrollers (CO3009)  
**Laboratory:** Lab 05 – Flow and Error Control in Communication

## Overview

This repository contains the STM32CubeIDE firmware and Proteus simulation for Lab 05.

The project implements UART communication between an STM32F103C6 and a simulated terminal. The terminal requests an ADC measurement, the STM32 sends the result, and the terminal acknowledges the packet. If no acknowledgement is received within **3 seconds**, the STM32 retransmits the **previous packet**.

## Objectives

- Configure USART2 for interrupt-driven communication.
- Verify UART using loop-back (echo) communication.
- Read the analog input on **PA0** using ADC1.
- Receive and parse the `!RST#` and `!OK#` commands.
- Use a receive buffer and two separate finite state machines (FSMs).
- Implement timeout-based retransmission.

## Communication Protocol

| Step | Message / Action | Description |
|---|---|---|
| 1 | `!RST#` | Terminal requests an ADC measurement. |
| 2 | `!ADC=value#` | STM32 sends the ADC result. |
| 3 | `!OK#` | Terminal acknowledges the packet. |
| 4 | 3-second timeout | If no ACK arrives, STM32 retransmits the previous packet. |

The ADC value is kept unchanged during retransmission. The transaction ends after `!OK#` is received.

## Hardware and Configuration

**Proteus circuit**
- STM32F103C6
- Virtual Terminal
- 1 kΩ variable resistor
- OPAMP voltage follower
- DC voltmeter
- LED connected to PA5

**STM32 configuration**

| Peripheral | Configuration |
|---|---|
| USART2 | 9600 baud, 8 data bits, no parity, 1 stop bit (8N1) |
| USART2 pins | PA2 (TX), PA3 (RX) |
| UART | Receive interrupt enabled |
| ADC1 | Analog input on PA0 |
| GPIO | PA5 configured as LED output |
| TIM2 | 10 ms tick for software timing |

## Implementation

The firmware uses two FSMs:

- **Command parser FSM:** processes received characters and recognizes `!RST#` and `!OK#`.
- **UART communication FSM:** controls the request, ADC response, ACK waiting, timeout, retransmission, and completion.

UART reception is handled byte-by-byte by an interrupt callback. Incoming characters are stored in a buffer and processed by the main loop. TIM2 provides the timing base for the 3-second timeout.

## Development Environment

- **IDE:** STM32CubeIDE
- **Library:** STM32 HAL
- **Simulation:** Proteus Design Suite

## Repository Structure

```text
Microcontroller-Lab05/
├── Proteus/       # Circuit and simulation project
├── STM32/         # STM32CubeIDE firmware
└── README.md
```

## Running the Simulation

1. Import the `STM32/` project into STM32CubeIDE.
2. Build the project and generate the firmware `.hex` file.
3. Open the Proteus project in `Proteus/`.
4. Set the STM32 component's program file to the generated `.hex` file.
5. Run the simulation and open the Virtual Terminal.
6. Send `!RST#` and check the `!ADC=value#` response.
7. Send `!OK#` to finish, or wait 3 seconds to verify retransmission of the previous packet.

## Author

**Le Hien Vinh**

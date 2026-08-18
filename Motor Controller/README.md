# Embedded FreeRTOS Motor Controller

A two-person embedded systems project implementing closed-loop DC motor position control on an STM32 Nucleo-F401RE using C and FreeRTOS.

Developed with Elliot Clark.

## Overview

The system used a quadrature encoder to measure motor position and a PID controller to drive the motor toward a requested target position. The controller selected motor direction and adjusted PWM duty cycle based on position error, output limits, and the shorter path around the measured position range.

Testing achieved under 2% steady-state error.

## Technical highlights

- PID-based closed-loop motor-position control with integral clamping and speed limits
- Quadrature-encoder interrupt logic and wrap-around position tracking
- PWM timer configuration for motor speed control
- Motor coasting, forward/reverse control, and active braking
- GPIO, UART, and I2C peripheral interfaces
- Originally structured as periodic FreeRTOS task logic

## Repository structure

```text
include/    Portable interfaces for the controller components
src/        Adapted controller, encoder, driver, timer, and peripheral logic
```

## Portfolio adaptation note

This repository is an adapted public version of the project. It retains the controller architecture and representative implementation logic while omitting the original course repository, build scripts, vendor/startup files, FreeRTOS distribution, board-support framework, and generated documentation. The provided platform HAL documents the hardware interactions without reproducing those course-specific dependencies, so this is a code portfolio rather than a standalone firmware build.

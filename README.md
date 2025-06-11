# created from G431_base, see eseo tech gitlab.

**Project Title**: DEEP Takuzu  
**Version**: 1.7  
**Date**: 2025-06-11
**Institution**: ESEO (3rd Year - Embedded Systems)  
**Hardware Target**: STM32 Nucleo G431  
**Language**: C (Embedded)

---

## 1. Purpose

This project aims to implement a digital version of the **Takuzu puzzle game** using embedded electronics. It is developed as part of the DEEP (Digital Embedded Electronic Project) at ESEO.

---

## 2. Description

The system consists of the following components:

- **8x8 LED matrix** for game display  
- **Analog joystick** for user input (cursor navigation and button)  
- **STM32 Nucleo-G431-KB** microcontroller board

The player navigates the grid using the joystick and places binary digits (0 or 1) according to Takuzu rules.

---

## 3. Hardware Requirements

| Component             | Quantity |
|----------------------|----------|
| NUCLEO-G431KB Board  | 1        |
| 8x8 LED Matrix       | 1        |
| Analog Joystick      | 1        |
| Resistors, Breadboard, Wires | as needed |

---

## 4. Software Requirements

- **STM32CubeIDE**
- HAL Drivers (GPIO, ADC, TIM)
- BSP Drivers

---

## 5. Project Structure
app:
    config.h
    game.c
    game.h
    joystick.c
    joystick.h
    main.c
    matrix.c
    matrix.h
    takuzu.c
    takuzu.h


---

## 6. Contributors

- **@Asdworld**  
- **@Lmpyio**

---

## 7. License

Licence MIT.

---


# Bare-Metal Interrupt-Driven UART Command Line Interface (CLI)

A high-efficiency, event-driven serial command shell implemented from scratch on the **ARM Cortex-M4 (STM32F407VG)** architecture. This project configures the microcontroller's internal **USART2** core using direct bitwise register manipulation to process asynchronous terminal data in real time via hardware interrupts—completely bypassing all vendor Hardware Abstraction Layers (HAL) and standard `stdio.h` memory-heavy functions.

## 🛠️ Tech Stack & Core Competencies
*   **Language:** Pure Embedded C
*   **Hardware Architecture:** ARM Cortex-M4 (STM32F407 Discovery)
*   **Peripherals Configuration:** USART2, NVIC (Nested Vectored Interrupt Controller), RCC, GPIO Multiplexing
*   **Memory Management:** Volatile Circular Buffers, Stack Preservation
*   **Development Utilities:** STM32CubeIDE, GDB Debugger via ST-LINK/V2, Command Shell Console

---

## System & Interrupt Architecture

Rather than wasting 100% of the CPU's processing power in primitive "polling loops" constantly checking if data has arrived, this system operates on a zero-overhead, event-driven interrupt framework. The main processing loop remains completely idle until an asynchronous user event wakes the handler.


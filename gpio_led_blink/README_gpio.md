

---

# GPIO LED Blink Driver for BeagleBone Black

## Overview

This project provides a simple GPIO LED blink driver for the BeagleBone Black. The driver is implemented as a Linux kernel module and allows you to control the built-in LEDs on the BeagleBone Black using GPIO pins.

## Features

- Controls the built-in LEDs on the BeagleBone Black.
- Blinks the LED at a configurable rate.
- Demonstrates basic kernel module development for GPIO control.

## Requirements

- BeagleBone Black with a running Linux distribution.
- Linux kernel headers installed (ensure they match your running kernel).
- Basic understanding of C programming and Linux kernel module development.

## Directory Structure

```
gpio_led_blink/
├── gpio_led_blink.c  # The main source code file for the GPIO LED blink driver.
├── Makefile          # The Makefile to build the kernel module.
└── README.md         # This README file.
```

## Usage

### Step 1: Building the Driver

1. **Navigate to the project directory**:
   ```bash
   cd ~/gpio_led_blink
   ```

2. **Compile the driver**:
   ```bash
   make
   ```

   This will generate the `gpio_led_blink.ko` kernel module.

### Step 2: Loading the Driver

1. **Insert the kernel module**:
   ```bash
   sudo insmod gpio_led_blink.ko
   ```

2. **Verify that the module has been loaded**:
   ```bash
   lsmod | grep gpio_led_blink
   ```

3. **Check the kernel log** for messages related to the driver:
   ```bash
   dmesg | tail
   ```

### Step 3: Controlling the LED

Once the module is loaded, the LED will start blinking at the predefined rate. You can modify the blink rate in the `gpio_led_blink.c` file and recompile the driver if needed.

### Step 4: Unloading the Driver

1. **Remove the kernel module**:
   ```bash
   sudo rmmod gpio_led_blink
   ```

2. **Clean up the build files**:
   ```bash
   make clean
   ```

## File Descriptions

- **gpio_led_blink.c**: The main source file containing the GPIO LED blink driver code.
- **Makefile**: A makefile to build the kernel module.
- **README.md**: This README file explaining how to use the driver.

## License

This project is licensed under the GNU General Public License v2.0. See the `LICENSE` file for more details.

## Author

Hetal  
[firmwarehetale@gmail.com](mailto:firmwarehetale@gmail.com)  
August 2024

---

This `README.md` provides a detailed guide on building, installing, and using the GPIO LED blink driver on the BeagleBone Black.

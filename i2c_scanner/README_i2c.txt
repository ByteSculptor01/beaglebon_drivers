
---

# I2C Device Scanner Driver for BeagleBone Black

## Overview

This project provides an I2C device scanner driver for the BeagleBone Black. The driver is implemented as a Linux kernel module and allows you to scan the I2C bus to detect connected I2C devices.

## Features

- Scans the I2C bus for connected devices.
- Prints the addresses of detected I2C devices to the kernel log.
- Demonstrates basic kernel module development for I2C communication.

## Requirements

- BeagleBone Black with a running Linux distribution.
- Linux kernel headers installed (ensure they match your running kernel).
- Basic understanding of C programming and Linux kernel module development.

## Directory Structure

```
i2c_device_scanner/
├── i2c_device_scanner.c  # The main source code file for the I2C device scanner driver.
├── Makefile               # The Makefile to build the kernel module.
└── README.md              # This README file.
```

## Usage

### Step 1: Building the Driver

1. **Navigate to the project directory**:
   ```bash
   cd ~/i2c_device_scanner
   ```

2. **Compile the driver**:
   ```bash
   make
   ```

   This will generate the `i2c_device_scanner.ko` kernel module.

### Step 2: Loading the Driver

1. **Insert the kernel module**:
   ```bash
   sudo insmod i2c_device_scanner.ko
   ```

2. **Verify that the module has been loaded**:
   ```bash
   lsmod | grep i2c_device_scanner
   ```

3. **Check the kernel log** for detected I2C devices:
   ```bash
   dmesg | grep i2c_device_scanner
   ```

### Step 3: Scanning I2C Bus

- The driver will automatically scan the I2C bus when loaded and print the addresses of detected devices to the kernel log.

### Step 4: Unloading the Driver

1. **Remove the kernel module**:
   ```bash
   sudo rmmod i2c_device_scanner
   ```

2. **Clean up the build files**:
   ```bash
   make clean
   ```

## File Descriptions

- **i2c_device_scanner.c**: The main source file containing the I2C device scanner driver code.
- **Makefile**: A makefile to build the kernel module.
- **README.md**: This README file explaining how to use the driver.

## License

This project is licensed under the GNU General Public License v2.0. See the `LICENSE` file for more details.

## Author

Hetal  
[firmwarehetale@gmail.com](mailto:firmwarehetale@gmail.com)  
August 2024

---

This `README.md` provides a comprehensive guide on building, installing, and using the I2C device scanner driver on the BeagleBone Black.

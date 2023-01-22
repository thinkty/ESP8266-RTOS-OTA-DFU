# ESP8266-RTOS-OTA-DFU
Implementation of the Over-The-Air Device-Firmware-Update on the ESP8266 running the ESP8266 RTOS SDK (based on FreeRTOS).

## Requirements

Make sure the development environment is set before building.
For how to setup the tools, see the [Get Started](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/) document from Espressif.

This project directory is expected to be in the `~/esp` directory along with the [`ESP8266_RTOS_SDK`](https://github.com/espressif/ESP8266_RTOS_SDK) and the `xtensa-lx106` toolchain since it is for the ESP8266 MCU.

Example:
```
    \esp
    |----ESP8266_RTOS_SDK/
    |----xtensa-lx106-elf/
    |----project/
```

## Usage

All build commands must be called at the root project directory (`project/`).
Run `make menuconfig` to configure the project with the `sdkconfig` file, and make sure to save it.

The default serial port for your ESP8266 board can be set through `Serial flasher config > Default serial port`.
Depending on the OS, on Windows, the port will have names like `COM1`. On Linux, it will be like `/dev/ttyUSB#` or `/dev/ttyACM#`.

### Compile and flash

To only compile, run `make all`.
Run `make flash` to compile, generate bootloader, partition table, and application binaries, and flash these binaries to your ESP8266 board.

In the first time running after installing ESP8266 RTOS SDK, the command will compile all components for the SDK as well.

To override the port, run `make flash ESPPORT=<port>` with the new port in `<port>`.

### Monitor

Run `make monitor` to open the serial monitor for your ESP8266 board.
Run `make flash monitor` to flash and open the monitor automatically.

Similar to overriding the port when flashing, the port for the monitor can be modfied as well.
See the [document](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#environment-variables) for more variables that can be specified.

For additional information about the toolchain, run `make help` or visit the [README](https://github.com/espressif/ESP8266_RTOS_SDK#compiling-the-project) for the ESP8266 RTOS SDK.

## License

MIT


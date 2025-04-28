# Ethernet_STM32duino

STM32F103C8T6 + W5500 Lite Ethernet Module (SPI Interface)

Reference: [Mischianti.org STM32 Ethernet W5500](https://mischianti.org/stm32-ethernet-w5500-with-plain-http-and-ssl-https/)

---

## Hardware Required
- STM32F103C8T6 (Blue Pill)
- W5500 Lite Ethernet Module
- USB to Serial Converter
- Breadboard, jumper wires

## Wiring

| W5500 Pin | STM32F103C8T6 Pin |
| :------- | :---------------- |
| SCSn (CS) | PA4 |
| SCLK      | PA5 |
| MISO      | PA6 |
| MOSI      | PA7 |
| GND       | GND |
| 3.3V      | 3.3V |

## Software Setup

1. Install Arduino IDE (>=1.8.13) or Arduino Pro IDE.
2. Add STM32 Board Manager URL: `https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json`
3. Install STM32 core for Arduino (STM32duino).
4. Install Libraries:
   - Ethernet_Generic
   - SPI (default in STM32 core)
5. Select Board:
   - Board: `Generic STM32F103C Series`
   - Variant: `STM32F103C8 (20k RAM, 64k Flash)`
   - Upload method: `STM32CubeProgrammer (Serial)`

## Examples Provided

- Ethernet_Basic_StaticIP
- Ethernet_Basic_DHCP
- Ethernet_HTTP_Client
- Ethernet_HTTPS_Client_BearSSL

Each example is located under the `/examples/` directory.

## License

This project is open-sourced under the MIT License.
*Note: This code is still WIP.
------------------------------

#Arduino code for MCP4706 8-bit DAC with EEPROM and I2C Interface

The MCP4706 is a single channel 8-bit buffered voltage output Digital-to-Analog Converter (DAC) with nonvolatile memory and an I2C serial interface.

This code allows you to read and write all capabilities listed from pg. 51 to 53 of the [datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/22272C.pdf).

The part number used for testing this code is MCP4706A0T-E/CH with device address `0x60`. Other part numbers may have different device addresses as listed on page 83 of the datasheet.

Observed deviation from desired output value is 1.3%.

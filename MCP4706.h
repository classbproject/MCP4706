// Device address for part # MCP4706A0T-E/CH. Device addresses are listed on page 83 of the datasheet.
#define devAddr 0x60

// Voltaile configuration commands
#define VOL_VDD_UNBUFF_PWRON_GAIN1X   0x40  //b01000000 Volatile memory, VDD as Vref unbuffered, Powered on, Gain 1X
#define VOL_VREF_UNBUFF_PWRON_GAIN1X  0x50  //b01010000 Volatile memory, Vref pin unbuffered, Powered on, Gain 1X
#define VOL_VREF_UNBUFF_PWRON_GAIN2X  0x51  //b01010001 Volatile memory, Vref pin unbuffered, Powered on, Gain 2X
#define VOL_VREF_BUFF_PWRON_GAIN1X    0x58  //b01011000 Volatile memory, Vref buffered, Powered on, Gain 1X
#define VOL_VREF_BUFF_PWRON_GAIN2X    0x59  //b01011001 Volatile memory, Vref buffered, Powered on, Gain 2X

// Non-volatile (EEPROM) configuration commands
#define NV_VDD_UNBUFF_PWRON_GAIN1X    0x60  //b01100000 Non-Volatile memory, VDD as Vref unbuffered, Powered on, Gain 1X
#define NV_VREF_UNBUFF_PWRON_GAIN1X   0x70  //b01110000 Non-Volatile memory, Vref pin unbuffered, Powered on, Gain 1X
#define NV_VREF_UNBUFF_PWRON_GAIN2X   0x71  //b01110001 Non-Volatile memory, Vref pin unbuffered, Powered on, Gain 2X
#define NV_VREF_BUFF_PWRON_GAIN1X     0x78  //b01111000 Non-Volatile memory, Vref buffered, Powered on, Gain 1X
#define NV_VREF_BUFF_PWRON_GAIN2X     0x79  //b01111001 Non-Volatile memory, Vref buffered, Powered on, Gain 2X

// Set output value with minimum config
// Use the writeConfig() function for this
#define MIN_CONFIG_PWRON              0x00 //b00000000 Powered on
#define MIN_CONFIG_PWROFF_1K_PDN      0x10 //b00010000 Powered down, Vout is loaded with 1K pull down resistor
#define MIN_CONFIG_PWROFF_100K_PDN    0x20 //b00100000 Powered down, Vout is loaded with 100K pull down resistor
#define MIN_CONFIG_PWROFF_500K_PDN    0x30 //b00110000 Powered down, Vout is loaded with 500K pull down resistor

void initialSetup(void);
bool testConnection(void);
bool writeData(uint8_t confg, uint8_t data);
bool writeConfig(uint8_t confg, uint8_t data);
void readDAC();

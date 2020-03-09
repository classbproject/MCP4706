#include <Wire.h>

#define devAddr 0x60 // Device address for part # MCP4706A0T-E/CH. Device addresses are listed on page 83 of the datasheet.

uint8_t recvBuffer[4];

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
#define MIN_CONFIG_PWRON              0x00 //b00000000 Powered on
#define MIN_CONFIG_PWROFF_1K_PDN      0x10 //b00010000 Powered down, Vout is loaded with 1K pull down resistor
#define MIN_CONFIG_PWROFF_100K_PDN    0x20 //b00100000 Powered down, Vout is loaded with 100K pull down resistor
#define MIN_CONFIG_PWROFF_500K_PDN    0x30 //b00110000 Powered down, Vout is loaded with 500K pull down resistor

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(100000);
  Serial.begin(115200); // Open serial connection to send info to the host
  while (!Serial) {}  // wait for Serial comms to become ready
  Serial.println("Starting up");
  Serial.println("Testing device connection...");
  Serial.println(testConnection() ? "MCP4706 connection successful" : "MCP4706 connection failed");
}

void loop() {
  // put your main code here, to run repeatedly:
  writeDAC(VOL_VREF_BUFF_PWRON_GAIN1X, 183);
  //readDAC();
  delay(3000);
}

bool testConnection(void) {
    Wire.beginTransmission(devAddr);
    return (Wire.endTransmission() == 0);
}

bool writeDAC(uint8_t confg, uint8_t data)
{
  uint8_t retVal;
  Wire.beginTransmission(devAddr);
  Wire.write(confg); // b 010 11 00 0; Write volatile memory command, Vref pin is buffered, not powered down, gain is 1.
  Wire.write(data);
  Wire.write(0x00); // For the MCP4706, a 4th dummy byte is required to complete the command. The DAC does NOT work without this.
  retVal = Wire.endTransmission();
  return retVal;
}

bool writeConfig(uint8_t confg, uint8_t data)
{
  uint8_t retVal;
  Wire.beginTransmission(devAddr);
  Wire.write(confg);
  Wire.write(data);
  retVal = Wire.endTransmission();
  return retVal;
}

void readDAC()
{
  uint8_t ctr, i = 0;
  Wire.requestFrom(devAddr, 4);
  ctr = 0;
  while(Wire.available())
  {
    recvBuffer[ctr] = Wire.read();
    ctr++;
  }

  Serial.print("ctr: ");
  Serial.print(ctr);
  Serial.println("");

  for (i=0; i<ctr; i++)
  {
    Serial.print("recBuffer[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.print(recvBuffer[i], HEX);
    Serial.println("");
  }

  Serial.println("\n");
}

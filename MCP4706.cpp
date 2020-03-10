#include <Arduino.h>
#include <Wire.h>
#include "MCP4706.h"

uint8_t recvBuffer[4];

void initialSetup(void)
{
  Wire.begin();
  Wire.setClock(100000); // Set I2C frequency to 100KHz
  Serial.begin(115200); // Open serial connection to send info to the host
  while (!Serial) {}  // wait for Serial comms to become ready
  Serial.println("Starting up");
  Serial.println("Testing device connection...");
  Serial.println(testConnection() ? "MCP4706 connection successful" : "MCP4706 connection failed");  
}

bool testConnection(void) {
    Wire.beginTransmission(devAddr);
    return (Wire.endTransmission() == 0);
}

bool writeData(uint8_t confg, uint8_t data)
{
  Wire.beginTransmission(devAddr);
  Wire.write(confg); // b 010 11 00 0; Write volatile memory command, Vref pin is buffered, not powered down, gain is 1.
  Wire.write(data);
  Wire.write(0x00); // For the MCP4706, a 4th dummy byte is required to complete the command. The DAC does NOT work without this.
  return (Wire.endTransmission() == 0);
}

bool writeConfig(uint8_t confg, uint8_t data)
{
  Wire.beginTransmission(devAddr);
  Wire.write(confg);
  Wire.write(data);
  return (Wire.endTransmission() == 0);
}

void readDAC()
{
  delay(50); // A small delay that is required to let any pending writing ops finish is this fn is called right after a write op.
  int reqBytes = 4;
  uint8_t i = 0;
  if (Wire.requestFrom(devAddr, reqBytes))
  {
    for (i=0; i<reqBytes; i++)
      recvBuffer[i] = Wire.read();
  }
  
  /* 1st and 3rd bytes are configuration bits for Volatile and Non-volatile commands
   * 2nd and 4th bytes are output data for Volatile and Non-volatile registers.
  */
  for (i=0; i<reqBytes; i++)
  {
    Serial.print("recvBuffer[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.print(recvBuffer[i], BIN);
    Serial.println("");
  }

  Serial.println("\n");
}

//end

#include "MCP4706.h"

void setup() {
  // Initial setup
  initialSetup();
  
  //writeData(VOL_VREF_BUFF_PWRON_GAIN1X, 255);
  writeData(NV_VREF_BUFF_PWRON_GAIN1X, 0xbe);
  readDAC();
}

void loop() {
  // put your main code here, to run repeatedly:
}


//end

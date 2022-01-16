// App Weather Station Part 1 (I2C Scanner).
// Software Designer: Dhr. Van Impe Christophe.
// Date Of Beginning: 03 januari 2022.

#include <Wire.h>

void setup()
{
  // Put Your Setup Code Here, To Run Once:

  Wire.begin();

  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nI2C Scanner");
}

void loop()
{
  // Put Your Main Code Here, To Run Repeatedly:

  byte error;
  byte address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  
  for (address = 1; address < 127; address++ )
  {
    /* The I2C_Scanner Uses The Return Value Of The Wire.endTransmission To 
     * See If
     * A Device Did Acknowledge To The Address.
     */

    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // Wait 5 seconds for the next scan.
}

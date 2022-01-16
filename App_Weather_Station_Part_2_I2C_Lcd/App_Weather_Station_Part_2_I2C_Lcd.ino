// App Weather Station Part 2 (I2C LCD 4 x 20 BLUE/WHITE).
// Software Designer: Dhr. Van Impe Christophe.
// Date Of Beginning: 03 januari 2022.

#include <Wire.h> // Library For I2C Communication.

#include <LiquidCrystal_I2C.h> // Library For I2C Lcd.

LiquidCrystal_I2C lcd(0x27, 20, 4); /* Set The LCD Address To 0x27
                                       For A 20 Chars And 4 Lines I2C Display.
*/

void setup()
{
  // Put Your Setup Code Here, To Run Once:

  lcd.init(); // Initialize The 4 X 20 I2C Lcd.
  lcd.backlight();
  Serial.begin(9600); // BaudRate Serial Monitor.

  lcd.setCursor(5, 0);
  lcd.print("Application");

  lcd.setCursor(3, 1);
  lcd.print("Weather Station");

  lcd.setCursor(0, 2);
  lcd.print("Software Developer:");

  lcd.setCursor(0, 3);
  lcd.print("Van Impe Christophe");

  delay(5000);
  lcd.noBacklight();
  lcd.clear();
}

void loop()
{
  // Put Your Main Code Here, To Run Repeatedly:
}

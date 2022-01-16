// App Weather Station Part 6 (Latch Test).
// Software Designer: Dhr. Van Impe Christophe.
// Date Of Beginning: 03 januari 2022.

// (GLOBALE) VARIABELEN.

const int KNOPPIN = 4; //definiëren van KNOPPIN aan I/O pin 4
const int LEDPINGreen = 5; //definiëren van LED Green pin 5
const int LEDPINRed = 6; //definiëren van LED Red pin 6
int knopWaarde = LOW; //variabele voor de drukknop toestand en initialisatie
int vorigeKnopWaarde = HIGH; //variabale voor vorige knopwaarde en initialisatie
bool ledToestandGreen = LOW; //variabele voor LED toestand aan of uit
bool ledToestandRed = HIGH; //variabele voor LED toestand aan of uit

#include <Wire.h> // Library For I2C Communication.

#include <LiquidCrystal_I2C.h> // Library For I2C Lcd.

LiquidCrystal_I2C lcd(0x27, 20, 4); /* Set The LCD Address To 0x27
                                     * For A 20 Chars And 4 Lines I2C Display.                                   */

void setup()
{
  // Put Your Setup Code Here,To Run Once:

  pinMode (KNOPPIN, INPUT); //KNOPPIN definiëren als ingang.
  pinMode (LEDPINGreen, OUTPUT); //LEDPINGreen definiëren als uitgang.
  pinMode (LEDPINRed, OUTPUT); //LEDPINRed definiëren als uitgang.

  
  lcd.init(); // Initialize The 4 X 20 I2C Lcd.
  lcd.noBacklight();
  Serial.begin(9600); // BaudRate Serial Monitor.

  
}

void loop()
{
  // Put Your Main Code Here,To Run Repeatedly:
  
  knopWaarde = digitalRead (KNOPPIN);     //inlezen van KNOPPIN
  if (knopWaarde == HIGH && vorigeKnopWaarde == LOW)      
  {
    if (ledToestandRed == LOW)
    {
      ledToestandRed = HIGH; 
      ledToestandGreen = LOW;
      lcd.noBacklight();
    }
    else
    {
      ledToestandRed = LOW;
      ledToestandGreen = HIGH;
      lcd.backlight();
    }
  }
  digitalWrite (LEDPINRed, ledToestandRed);
  digitalWrite (LEDPINGreen, !ledToestandRed);
  vorigeKnopWaarde = knopWaarde;
  delay (50);
}

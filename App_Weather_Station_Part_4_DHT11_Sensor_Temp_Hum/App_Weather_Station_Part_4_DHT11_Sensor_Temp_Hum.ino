// App Weather Station Part 4 (DHT11 Sensor(Temp & Hum)).
// Software Designer: Dhr. Van Impe Christophe.
// Date Of Beginning: 03 januari 2022.

#include <Wire.h> // Library For I2C Communication.

#include <LiquidCrystal_I2C.h> // Library For I2C Lcd.

#include <Adafruit_Sensor.h> // Library For Sensor DHT11(Adafruit).

#include <DHT.h> // Library For Sensor DHT11.

LiquidCrystal_I2C lcd(0x27, 20, 4); /* Set The LCD Address To 0x27
                                       For A 20 Chars And 4 Lines
                                       I2C Display.*/

const int KNOPPIN = 4; // Definiëren Van KNOPPIN Aan I/O pin 4 Arduino Mega 2560.

const int LEDPINGreen = 5; // Definiëren Van LED Green Pin 5.
const int LEDPINRed = 6; // Definiëren Van LED Red Pin 6.

int knopWaarde = LOW; // Variabele Voor De Drukknop Toestand En Initialisatie.

int vorigeKnopWaarde = HIGH; /* Variabale Voor Vorige Knopwaarde En
                                initialisatie.
*/

bool ledToestandGreen = LOW; // Bool Variabele Voor LED Toestand Green  Uit.
bool ledToestandRed = HIGH; // Bool Variabele Voor LED Toestand Red Aan.

#define DHTPIN 3

#define DHTTYPE DHT11   // DHT 11.

DHT dht = DHT(DHTPIN, DHTTYPE); // Initialize DHT Sensor For Normal 16mhz Arduino.

void setup()
{
  // Put Your Setup Code Here,To Run Once:

  pinMode (KNOPPIN, INPUT); // KNOPPIN Definiëren Als Ingang.
  pinMode (LEDPINGreen, OUTPUT); // LEDPINGreen Definiëren Als Uitgang.
  pinMode (LEDPINRed, OUTPUT); // LEDPINRed Definiëren Als Uitgang.

  lcd.init(); // Initialize The 4 X 20 I2C Lcd.
  lcd.noBacklight();
  Serial.begin(9600); // BaudRate Serial Monitor.
  Serial.println("DHT11 Test!");

  dht.begin(); // Setup Sensor(DHT11).
}



void loop()
{
  // Put Your Main Code Here,To Run Repeatedly:

  knopWaarde = digitalRead (KNOPPIN); // Inlezen Van KNOPPIN.
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

  float h = dht.readHumidity();

  float t = dht.readTemperature(); // Read Temperature As Celsius (the default).

  // Read Temperature As Fahrenheit (isFahrenheit = true).

  float f = dht.readTemperature(true);

  // Check If Any Reads Failed And Exit Early(To Try Again).

  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute Heat Index In Fahrenheit(The Default).

  float hif = dht.computeHeatIndex(f, h);

  // Compute Heat Index In Celsius(isFahreheit = false).

  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.println( h);
  Serial.print(" % \t");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C\t");

  // Serial.print(f);
  // Serial.print(" *F\t");
  // Serial.print("Heat index: ");
  // Serial.print(hic);
  // Serial.print(" *C ");
  // Serial.print(hif);
  // Serial.println(" *F");

  lcd.setCursor(0, 2);
  lcd.print("Temp : ");
  lcd.print(t);

  lcd.setCursor(0, 3);
  lcd.print("Humidity : ");
  lcd.print(h);
  lcd.print(char(37));
}

// Functions...

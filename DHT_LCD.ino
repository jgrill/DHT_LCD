#include "DHT.h"
#include <LiquidCrystal.h>

#define DHT_PIN 8

#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  dht.begin();
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // DHT22 requires no less than a 2 second delay between reads
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(f);
  lcd.print("F ");
  lcd.print(h);
  lcd.print("%H");
  lcd.setCursor(0, 1);
  lcd.print("H Index: ");
  lcd.print(hif);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}

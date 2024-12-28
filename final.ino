#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "ccs811.h"
#include "MQ135.h"

// Pin definitions
#define DHTPIN 2             
#define DHTTYPE DHT11
#define FLAME_PIN 3          // Connect flame sensor to digital pin 3
#define MQ135_PIN A0         // Connect MQ135 to analog pin A0
#define LED_PIN 4         
#define BUZZER_PIN 7          

DHT dht(DHTPIN, DHTTYPE);
CCS811 ccs811;                
MQ135 gasSensor = MQ135(MQ135_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); //I2C address

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing system...");

  // Initialize sensors
  dht.begin();
  Serial.println("Initializing DHT11 sensor");

  Wire.begin(); // Use default SDA (A4) and SCL (A5) for Arduino Uno
  Serial.println("Initializing CCS811 sensor");

  if (!ccs811.begin()) {
    Serial.println("CCS811 initialization failed!");
    while (1);
  }

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Init...");

  // Initialize pins
  pinMode(FLAME_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Start CCS811 measurement
  if (!ccs811.start(CCS811_MODE_1SEC)) {
    Serial.println("CCS811 start failed!");
    while (1);
  }

  // Allow sensors to stabilize
  delay(2000);
}

void loop() {
  // Read sensors
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int flame = digitalRead(FLAME_PIN);
  float air_quality = gasSensor.getPPM();
  uint16_t eco2, etvoc, errstat, raw;

  ccs811.read(&eco2, &etvoc, &errstat, &raw);

  // Check if DHT reading failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print sensor values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Flame: ");
  Serial.print(flame);
  Serial.print(", MQ135: ");
  Serial.print(air_quality);
  Serial.print(" ppm, eCO2: ");
  Serial.print(eco2);
  Serial.print(" ppm, TVOC: ");
  Serial.print(etvoc);
  Serial.println(" ppb");

  // Fire detection logic and display
  lcd.clear();
  if (temperature > 36 || flame == LOW || air_quality > 100 || eco2 > 1600 || etvoc > 1430) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.setCursor(0, 0);

    // Display relevant alert information
    if (temperature > 36) {
      lcd.print("Temp:");
      lcd.print(temperature);
      lcd.print("*C");
    } else if (flame == LOW) {
      lcd.print("Flame Detected");
    } else if (air_quality > 100) {
      lcd.print("MQ135: ");
      lcd.print(air_quality);
      lcd.print("ppm");
    } else if (eco2 > 1600) {
      lcd.print("CO2: ");
      lcd.print(eco2);
      lcd.print("ppm");
    } else if (etvoc > 1430) {
      lcd.print("TVOC: ");
      lcd.print(etvoc);
      lcd.print("ppb");
    }
    lcd.setCursor(0, 1);
    lcd.print("ALERT! Fire");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("*C");
    lcd.setCursor(0, 1);
    lcd.print("Normal");
  }

  delay(500); // Wait before next loop
}

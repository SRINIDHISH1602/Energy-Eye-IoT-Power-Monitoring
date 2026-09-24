#define BLYNK_TEMPLATE_ID "TMPL3-YlGR2tE"
#define BLYNK_TEMPLATE_NAME "Energy Eye"
#define BLYNK_AUTH_TOKEN "vdh5hpYLRDGr-xmjUnFzSpfdqdSr1WGQ"

#include "time.h"
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "ACS712.h"
#include <ZMPT101B.h>
#include <EEPROM.h>

// WiFi & Blynk credentials
char ssid[] = "@#₹_";
char pass[] = "zxcvbnm12";

#define RELAY 5

ACS712 ACS(35, 3.3, 4095, 125);      // ACS712-20A → ideally use 100 instead of 125
ZMPT101B voltageSensor(34, 50.0);

LiquidCrystal_I2C lcd(0x27, 16, 2);

float unit = 0.0;       // kWh
float volt = 0.0;
float current_mA = 0.0;
float power_W = 0.0;
float amount = 0.0;     // ₹
int switchState = 0;

#define EEPROM_SIZE 512
#define UNIT_ADDRESS 0

unsigned long lastMillis = 0;

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V4);
}

BLYNK_WRITE(V4) {
  switchState = param.asInt();
  digitalWrite(RELAY, switchState ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(UNIT_ADDRESS, unit);
  if (isnan(unit)) unit = 0.0;

  ACS.autoMidPoint();
  voltageSensor.setSensitivity(500.0f);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Energy Meter");

  lastMillis = millis();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  bool relayOn = (switchState == 1);

  // ---------- CURRENT ----------
  float avg_mA = 0;
  for (int i = 0; i < 60; i++) {
    avg_mA += ACS.mA_AC();
  }
  avg_mA /= 60.0;

  if (avg_mA > 5) current_mA = avg_mA;
  else current_mA = 0;

  if (!relayOn) current_mA = 0;

  // ---------- VOLTAGE ----------
  float v = voltageSensor.getRmsVoltage();
  if (v > 50) volt = v;
  else volt = 0;

  // ---------- POWER ----------
  power_W = volt * (current_mA / 1000.0);
  if (!relayOn) power_W = 0;

  // ---------- ENERGY (kWh) ----------
  unsigned long now = millis();
  float elapsedMs = now - lastMillis;
  lastMillis = now;

  if (relayOn && power_W > 1) {
    float kW = power_W / 1000.0;
    float hours = elapsedMs / 3600000.0;
    unit += kW * hours;
  }

  // ---------- CALCULATE AMOUNT ----------
  amount = unit * 8.0;   // ₹8 per unit (1kWh)

  // ---------- EEPROM STORE ----------
  static unsigned long lastSave = 0;
  if (millis() - lastSave > 5000) {
    EEPROM.put(UNIT_ADDRESS, unit);
    EEPROM.commit();
    lastSave = millis();
  }

  // ---------- LCD ----------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("U:");
  lcd.print(unit, 2);
  lcd.print("kWh");

  lcd.setCursor(0, 1);
  lcd.print("Amt:");
  lcd.print("Rs");
  lcd.print(amount, 2);
  
  // ---------- Blynk ----------
  Blynk.virtualWrite(V0, volt);
  Blynk.virtualWrite(V1, current_mA);
  Blynk.virtualWrite(V2, power_W);
  Blynk.virtualWrite(V3, unit);
  Blynk.virtualWrite(V7, amount);

  delay(400);
}

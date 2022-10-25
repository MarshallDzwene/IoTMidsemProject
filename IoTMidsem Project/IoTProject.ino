#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x3F, 16 column and 2 rows

#define TRIG_PIN 26 // ESP32 pin GIOP26 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 25 // ESP32 pin GIOP25 connected to Ultrasonic Sensor's ECHO pin
#define REDLED 19
float duration_us, distance_cm, minimum_depth, tank_height, current_level;

void setup() {
  lcd.init();               // initialize the lcd
  lcd.backlight();          // open the backlight
  pinMode(TRIG_PIN, OUTPUT); // config trigger pin to output mode
  pinMode(ECHO_PIN, INPUT);  // config echo pin to input mode
  pinMode(REDLED, OUTPUT);
  Serial.begin(115200);
  minimum_depth = 5;
  tank_height = 200;
  }

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
  current_level = tank_height - distance_cm;

// change distance to current level for deployment

  lcd.clear();
  lcd.setCursor(0, 0); // start to print at the first row
  lcd.print("Water Level: ");
  lcd.print(distance_cm); /// subtract this distance from length of tank

  delay(500);
}

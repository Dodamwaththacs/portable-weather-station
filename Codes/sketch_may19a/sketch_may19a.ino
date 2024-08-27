#include <LiquidCrystal_I2C.h>
#include <DFRobot_DHT11.h>

LiquidCrystal_I2C lcd(0x3F, 16, 4); // I2C address 0x27, 16 columns and 4 rows
DFRobot_DHT11 DHT;
#define DHT11_PIN 10
#define MQ2_PIN A0
#define RAIN_SENSOR_PIN_1 A1
#define RAIN_SENSOR_PIN_2 A2
const int buzzerPin = 9;

bool showTemp = true;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(RAIN_SENSOR_PIN_1, INPUT);
  pinMode(RAIN_SENSOR_PIN_2, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  DHT.read(DHT11_PIN);
  int mq2Value = analogRead(MQ2_PIN);
  float mq2Voltage = mq2Value * (5.0 / 1023.0);
  float mq2Rs = ((5.0 - mq2Voltage) / mq2Voltage) * 10000.0;
  float mq2Resistance = mq2Rs * 1.18;
  float mq2PPM = 116.6020682 * pow(mq2Resistance / 10000.0, -2.769034857);
  int rainValue1 = analogRead(RAIN_SENSOR_PIN_1);
  int rainValue2 = analogRead(RAIN_SENSOR_PIN_2);

  lcd.clear();
  lcd.setCursor(0, 0);

  if (showTemp) {
    lcd.print("Temp: ");
    lcd.print(DHT.temperature);
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
  } else {
    lcd.print("MQ2 Sensor:");
    lcd.setCursor(0, 1);
    lcd.print("PPM: ");
    lcd.print(mq2PPM);
  }

  // Alternate between displaying temperature/humidity and MQ2 values every 5 seconds
  if ((millis() / 1000) % 5 == 0) {
    showTemp = !showTemp;
  }

  // Display raindrop sensor values every second
  lcd.setCursor(0, 2);
  lcd.print("Rain: ");
  if (rainValue1 < 700 && rainValue2 < 700) {
    lcd.print("RAINING");
    deactivateBuzzer();
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    delay(1000); // Delay for 1 second
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer

  } else {
    lcd.print("Normal");
    
    activateBuzzer();
  }
  

  delay(1000);
}

void activateBuzzer() {
  digitalWrite(buzzerPin, HIGH);
}

void deactivateBuzzer() {
  digitalWrite(buzzerPin, LOW);
}

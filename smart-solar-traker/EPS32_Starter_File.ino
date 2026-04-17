#include <Wire.h>
#include <LCD_I2C.h>
#include <ESP32Servo.h>
#include <DHT11.h>
#include <BH1750.h>

/* ------------------- DEFINES ------------------- */


#define BUZZER_PIN 15
#define BUTTON_PIN 2

#define SERVO_H_PIN 18
#define SERVO_V_PIN 19

#define LDR_BOT 34
#define LDR_TOP 35
#define LDR_LEFT 32
#define LDR_RIGHT 33

/* ------------------- OBJECTS ------------------- */
LCD_I2C lcd(0x27, 16, 2);
DHT11 dht(4);
BH1750 lightMeter;

Servo servohori;
Servo servoverti;

/* ------------------- VARIABLES ------------------- */
int servoh = 0;
int servov = 0;

int servohLimitHigh = 180;
int servohLimitLow  = 10;
int servovLimitHigh = 180;
int servovLimitLow  = 10;

int h, c;
float lux = 0;

/* ------------------- BUZZER PWM ------------------- */
const int buzzerChannel = 0;
const int buzzerFreq = 1000;
const int buzzerResolution = 8;

/* ------------------- SETUP ------------------- */
void setup()
{
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin(21, 22);   // SDA, SCL

  lcd.begin();
  lcd.backlight();

 

  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);


  servohori.attach(SERVO_H_PIN);
  servoverti.attach(SERVO_V_PIN);

  servohori.write(0);
  servoverti.write(0);
}

/* ------------------- LOOP ------------------- */
void loop()
{
  readLightIntensity();
  servoTracking();
  dht11_Read();

  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    servoverti.write(0);
    servohori.write(0);
    buzzer_tone(1);
  }
  else
  {
    buzzer_tone(0);
  }

  delay(800);
}

/* ------------------- LIGHT SENSOR ------------------- */
void readLightIntensity()
{
  lux = lightMeter.readLightLevel();

  if (lux < 0 || lux > 120000)  // Safety check
    lux = 0;

  lcd.setCursor(0, 0);
  lcd.print("Light:");
  lcd.print(lux, 1);
  lcd.print(" lx ");

  Serial.print("Light Intensity: ");
  Serial.print(lux);
  Serial.println(" lx");
}

/* ------------------- SERVO TRACKING ------------------- */
void servoTracking()
{
  servoh = servohori.read();
  servov = servoverti.read();

  int left  = analogRead(LDR_LEFT);
  int right = analogRead(LDR_RIGHT);
  int top   = analogRead(LDR_TOP);
  int bot   = analogRead(LDR_BOT);

  if (top < bot) servov -= 5;
  else if (bot < top) servov += 5;

  servov = constrain(servov, servovLimitLow, servovLimitHigh);
  servoverti.write(servov);
  delay(8);

  if (left > right) servoh -= 5;
  else if (right > left) servoh += 5;

  servoh = constrain(servoh, servohLimitLow, servohLimitHigh);
  servohori.write(servoh);
  delay(8);
}

/* ------------------- BUZZER ------------------- */
void buzzer_tone(int buz)
{
  if (buz == 1)
    ledcWriteTone(buzzerChannel, buzzerFreq);
  else
    ledcWriteTone(buzzerChannel, 0);
}

/* ------------------- DHT11 ------------------- */
void dht11_Read()
{
  h = dht.readHumidity();
  c = dht.readTemperature();

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("% ");

  lcd.setCursor(7, 1);
  lcd.print("T:");
  lcd.print(c);
  lcd.print("C ");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %  Temperature: ");
  Serial.println(c);
}

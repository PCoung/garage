//WhiteCard UID: 41 6A A2 1C
//BlueCard UID: B9 A7 A3 5A
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"
// Create instances
const int DHTPIN = 4;      
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
Servo sg90;
#define  greenLed  7
#define  redLed  6
#define  servoPin  8
#define  buzzerPin  5
#define  qtro1  A0
#define  qtro2  A1
#define  qtro3  A2
#define  qtro4  A3
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int x = 0, ngay = 0, thang = 0, nam = 0, h, m ,s;
String tagUID1 = "41 6A A2 1C",tagUID2 =  "B9 A7 A3 5A";
long Wallet[] = {10,10};
void setup() {
  
  // Arduino Pin configuration
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
  sg90.attach(servoPin);  
  sg90.write(0); 
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(5, 1);
  lcd.print("our project");
  delay(2500);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Made by");
  lcd.setCursor(8, 1);
  lcd.print("T-REX");
  delay(2500);
  SPI.begin();      
  mfrc522.PCD_Init();   
  lcd.clear();
   if (! rtc.begin())
  {
    lcd.print("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning())
  {
    lcd.print("RTC is NOT running!");
    lcd.println();
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}
void loop() {
  DateTime now = rtc.now();
  if (now.hour() <= 9)
  {
    lcd.setCursor(0, 0);
    lcd.print("0");
    lcd.print(now.hour());
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print(now.hour());
  }
  lcd.print(':');
  if (now.minute() <= 9)
  {
    lcd.print("0");
    lcd.print(now.minute());
  }
  else {
    lcd.print(now.minute());
  }
  lcd.print(':');
  if (now.second() <= 9)
  {
    lcd.print("0");
    lcd.print(now.second());
  }
  else {
    lcd.print(now.second());
  }

  lcd.setCursor(0, 1);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(",");
  if (now.day() <= 9)
  {
    lcd.print("0");
    lcd.print(now.day());
  }
  else {
    lcd.print(now.day());
  }
  lcd.print('/');
  if (now.month() <= 9)
  {
    lcd.print("0");
    lcd.print(now.month());
  }
  else {
    lcd.print(now.month());
  }
  lcd.print('/');
  if (now.year() <= 9)
  {
    lcd.print("0");
    lcd.print(now.year());
  }
  else {
    lcd.print(now.year());
  }
  float t = dht.readTemperature();
  lcd.setCursor(9, 0);
  lcd.print(t);
  lcd.print("*C");
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Reading from the card
  String tag = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tag.toUpperCase();
  //Checking the card

  if ((tag.substring(1) == tagUID1) or (tag.substring(1) == tagUID2))
  {
    // If UID of tag is matched.
   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    delay (1000);
    sg90.write(0);
    lcd.setCursor(0, 0);
    lcd.print("Available space");
    Availble_space ();
    
    digitalWrite(greenLed, HIGH);
    delay(5000);
    digitalWrite(greenLed, LOW);
    sg90.write(90);
    lcd.clear();
    
  }
  else
  {
    // If UID of tag is not matched.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong Tag Shown");
    lcd.setCursor(0, 1);
    lcd.print("Access Denied");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLed, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLed, LOW);
    lcd.clear();
  }
}
void Availble_space ()
{
    if (analogRead(qtro1)> 1000)
    {
      lcd.setCursor(0, 1);
      lcd.print("A1");
    }
    else if (analogRead(qtro2)> 200)
    {
      lcd.setCursor(0, 1);
      lcd.print("A2");
    }
    else if (analogRead(qtro3)> 200)
    {
      lcd.setCursor(0, 1);
      lcd.print("B1");
    }
    else if (analogRead(qtro4)> 200)
    {
      lcd.setCursor(0, 1);
      lcd.print("B2");
    }
}

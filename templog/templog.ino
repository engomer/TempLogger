/* Temperature chechker, database logger, mail sender and alarm system for pharmacies 
 * Version: v1.0 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Ömer Gençay <ogencay98@gmail.com> <+905396455196> 
 * January 2019
 */


/*  
    dht pin = d0
    scl = d1
    sda = d2
    onewire = d3
    buzzer = d4
*/
//LIBRARY DECLERATION STARTS
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//LIBRARY DECLERATION ENDS

//WIFI STAFF STARTS
const char* ssid= "WIFI SSID";
const char* pwd = "WIFI PASSWORD";
//WIFI STAFF ENDS

//RESET STAFF STARTS
void(* resetFunc) (void) = 0;
int count = 0;
//RESET STAFF ENDS

//EMAIL STAFF STARTS
const char server[] = "SMTP MAIL SERVER";
const char* email = "MAIL ADDRESS";
const char* email64 = "MAIL ADDRESS BASE 64 FORMAT";
const char* pwdmail = "MAIL PASSWORD";
const char* pwd64 = "MAIL PASSWORD BASE 64 FORMAT";
WiFiClient espClient; 
//EMAIL STAFF ENDS

//DATABASE STAFF BEGINS
char host[] = "HOST SERVER";
const int httpPort = 80;
//DATABASE STAFF ENDS

//LCD STAFF STARTS
LiquidCrystal_I2C lcd(0x27, 16, 2);
//LCD STAFF STARTS

//BUZZER STAFF STARTS
#define BUZZERPIN 2
//BUZZER STAFF ENDS

//MEASUREMENT STAFF DECLERATION STARTS
#define DHTPIN 16
#define ONEWIREPIN 0
#define DHTTYPE DHT11
OneWire oneWire(ONEWIREPIN);
DallasTemperature wire(&oneWire);
dht DHT;
float hum;
float tempout;
float tempin;
char buffer[10];
//MEASUREMENT STAFF DECLERATION ENDS

//FUNCTIONS DECLERATION STARTS
void measure();
byte emailResp();
byte sendEmail(float tempin, float tempout, float hum);
void print2screen(float tempin, float tempout, float hum);
void printerror(char* error);
bool isinok(float temp);
bool isouttempok(float temp);
bool ishumok(float hum);
void buzerror();
void connect2WiFi();
void sendDB(float tempin,float tempout,float hum);
void chk();
//FUNCTIONS DECLERATION ENDS

void setup() {
  Serial.begin(115200);
  delay(100);
  wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,1);
  lcd.print("Merhaba");
  delay(500);
  pinMode(BUZZERPIN, OUTPUT);
  connect2WiFi();
  printerror("Wifi Baglandi");
  measure();
  printerror("Hazirlaniyor..");
  delay(10000);
  print2screen(tempin,tempout,hum);  
}

void loop() 
{ 
 count = count +1;
  if(count % 4 == 0){measure(); print2screen(tempin,tempout,hum);} //MEASURE AND PRINT TO SCREEN THE VALUES FOR 40 SEC CYCLE 
  if(count % 60 == 0 ){connect2WiFi(); chk(); } //REFRESH WIFI EVERY 10 MINUTE AND CHECK VALUES 
  if(count % 360 == 0){sendDB(tempin,tempout,hum);}// SEND TO DB FOR 1 HOUR CYCLE
  if(count % 720 == 0){count = 0;} //SET COUNTER TO 0 TO REDUCE OVERSIZE
  delay(10000);
}
void chk() // CHECKS VALUES IF THEY ARE NOT GOOD SENDS MAIL AND BEEPS THE BUZZER
{
  if(isinok(tempin)==0 || isouttempok(tempout)==0 || ishumok(hum)==0)
  {
   sendEmail(tempin,tempout,hum);
   buzerror();
   delay(1000); 
  }
}

void measure() // MEASURE 3 VALUES ROOM TEMPERATURE, HUMIDITY AND FRIDGE TEMPERATURE
{
  DHT.read11(DHTPIN);
  wire.requestTemperatures();

  Serial.print("Fridge Temp: ");
  Serial.print(wire.getTempCByIndex(0));
  tempin = wire.getTempCByIndex(0);
  
  Serial.print("\t");
  Serial.print("Current Temp: ");
  Serial.print(DHT.temperature);
  tempout = DHT.temperature;
  
  Serial.print("\t");
  Serial.print("Current Humidity: ");
  Serial.print(DHT.humidity);
  hum = DHT.humidity;

  Serial.println("");
  delay(600);
}

void print2screen(float tempin, float tempout, float hum) // PRINTS THE MEASUREMENT VALUES TO THE LCD SCREEN
{
  lcd.clear();
  lcd.home();
  
  lcd.print("T1:   T2:   Hum:");
  lcd.setCursor(0,1);
  lcd.print(tempout, 1);
  lcd.print("  ");
  lcd.print(tempin, 1);
  lcd.print("  ");
  lcd.print(hum ,1);
 }

void printerror(char* error) // PRINTS ONE LINE TO LCD
{
  lcd.clear();
  lcd.home();
  lcd.print(error);
}

bool isinok(float temp) //CHECKS FRIDGE TEMPERATURE
{
   if(temp<2 || temp>8)
   {
    return 0;
   }
   return 1;
}

bool isouttempok(float temp) //CHECKS ROOM TEMPERATURE
{
  if(temp<15 || temp>25)
  {
    return 0;
  }
  return 1;
}
bool ishumok(float hum) // CHECKS THE HUMIDITIY
{
  if(hum>65) return 0;
  return 1;
}
void buzerror() //BUZZER BEEP FUNCTION
{
    delay(200);
    digitalWrite(BUZZERPIN, HIGH);
    delay(200);
    digitalWrite(BUZZERPIN, LOW);
    delay(200);
    digitalWrite(BUZZERPIN, HIGH);
    delay(200);
    digitalWrite(BUZZERPIN, LOW);
    delay(200);
    digitalWrite(BUZZERPIN, HIGH);
    delay(200);
    digitalWrite(BUZZERPIN, LOW);
    delay(200);
    digitalWrite(BUZZERPIN, HIGH);
    delay(200);
    digitalWrite(BUZZERPIN, LOW);
}

void connect2WiFi() // CONNECT WIFI AND PRINT CREDITENDALS
{
  delay(1500);
  Serial.println("Wifi Connecting.....");
  Serial.print(".");
  delay(10);
  WiFi.begin(ssid,pwd);
  
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
    Serial.print("Wifi Connected!");
    Serial.print("WiFi SSID");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

byte sendEmail(float tempin, float tempout, float hum) //SENDS MAIL USING THE ADDRES: sensor@ogencay.com
{
  
  if (espClient.connect(server, 587) == 1) 
  {
    Serial.println(F("connected"));
  } 
  else 
  {
    Serial.println(F("connection failed"));
    return 0;
  }
  if (!emailResp()) 
    return 0;
    
  Serial.println(F("Sending EHLO"));
  espClient.println("EHLO <SMTP SERVER>");
  if (!emailResp()) 
    return 0;
  Serial.println(F("Sending auth plain"));
  espClient.println("AUTH LOGIN");
  if (!emailResp()) 
    return 0;
    
  Serial.println(F("Sending User"));
  espClient.println("<MAIL ADDRESS BASE 64>"); //base64, ASCII encoded Username
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending Password"));
  espClient.println("<PASSWORD BASE 64>");//base64, ASCII encoded Password
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending From"));
  espClient.println(F("MAIL From: <MAIL ADDRESS>"));
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending To"));
  espClient.println(F("RCPT To: <RECIPIENT MAIL ADDRESS>"));
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending DATA"));
  espClient.println(F("DATA"));
  if (!emailResp()) 
    return 0;
  Serial.println(F("Sending email"));
  
  espClient.println(F("To:  <RECIPIENT MAIL ADDRESS>"));
  
  espClient.println(F("From: <MAIL ADDRESS>"));
 
  espClient.println(F("Subject: TEMPERATURE AND HUMIDITY SENSOR\r\n"));
  espClient.println(F("YOUR MEASUREMENTS ARE NOT GOOD PLEASE CHECK IT BELOW\n"));
  if(tempin<2 || tempin > 8)
  espClient.println("INSIDE TEMPERATURE IS NOT BETWEEN 2-8 C. INSIDE TEMPERATURE = " + String(dtostrf(tempin,3,2,buffer)) + " C"); 
  if(tempout<15 || tempout > 25)
  espClient.println("OUTSIDE TEMPERATURE IS NOT BETWEEN 15-25 C. OUTSIDE TEMPERATURE = " + String(dtostrf(tempout,3,2,buffer)) + " C"); 
  if(hum > 65)
  espClient.println("HUMIDITY IS BIGGER THAN 65% . HUMIDITY = " + String(dtostrf(hum,3,2,buffer)) + "%"); 
  
  espClient.println(F("."));
  if (!emailResp()) 
    return 0;
  Serial.println(F("Sending QUIT"));
  espClient.println(F("QUIT"));
  if (!emailResp()) 
    return 0;
  espClient.stop();
  Serial.println(F("disconnected"));
  return 1;
}

byte emailResp() // READS THE CLIENT FOR E MAIL RESPONSE TO CHECK IT HAS BEEN SENT OR NOT
{
  byte responseCode;
  byte readByte;
  int loopCount = 0;

  while (!espClient.available()) 
  {
    delay(1);
    loopCount++;
    // Wait for 20 seconds and if nothing is received, stop.
    if (loopCount > 300000) 
    {
      espClient.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  responseCode = espClient.peek();
  while (espClient.available())
  {
    readByte = espClient.read();
    Serial.write(readByte);
  }

  if (responseCode >= '4')
  {
   return 0;
  }
  return 1;
}

void sendDB(float tempin,float tempout,float hum)
{
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
  
  if (!client.connect(host, 80)) { Serial.println("connection failed"); return;}
  
  
  String url = "/api/insert.php?tempin=" + String(tempin) +"&tempout=" + String(tempout) + "&hum="+ String(hum);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print("GET " + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);
 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(3000);
  
}

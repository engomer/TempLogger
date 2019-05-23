/* Temperature chechker, database logger, mail sender and alarm system for pharmacies 
 * Version: v1.0 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Ömer Gençay <ogencay98@gmail.com> <+905396455196> 
 * January 2019
 */

// API KEY : 38df0b72-86cc-412f-805b-7a6c27554ad5
/*  
    dht pin = d6
    scl = d1
    sda = d2
    onewire = d3
    buzzer = d4
*/
//LIBRARY DECLERATION STARTS
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//LIBRARY DECLERATION ENDS

//WIFI STAFF STARTS
const char* ssid= "gencay_eczanesi";
const char* pwd = "sel20en00";
//WIFI STAFF ENDS

//RESET STAFF STARTS
void(* resetFunc) (void) = 0;
int count = 0;
//RESET STAFF ENDS

//EMAIL STAFF STARTS
const char* subject = "Templogger%20Sensör%20Değerleri%20Uyumsuz!";
//EMAIL STAFF ENDS

//DATABASE STAFF BEGINS
char host[] = "templog.herokuapp.com";
const int httpPort = 80;
//DATABASE STAFF ENDS

//LCD STAFF STARTS
LiquidCrystal_I2C lcd(0x27, 16, 2);
//LCD STAFF STARTS

//BUZZER STAFF STARTS
#define BUZZERPIN 2
//BUZZER STAFF ENDS

//MEASUREMENT STAFF DECLERATION STARTS
#define DHTPIN 12
#define ONEWIREPIN 0
#define DHTTYPE DHT11
OneWire oneWire(ONEWIREPIN);
DallasTemperature wire(&oneWire);
DHT dht(DHTPIN, DHTTYPE);
float hum;
float tempout;
float tempin;
char buffer[10];
//MEASUREMENT STAFF DECLERATION ENDS

//FUNCTIONS DECLERATION STARTS
void measure();
void sendMail(float tempin, float tempout, float hum);
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
  dht.begin();
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
   sendMail(tempin,tempout,hum);
   buzerror();
   delay(1000); 
  }
}

void measure() // MEASURE 3 VALUES ROOM TEMPERATURE, HUMIDITY AND FRIDGE TEMPERATURE
{
  
  wire.requestTemperatures();

  Serial.print("Fridge Temp: ");
  Serial.print(wire.getTempCByIndex(0));
  tempin = wire.getTempCByIndex(0);
  
  Serial.print("\t");
  Serial.print("Current Temp: ");
  Serial.print(dht.readTemperature());
  tempout = dht.readTemperature();
  
  Serial.print("\t");
  Serial.print("Current Humidity: ");
  Serial.print(dht.readHumidity());
  hum = dht.readHumidity();

  Serial.println("");
  delay(600);
}

void print2screen(float tempin, float tempout, float hum) // PRINTS THE MEASUREMENT VALUES TO THE LCD SCREEN
{
  lcd.clear();
  lcd.home();
  
  lcd.print("T1:   T2:   Nem:");
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


void sendDB(float tempin,float tempout,float hum)
{
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
  
  if (!client.connect(host, 80)) { Serial.println("connection failed"); return;}
  
  
  String url = "/api/38df0b72-86cc-412f-805b-7a6c27554ad5/insert.php?tempin=" + String(tempin) +"&tempout=" + String(tempout) + "&hum="+ String(hum);
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

void sendMail(float tempin,float tempout,float hum)
{
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
  
  if (!client.connect(host, 80)) { Serial.println("connection failed"); return;}
  
  
  String url = "/api/38df0b72-86cc-412f-805b-7a6c27554ad5/sendmail.php?&subject=" + String(subject) + "&body=Ölçümleriniz%20istenilen%20aralıkta%20değil,%20lütfen%20kontrol%20edin.<br/>Oda:%20"
                + String(tempout) + "%20Dolap:%20" + String(tempin) + "%20Nem:%20" + String(hum);
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

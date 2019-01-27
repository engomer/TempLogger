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

//SERVER STAFF STARTS
ESP8266WebServer localServer(80);
String page= "";
//SERVER STAFF ENDS

//WIFI STAFF STARTS
const char* ssid= "Musluk";
const char* pwd = "mamamamimimimikrofonsov";
//WIFI STAFF ENDS
//RESET STAFF STARTS
void(* resetFunc) (void) = 0;
int count = 0;
//RESET STAFF ENDS
//EMAIL STAFF STARTS
const char server[] = "mail.ogencay.com";
const char* email = "sensor@ogencay.com";
const char* email64 = "c2Vuc29yQG9nZW5jYXkuY29t";
const char* pwdmail = "1510OMer";
const char* pwd64 = "MTUxME9NZXI=";
WiFiClient espClient; 
//EMAIL STAFF ENDS

//CLOUD STAFF STARTS
String apiKey = "XSKI0MAE18GL8JP2";
const char* cloudServer = "api.thingspeak.com";
WiFiClient cloudClient;
//CLOUD STAFF ENDS

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
void counter();
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
  if(count % 4 == 0){measure(); print2screen(tempin,tempout,hum);}
  if(count % 18 == 0 ){measure(); print2screen(tempin,tempout,hum); chk(); Serial.println(count);}
  if(count % 60 == 0 ){connect2WiFi();}
  if(count % 360 == 0){sendDB(tempin,tempout,hum);}
  if(count % 720 == 0){count = 0;}
  delay(10000);
}
void chk()
{
  if(isinok(tempin)==0 || isouttempok(tempout)==0 || ishumok(hum)==0)
  {
   //sendEmail(tempin,tempout,hum);
   buzerror();
   delay(1000); 
  }
}

void measure()
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

void print2screen(float tempin, float tempout, float hum)
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

void printerror(char* error)
{
  lcd.clear();
  lcd.home();
  lcd.print(error);
}

bool isinok(float temp)
{
   if(temp<2 || temp>8)
   {
    //printerror("Buzdolabi");
    return 0;
   }
   return 1;
}

bool isouttempok(float temp)
{
  if(temp<15 || temp>25)
  {
    //printerror("Sıcaklik!!");
    return 0;
  }
  return 1;
}
bool ishumok(float hum)
{
  if(hum>65)
  {
    //printerror("Nem > 65");
    return 0;
  }
  return 1;
}
void buzerror()
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
    
  
  delay(15000);
}

void connect2WiFi()
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

byte sendEmail(float tempin, float tempout, float hum)
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
  espClient.println("EHLO mail.ogencay.com");
  if (!emailResp()) 
    return 0;
  Serial.println(F("Sending auth plain"));
  espClient.println("AUTH LOGIN");
  if (!emailResp()) 
    return 0;
    
  Serial.println(F("Sending User"));
  espClient.println("c2Vuc29yQG9nZW5jYXkuY29t"); //base64, ASCII encoded Username
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending Password"));
  espClient.println("MTUxME9NZXI=");//base64, ASCII encoded Password
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending From"));
  espClient.println(F("MAIL From: sensor@ogencay.com"));
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending To"));
  espClient.println(F("RCPT To: ogencay98@gmail.com"));
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending DATA"));
  espClient.println(F("DATA"));
  if (!emailResp()) 
    return 0;
  Serial.println(F("Sending email"));
  
  espClient.println(F("To:  ogencay98@gmail.com"));
  
  espClient.println(F("From: sensor@ogencay.com"));
 
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

byte emailResp()
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
  
  
  String url = "/insert.php?tempin=" + String(tempin) +"&tempout=" + String(tempout) + "&hum="+ String(hum);
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

void counter()
{
  int i;
    for(i=count ; i<=720 ; i++)
    {   
        delay(10000);

        if(i % 18 == 0 ){measure(); print2screen(tempin,tempout,hum); chk(); Serial.println(count);}
        if(i % 60 == 0 ){resetFunc();}
        if(i % 360 == 0){sendDB(tempin,tempout,hum);}
        if(i % 720 == 0){count = 0;}
    }
}

#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>
#include <Wire.h>     
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd(0x3F,16,2);   

WiFiClient client;
HTTPClient http;
String url;
String API ="LSHXLSUUDW41LKA0" ;
String FieldNo="1";

void ConnecTOWifi (void) ;
void setup (){
  Serial.begin (115200);
  lcd.init();       
  lcd.backlight();  
  lcd.setCursor(0, 0);
  lcd.print("Connecting to...");
  ConnecTOWifi ();
}
int httpcode, stepvalue;

void loop (){
  stepvalue=analogRead(A0);
  int db = map(stepvalue,20,900,49.5,90);   
  SendGETRequest (db);
  lcd.setCursor(0, 0);
  lcd.print("Loudness: ");
  lcd.print(db);
  lcd.print("dB");
if (db <= 60)
  {
    lcd.setCursor(0, 1);
    lcd.print("Level: Quite");
    
  }
  else if (db > 60 && db<85)
  {
    lcd.setCursor(0, 1);
    lcd.print("Level: Moderate");
    
  }
  else if (db>=85)
  {
    lcd.setCursor(0, 1);
    lcd.print("Level: High");
    
 
  }  
  delay(15000);
}

void SendGETRequest(int data){
  url = "http://api.thingspeak.com/update?api_key=" ;
  url = url + API;
  url = url + "&field";
  url = url + FieldNo;
  url = url + "=";
  url = url + data;
  http.begin (client,url) ;
  Serial.println ("Waiting For Response") ;
  httpcode = http.GET() ;
  if (httpcode>0){
  //Serial.print(db) ;
  Serial.println("— Data sent successfully") ;
  }
  else{
    Serial.println("Error in sending");
  }
  http.end();
}

void ConnecTOWifi (){
  WiFi.mode(WIFI_STA);
  WiFi.begin("OnePlusNord25G","21bct0366") ;
  Serial.print("connecting to wifi") ;
  while (WiFi.status()!= WL_CONNECTED){
    Serial.print('.');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connected...");
    delay(4000);
    lcd.clear();
    delay (200) ;    
  }
  Serial.print ("IP Address:");
  Serial.println (WiFi.localIP()) ;
  Serial.print ("MacAddress : ");
  Serial.println (WiFi.macAddress()) ;
}
  

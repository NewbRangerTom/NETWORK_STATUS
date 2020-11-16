#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

const char* WIFI_SSID = "your_SSID";  //your SSID for 2.4Ghz network
const char* WIFI_PWD = "your_password";  //your password (WPA2 key)

const IPAddress remote_ip(1,1,1,1);   // you can change this to any public address you want.  A public DNS server is ideal.
const IPAddress gateway_ip(x,x,x,x);  // change to your gateway IP address

int dt1=1000;
int dt2=2000;
int dt5=5000;

//LED pinout - common cathode to GND
#define ledR  D2
#define ledG  D3

long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

void printDigits(byte digits){
 // utility function for digital clock display: prints colon and leading 0
 Serial.print(":");
 if(digits < 10)
   Serial.print('0');
 Serial.print(digits,DEC);  
}

void time(){
  long timeNow = millis();
 
  int days = timeNow / day ;                                //number of days
  int hours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
  int minutes = ((timeNow % day) % hour) / minute ;         //and so on...
  int seconds = (((timeNow % day) % hour) % minute) / second;

// digital clock display of current time
   Serial.print(days,DEC);  
   printDigits(hours);  
   printDigits(minutes);
   printDigits(seconds);
   Serial.println();  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW); 
  
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  delay(dt2);
  
  int counter = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(dt1);
    Serial.print("Waiting!");
  
    counter++;
  }

  Serial.println("WiFi connected ");  
  Serial.println(WiFi.localIP());
  delay(dt5);

  Serial.print("Ping Gateway IP ");
  Serial.println(gateway_ip);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(WiFi.status() == WL_CONNECTED){
    Serial.print("LAN UP ");
    time();
    Serial.println(" ");
    }

  if(Ping.ping(remote_ip)) {
    Serial.print("WAN UP ");
    time();
    Serial.println(" ");
    digitalWrite(ledG, HIGH);
    digitalWrite(ledR, LOW);
    } 
  else {
    Serial.print("WAN Down ");
    time();
    Serial.println(" ");
    digitalWrite(ledG, LOW);
    digitalWrite(ledR, HIGH);
    }
}

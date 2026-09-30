#include <Wire.h>
#include<WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define led 2
char data;
String current_dir ="1";
String new_dir=""; 
#define SCREEN_ADDRESS 0x3C 
#define signal_pin 32
const char*ssid="Redmi A3";
const char*pass="Anoop@689102";
WiFiServer Server(80);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup(){
  Wire.begin(21, 22);
  pinMode(led,OUTPUT);
  pinMode(signal_pin,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid,pass);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed. Check wiring/address!"));
    for(;;);
  
}
  
  
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
   disupdate("Connecting to WiFi...");
  }
  
  disupdate("connectected.!");
  ip();
  Server.begin();
  
}
void blink(int time){
  digitalWrite(led,HIGH);
  delay(time);
  digitalWrite(led,LOW);
  delay(time);
}
void disupdate(const char*text){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,10);
  display.println(text);
  display.display();

}
void ip(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("ip:");
  display.setCursor(0,25);
  display.println(WiFi.localIP());
  display.display();
}
void loop(){
  digitalWrite(signal_pin,LOW);
  WiFiClient client=Server.available();
  if(client){
    disupdate("Client Connected");
    digitalWrite(signal_pin,HIGH);
    while(client.connected()){
      if(client.available()){
        String text=client.readStringUntil('\n');
        disupdate("Data is comming");
        if (text=="1") {
        disupdate("Block in Thiruvalla");
        }
        if (text=="2") {
        disupdate("Block in Kattode");
        }
        if (text=="3") {
        disupdate("Block in Kuttoor");
        }
        if (text=="4") {
        disupdate("Block in Market");
        }
        blink(100);
      }
      delay(10);
    }
  client.stop();
  disupdate("Client Stoped...!");
  }
}
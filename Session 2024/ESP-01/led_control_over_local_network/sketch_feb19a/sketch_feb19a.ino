#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

/* Put your SSID & Password */
const char* ssid = "Cortex02";       
const char* password = "123456789"; 

ESP8266WebServer server(80);

#define LED_PIN     5
#define NUM_LEDS    60
#define violet      (143,0,255)
#define cyan        (0,255,255)
#define red         (255,0,0)
#define blue        (0,0,255)
#define off         (0,0,0)
#define m_delay       40  // 40

CRGB leds[NUM_LEDS];
bool LEDstatus = LOW;

void setup() {  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT); 
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Access Point IP:");
  Serial.println(myIP);
  
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  //Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
  
  if(LEDstatus)
  {
    digitalWrite(LED_PIN, HIGH);
    for (int i = 0; i <= NUM_LEDS; i++) 
    {
      leds[i] = CRGB off;
      FastLED.show();
      delay(m_delay);
    }
    // for (int i = 0; i <= NUM_LEDS; i++) 
    // {
    //   leds[i] = CRGB violet;
    //   FastLED.show();
    //   delay(m_delay);
    // }
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    for (int i = 0; i <= NUM_LEDS; i++) 
    {
      leds[i] = CRGB cyan;
      FastLED.show();
      delay(m_delay);
    }
  }
}

void handle_OnConnect() {
  LEDstatus = LOW;
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledon() {
  LEDstatus = HIGH;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledoff() {
  LEDstatus = LOW;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String updateWebpage(uint8_t LEDstatus){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #3498db;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  
   if(LEDstatus){
    ptr +="<p>LED: OFF</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
   }else{
    ptr +="<p>LED: ON</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
  }

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
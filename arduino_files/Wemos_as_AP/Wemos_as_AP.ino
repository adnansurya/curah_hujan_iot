#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "TESDOANG"
#define STAPSK  "12345678"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);
int sensor1=0, sensor2=0, sensor3=0, sensor4=0, sensor5=0;
String informasi = "";

void handleRoot() {

  server.send(200, "text/html", "Ini Server");

}

void handleNotFound() {
  
  server.send(404, "text/html", "Page Not Found");

}

void sensor1get() {
  if (server.method() != HTTP_GET) {   
    server.send(405, "text/plain", "Method Not Allowed");   
  } else {   
    informasi = server.arg("value"); 
    sensor1 = informasi.toInt();  
    server.send(200, "text/plain", "GET body was:\n" + server.arg("value"));    
  }
}

void sensor2get() {
  if (server.method() != HTTP_GET) {   
    server.send(405, "text/plain", "Method Not Allowed");   
  } else {   
    informasi = server.arg("value"); 
    sensor2 = informasi.toInt();  
    server.send(200, "text/plain", "GET body was:\n" + server.arg("value"));    
  }
}
void sensor3get() {
  if (server.method() != HTTP_GET) {   
    server.send(405, "text/plain", "Method Not Allowed");   
  } else {   
    informasi = server.arg("value"); 
    sensor3 = informasi.toInt();  
    server.send(200, "text/plain", "GET body was:\n" + server.arg("value"));    
  }
}
void sensor4get() {
  if (server.method() != HTTP_GET) {   
    server.send(405, "text/plain", "Method Not Allowed");   
  } else {   
    informasi = server.arg("value"); 
    sensor4 = informasi.toInt();  
    server.send(200, "text/plain", "GET body was:\n" + server.arg("value"));    
  }
}
void sensor5get() {
  if (server.method() != HTTP_GET) {   
    server.send(405, "text/plain", "Method Not Allowed");   
  } else {   
    informasi = server.arg("value"); 
    sensor5 = informasi.toInt();  
    server.send(200, "text/plain", "GET body was:\n" + server.arg("value"));    
  }
}
void setup(void) {
 
  Serial.begin(115200);
 WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/sensor1", sensor1get);
  server.on("/sensor2", sensor2get);
  server.on("/sensor3", sensor3get);
  server.on("/sensor4", sensor4get);
  server.on("/sensor5", sensor5get);
  
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  
 server.handleClient();
 Serial.print("Sensor 1:");
 Serial.print(sensor1);
  Serial.print(" Sensor 2:");
 Serial.print(sensor2);
  Serial.print(" Sensor 3:");
 Serial.print(sensor3);
  Serial.print(" Sensor 4:");
 Serial.print(sensor4);
  Serial.print(" Sensor 5:");
 Serial.println(sensor5);
 delay(1000);
 
}

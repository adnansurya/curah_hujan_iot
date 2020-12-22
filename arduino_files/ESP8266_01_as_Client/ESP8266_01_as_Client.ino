
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#ifndef STASSID
#define STASSID "TESDOANG"
#define STAPSK  "12345678"
#endif

#define KODE 3


const char* ssid = STASSID;
const char* password = STAPSK;

const char *host = "192.168.4.1";
const int httpsPort = 80;


String informasi = "";
void setup() {


  Serial.begin(9600);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 

  Serial.println("Ready..");

}

void loop() {
  
 while(Serial.available() > 0){
    informasi = Serial.readStringUntil('\n');
    pushToServer(KODE, informasi);
     
  }

}


void pushToServer(int kodeSensor, String hasilUkur){
  HTTPClient http;    //Declare object of class HTTPClient

  String getData, Link; 

  //GET Data
  getData = "?value=" + hasilUkur ;  //Note "?" added at front
  Link = "http://192.168.4.1/sensor"+String(kodeSensor) + getData;
  
  http.begin(Link);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(Link);
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  
  delay(1000);  //GET Data at every 5 seconds
  
}

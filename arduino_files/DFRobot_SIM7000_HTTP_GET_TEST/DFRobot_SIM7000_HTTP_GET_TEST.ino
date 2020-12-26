 /*
  * File  : DFRobot_SIM7000_HTTP.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example verify HTTP connection over a HTTP request
  *         With initialization completed, we connect to server POST data and GET data
  *         Thus we finished the HTTP POST and GET verification
  * Note  : If you use NB-IOT please confirm that the IOT is in the whitelist of your NB card
  *         If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8

//This URL is use for get data from tlink, please change the SENSORID to your sensorsId
#define GETURL    "betaku.000webhostapp.com/curahujan/submit.php?sen1=99&sen2=99&sen3=99&sen4=99&sen5=99&waktu=rabu"

SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000;

void setup(){
    int signalStrength,dataNum;
    Serial.begin(115200);
    while(!Serial);
    sim7000.begin(mySerial);
    Serial.println("Turn ON SIM7000......");
    if(sim7000.turnON()){                                    //Turn ON SIM7000
        Serial.println("Turn ON !");
    }

    Serial.println("Set baud rate......");
    while(1){
        if(sim7000.setBaudRate(19200)){                      //Set SIM7000 baud rate from 115200 to 19200 reduce the baud rate to avoid distortion
            Serial.println("Set baud rate:19200");
            break;
        }else{
            Serial.println("Faile to set baud rate");
            delay(1000);
        }
    }

    Serial.println("Check SIM card......");
    if(sim7000.checkSIMStatus()){                            //Check SIM card
        Serial.println("SIM card READY");
    }else{
        Serial.println("SIM card ERROR, Check if you have insert SIM card and restart SIM7000");
        while(1);
    }

    Serial.println("Set net mode......");
    while(1){
        if(sim7000.setNetMode(GPRS)){                        //Set net mod GPRS
            Serial.println("Set GPRS mode");
            break;
        }else{
            Serial.println("Fail to set mode");
            delay(1000);
        }
    }

    Serial.println("Get signal quality......");
    signalStrength=sim7000.checkSignalQuality();             //Check signal quality from (0-30)
    Serial.print("signalStrength =");
    Serial.println(signalStrength);
    delay(500);

    Serial.println("Attaching service......");
    while(1){
        if(sim7000.attacthService()){                        //Open the connection
            Serial.println("Attach service");
            break;
        }else{
            Serial.println("Fail to Attach service");
            delay(1000);
        }
    }

    Serial.println("Init http......");
    while(1){
        if(sim7000.httpInit(GPRS)){                          //Init http service
            Serial.println("HTTP init !");
            break;
        }else{
            Serial.println("Fail to init http");
        }
    }



    Serial.print("GET from ");
    Serial.println(GETURL);
    sim7000.httpGet(GETURL);                                 //HTTP GET

    Serial.println("Disconnect");
    sim7000.httpDisconnect();                                //Disconnect
    Serial.println("Close net work");
    sim7000.closeNetwork();                                  //Close net work
    Serial.println("Turn off SIM7000");
    sim7000.turnOFF();                                       //Turn OFF SIM7000
}

void loop() {
    delay(1000);
}

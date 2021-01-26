#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>


RTC_DS3231 rtc;
LiquidCrystal_I2C lcd (0x27,20,4); 

File myFile;

char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String waktu = "", jarak;

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    lcd.print("Couldn't find RTC");
    while (1);
  }else{
    lcd.print("RTC OK!");
  }

  lcd.setCursor(0,0);
  if (rtc.lostPower()) {
        lcd.print("RTC lost power, lets set the time!");
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));     // following line sets the RTC to the date & time this sketch was compiled
    
    // Set the current date, and time in the following format:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));     // This line sets the RTC with an explicit date & time, for example to set
  }else{
     lcd.print("RTC OK!");
  }

  lcd.setCursor(0,2);
  if (!SD.begin(53)) { //tergantung di pin chipselect yang digunakan
    Serial.println("Gagal baca microSD!");
    lcd.print("Gagal baca microSD!");
    return;
  }else{
    Serial.println("Sukses baca kartu microSD!");
    lcd.print("MicroSD Terbaca!");
  }
  
  myFile = SD.open("SENSOR.csv", FILE_WRITE); //menulis File coba.txt
 
  // jika file sudah berhasil dibuka maka tulis data dimulai
  lcd.setCursor(0,2);
  if (myFile) {

    myFile.println("HARI;TANGGAL;WAKTU;SENSOR 1;SENSOR 2;SENSOR 3;SENSOR 4;SENSOR 5;");
    myFile.close();
  } else {
    // jika gagal print error
    Serial.println("GAGAL TULIS.txt");
    lcd.print("GAGAL TULIS.txt");
  }

  lcd.clear();
  delay(3000);
}
String dataMasuk = "";

void loop() {
  // read from port 1, send to port 0:
 while(Serial1.available()>0){
    dataMasuk = Serial1.readStringUntil('\n');
    dataMasuk.trim();
    Serial.println("Data Masuk : " + dataMasuk);

lcd.clear();
       
    myFile = SD.open("SENSOR.csv", FILE_WRITE);

    lcd.setCursor(0,3);
    if(myFile){
      lcd.print("Micro SD OK!"); 
    }else{
      lcd.print("Micro SD ERROR!"); 
    }

     lcd.setCursor(0,2);
       lcd.print(dataMasuk);

    DateTime now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(", ");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print('|');
    myFile.print(daysOfTheWeek[now.dayOfTheWeek()]);
    myFile.print(';');
    
    
    lcd.print(now.day(), DEC);
    lcd.print('/');
    Serial.print(now.day(), DEC);
    Serial.print('/');
    myFile.print(now.day(), DEC);
    myFile.print('/');
    
    
    lcd.print(now.month(), DEC);
    lcd.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    
    
    lcd.print(now.year(), DEC);
    
    Serial.print(now.year(), DEC);
    Serial.print('|');
    myFile.print(now.year(), DEC);
    myFile.print(';');
    

    lcd.setCursor(0,1);
    lcd.print("WAKTU : ");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    
    
    lcd.print(now.minute(), DEC);
   // lcd.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    
    
  //lcd.print(now.second(), DEC);

    Serial.print(now.second(), DEC);
    Serial.print('|');
    myFile.print(now.second(), DEC);
    myFile.print(';');
    myFile.print(dataMasuk);
      myFile.println(';');
      
    
     
     myFile.close();
     while(Serial2.available()>0){
      String perintah = Serial2.readStringUntil('\n');
      perintah.trim();
      if(perintah == "Ready to Send" || perintah == "Disconnect"){
            Serial2.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial2.print(',');
    Serial2.print(now.day(), DEC);
    Serial2.print('/');
    Serial2.print(now.month(), DEC);
    Serial2.print('/');
    Serial2.print(now.year(), DEC);
    Serial2.print(' ');

    Serial2.print(now.hour(), DEC);
    Serial2.print(':');
    Serial2.print(now.minute(), DEC);
    Serial2.print(':');
    Serial2.print(now.second(), DEC);
    Serial2.print(';');
    Serial2.println(dataMasuk);
   
      } 
     }
    
//   delay(30000);
  }
}

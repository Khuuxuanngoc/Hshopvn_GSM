/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Muc tieu dat ra: Giao tiep giua PC voi Module Sim thong qua Arduino
Target: Communicating from PC to GSM-module.
******

IMPORTAN: Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********

Tutorial: 
********

Code download:  https://github.com/Khuuxuanngoc/Hshopvn_GSM
Link product:   http://hshop.vn/products/mach-gsmsim800ds-toch-hop-nguon-va-ic-dem

P/S:  1/ Choosing "Both NL & CR" and "9600" baudrate!
      2/ Type "AT" then enter to see result -. it 'll be return "OK"
      3/ Type the same other AT command
      4/ Type "-Z" to send CTRL+Z [Used in SMS AT command]
      
Update: 7/2/2017
***********************************************************************************************/
#include <SoftwareSerial.h>

SoftwareSerial sim(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sim.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String tempString = "";
    tempString = Serial.readStringUntil('\n');

    if(tempString.indexOf("-Z")>-1){
      sim.write(26);
      Serial.println("Ctr+Z");
    }else{
      sim.println(tempString);
    }
  }else;
  
  if(sim.available()){
    Serial.write(sim.read());
  }else;
}

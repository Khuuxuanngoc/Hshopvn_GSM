/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Dao trang thai relay khi so dien thoai goi den hop le.
Decription: Reversing state of relay when phone number (comming) is valid.
******

IMPORTAN: - Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********  - Replace delay [origin] by *.delay [example: HGSM.delay(1000)]
          - DO NOT use "delay" or "*.delay" in "GSM_Ready" [it seems to be interrupt when data is comming [.getDataGSM] from GSM]

Tutorial:
********

Code download:  https://github.com/Khuuxuanngoc/Hshopvn_GSM
Link product:   http://hshop.vn/products/mach-gsmsim800ds-toch-hop-nguon-va-ic-dem

P/s: Remember SET country code if you are NOT in VietNam
***********************************************************************************************/
#include "SoftwareSerial.h"
#include "Hshopvn_GSM.h"

// Declare Library:
SoftwareSerial sim800ds(2, 3);
HshopGSM HGSM = HshopGSM(&sim800ds);

// Declare phone number 
unsigned long UL_PhoneNum = 938022500;  // "0938022500" or "+84938022500"

// Declare pin:
unsigned char Relay_pin = 13;
unsigned char Relay_active = 0; // Relay active LOW
//

void setup() {
  // put your setup code here, to run once:
  // Pin init:
  pinMode(Relay_pin,OUTPUT);
  digitalWrite(Relay_pin, !Relay_active);  // turn off relay
  
  //Only show monitor
  Serial.begin(9600);
  Serial.println("Start!!");
  
  // Init library:
  HGSM.init(&GSM_Ready, 9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
}

void GSM_Ready() {
  if (HGSM.getDataGSM() != "") {
    Serial.println(HGSM.getDataGSM());  //show data comming
    if(HGSM.checkData(UL_PhoneNum)){
      Serial.println("Detect my vailid Number!");
      
      HGSM.hangcall();
      digitalWrite(Relay_pin,!digitalRead(Relay_pin));
    }else;
  } else;
}

/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Goi SMS den SDT 0938022500.
Decription: Sending SMS to 0938022500.
******

IMPORTAIN: - Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********  - Replace delay [origin] by *.delay [example: HGSM.delay(1000)]


Tutorial:
********

Code download:  https://github.com/Khuuxuanngoc/Hshopvn_GSM
Link product:   http://hshop.vn/products/mach-gsmsim800ds-toch-hop-nguon-va-ic-dem

P/s: Remember SET country code if NOT in VietNam
***********************************************************************************************/
#include "SoftwareSerial.h"
#include "Hshopvn_GSM.h"

SoftwareSerial sim800ds(2, 3);
HshopGSM HGSM = HshopGSM(&sim800ds);

String Str_PhoneNum = "0938022500";
unsigned long UL_PhoneNum = 938022500;

void setup() {
  // put your setup code here, to run once:
  //Only show monitor
  Serial.begin(9600);
  Serial.println("Start!!");

  // Init Country code default: VietNam (+84)
  HGSM.init(&GSM_Ready, 9600);


  //Send SMS with phone number as String
  HGSM.sendsms(Str_PhoneNum, "Hshopvn test GSM ");

  // Or send SMS with phone number as unsigned long
  // HGSM.sendsms(UL_PhoneNum, "Hshopvn test GSM ");
}


void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
}

void GSM_Ready() {
  if (HGSM.getDataGSM() != "") {
    Serial.println(HGSM.getDataGSM());  //show data comming
  } else;
}
/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Goi den SDT 0938022500 15s sau do gac may.
Decription: Making a call to 0938022500 during 15s then hang up.
******

IMPORTAN: - Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********  - Replace delay [origin] by *.delay [example: HGSM.delay(1000)]
          - DO NOT use "delay" or "*.delay" in "UserFunction" [it seems to be interrupt when data is comming [.getDataGSM] from GSM]

Tutorial:
********

Code download:  https://github.com/Khuuxuanngoc/Hshopvn_GSM
Link product:   http://hshop.vn/products/mach-gsmsim800ds-toch-hop-nguon-va-ic-dem

P/s: Remember SET country code if you are NOT in VietNam
***********************************************************************************************/
#include "SoftwareSerial.h"
#include "Hshopvn_GSM.h"

SoftwareSerial sim800ds(2, 3);
HshopGSM HGSM = HshopGSM(&sim800ds);

String Str_PhoneNum = "0938022500";
unsigned long UL_PhoneNum = 938022500;

void UserFunction() {
  if (HGSM.getDataGSM() != "") {
    Serial.println(HGSM.getDataGSM());
  } else;
}

void setup() {
  // put your setup code here, to run once:
  //Only show monitor
  Serial.begin(9600);
  Serial.println("Start!!");

  // Init Country code default: VietNam (+84)
  HGSM.init(&UserFunction, 9600);

  //or Set Country code.
  //    HGSM.init(&UserFunction, 9600,"+84");

  //Make the call with phone number as String
  HGSM.call(Str_PhoneNum);
  HGSM.delay(15000);

  //Hang up a call
  HGSM.hangcall();
  HGSM.delay(1000);

  //phone number as unsigned long (save memmory), if your number <= 10 characters.
  HGSM.call(UL_PhoneNum);
  HGSM.delay(15000);
  HGSM.hangcall();
  HGSM.delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
}


/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Khung chuong trinh tối giản.
Decription: Making a call to 0938022500 during 15s then hang up.
******

IMPORTAN: - Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********  - Replace delay [origin] by *.delay [example: HGSM.delay(1000)]
          - DO NOT use "delay" or "*.delay" in "UserFunction" [it seems to be interrupt when data is comming [.getDataGSM] from GSM]

Tutorial:
********

Code download:  https://github.com/Khuuxuanngoc/Hshopvn_GSM
Link produce:   http://hshop.vn/products/mach-gsmsim800ds-toch-hop-nguon-va-ic-dem

P/s: Remember SET country code if you are NOT in VietNam
***********************************************************************************************/
#include "SoftwareSerial.h"
#include "Hshopvn_GSM.h"

SoftwareSerial sim800ds(2, 3);
HshopGSM HGSM = HshopGSM(&sim800ds);

void UserFunction() {
  if (HGSM.getDataGSM() != "") {
    
  } else;
}

void setup() {
  // put your setup code here, to run once:

  // Init Country code default: VietNam (+84)
  HGSM.init(&UserFunction, 9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
}


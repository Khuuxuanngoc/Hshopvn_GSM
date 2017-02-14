/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Dung dien thoai gui tin SMS voi noi dung phu hop voi tu khoa trong mang KeyWordON[x] de bat thiet bi x (Relay_pin[x]) hoac trong mang KeyWordOF[x] de tat thiet bi x (Relay_pin[x]).
Decription: If SMS has content that match array KeyWordON or KeyWordOF, it will turn on or turn off relay.
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

// Declare pin of relays:
unsigned char Relay_pin[8] = {5, 6, 7, 8, 9, 10, 11, 12};
unsigned char Relay_active = 0; // Relay active LOW
String KeyWordON[8] = {"ON1", "ON2", "ON3", "ON4", "ON5", "ON6", "ON7", "ON8"};
String KeyWordOF[8] = {"OF1", "OF2", "OF3", "OF4", "OF5", "OF6", "OF7", "OF8"};

void UserFunction() {
  if (HGSM.getDataGSM() != "") {
//    Serial.println(HGSM.getDataGSM());

    for (unsigned char count_for = 0; count_for < 8; count_for++) {
      if (HGSM.checkData(KeyWordOF[count_for])) {            // if Key word (turn off) match
        digitalWrite(Relay_pin[count_for], !Relay_active);   // Turn off relay
        Serial.println("I turn off relay: " + String(count_for));
      } else if (HGSM.checkData(KeyWordON[count_for])) {     // if Key word (turn on) match
        digitalWrite(Relay_pin[count_for], Relay_active);    // Turn on relay
        Serial.println("I turn on relay: " + String(count_for));
      } else;
    }

  } else;
}

void setup() {
  // put your setup code here, to run once:
  // Relay init:
  for (unsigned char count_for = 0; count_for < 8; count_for++) {
    pinMode(Relay_pin[count_for], OUTPUT);
    digitalWrite(Relay_pin[count_for], !Relay_active);  // turn off relay
  }

  //Only show monitor
  Serial.begin(9600);
  Serial.println("Start!!");

  // Init Country code default: VietNam (+84)
  HGSM.init(&UserFunction, 9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
}


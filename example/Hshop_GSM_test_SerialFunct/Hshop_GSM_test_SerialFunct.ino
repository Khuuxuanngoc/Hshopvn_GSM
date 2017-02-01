#include "Hshopvn_GSM.h"
HshopGSM HshopGSM;

JOB ff;

void func(HardwareSerial &refSer)
{
   refSer.println("ref to ser");
}


void setup() {
  // put your setup code here, to run once:
	HshopGSM.init();
  Serial.begin(9600);
  Serial.println("Serial declare!");

  func(Serial1);
}

void loop() {
  // put your main code here, to run repeatedly:

}

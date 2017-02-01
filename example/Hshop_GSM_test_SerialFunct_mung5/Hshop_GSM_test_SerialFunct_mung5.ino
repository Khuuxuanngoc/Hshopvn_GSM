#include "Hshopvn_GSM.h"

HardwareSerial *refSer0;
SoftwareSerial kk(10,11);

//HshopGSM HGSM = HshopGSM(&Serial);
HshopGSM HGSM = HshopGSM(&kk);


void (*pvoid)() = NULL;

String SDT= "01219012347";

unsigned long timetest =0;
unsigned char count=0;

void kxnF(){
	if(HGSM.getDataGSM() != ""){
		Serial.println(HGSM.getDataGSM());
	}else;
	
	if(millis() - timetest >=100){
		timetest = millis();
		Serial.println("kxn Funct running!" + String(count++));
	}
}

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("Start!!");
	
	// HGSM.setUserFunct(&kxnF);
	HGSM.set_timeWaitRespond(1500);
	
	HGSM.init(&kxnF, 9600, "+223");
	
	HGSM.call("01219012347");
	HGSM.holdcall();
	// delay(1000);
	
	
	
  
	// unsigned long nump=1219012347;
	// HGSM.call(nump);
  
	// int pos__1 = 1;
	// HGSM.deleteSms(pos__1);
  
	// unsigned int pos__2 = 2;
	// HGSM.deleteSms(pos__2);
  
	// unsigned char pos__0 = 0;
	// HGSM.deleteSms(pos__0);
}


void loop() {
  // put your main code here, to run repeatedly:
	// Serial.println(count++);
  HGSM.handle();
  HGSM.sendsms(SDT,"Test sms");
  // if(count==240)
	// pvoid();  
	
	// delay(10);
}

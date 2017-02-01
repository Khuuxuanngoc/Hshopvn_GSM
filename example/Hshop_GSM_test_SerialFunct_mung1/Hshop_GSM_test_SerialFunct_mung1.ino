#include "Hshopvn_GSM.h"

HardwareSerial *refSer0;
SoftwareSerial kk(10,11);

//HshopGSM HGSM = HshopGSM(&Serial);
HshopGSM HGSM = HshopGSM(&kk);

// JOB ff;

#define ena

#define num_ 7

#ifdef ena
  #if num_ >=10
    void func(HardwareSerial &refSer)
    {
       refSer.println("ref to ser >=10");
    }
  #else
    void func(HardwareSerial &refSer)
    {
       refSer.println("ref to ser <=9");
    }
  #endif
//#else

#endif

//void func2(SoftwareSerial &refSer)
//{
//   refSer.println("ref to ser >=100");
////   refSer->println("ref to ser >=100");
//}

String SDT= "01219012347;";

// enum Color { red, green, blue };
// Color r = red;
// Color r1 = red;
// Color r2 = red;

// typedef enum {
		// NOTHING_,
		// CHECK_AT,
		// CALLING,
		// SMS_SEND
// }ModeCm;			// error

enum{
		NOTHING_,
		CHECK_AT,
		CALLING,
		SMS_SEND
}ModeCm;

void kxnF(){
	if(HGSM.getData != ""){
		Serial.println(HGSM.getData);
	}
}

void setup() {
  // put your setup code here, to run once:
	// HGSM.makeDebug(&Serial,9600);
	HGSM.init(9600,"+223");
	HGSM.setUserFunct(&kxnF);
	HGSM.set_timeWaitRespond(3000);
	
	
  refSer0= &Serial;
  Serial.begin(9600);
  
//  kk.begin(9600);

  Serial.println("start enum");
  Serial.println(HGSM.CountryCode);
  ModeCm=CHECK_AT;
  
  Serial.println(ModeCm);
  ModeCm=CALLING;
  Serial.println(ModeCm);
  ModeCm=SMS_SEND;
  Serial.println(ModeCm);
  Serial.println("end enum");
  
	String at = "AT";
	String crlf="\r\n";
	
  refSer0->println(at+crlf);
  
  func(Serial);
  HGSM.call("01219012347");
  
  unsigned long nump=1219012347;
  HGSM.call(nump);
  
  int pos__1 = 1;
  HGSM.deleteSms(pos__1);
  
  unsigned int pos__2 = 2;
  HGSM.deleteSms(pos__2);
  
  unsigned char pos__0 = 0;
  HGSM.deleteSms(pos__0);
  
//  func2(&Serial);
//  func2(kk);    //error
}

void loop() {
  // put your main code here, to run repeatedly:
	// if(kk.available()){
		// Serial.print((char)kk.read());
		// delay(5);
	// }
  HGSM.handle();
}

#ifndef _HSHOP_GSM_
#define _HSHOP_GSM_

// #define hardwareSerial
#define GSML_DB

#if (ARDUINO >= 100)
	#include "Arduino.h"
	#ifndef hardwareSerial
		#include <SoftwareSerial.h>
	#endif
#else
	#include "WProgram.h"
	#ifndef hardwareSerial
		#include <NewSoftSerial.h>
	#endif
#endif

/***********************************************************************
		Chon cong SERIAL de ket noi
************************************************************************
	#define hardwareSerial =>	TX_pin = 1, RX_pin = 0
						Or
	//#define hardwareSerial =>	TX_pin = 3, RX_pin = 2
************************************************************************/

class HshopGSM{
	protected:
		String getData;
	public:
	
	#ifdef hardwareSerial
		HshopGSM(HardwareSerial *refSer);
	#else
		#if ARDUINO >= 100
		  HshopGSM(SoftwareSerial *refSer);
		#else
		  HshopGSM(NewSoftSerial *refSer);
		#endif
	#endif
	
	#ifdef hardwareSerial
		HardwareSerial *myGMS;
	#else
		#if ARDUINO >= 100
		  SoftwareSerial *myGMS;
		#else
		  NewSoftSerial *myGMS;
		#endif
	#endif
	
	#ifdef GSML_DB
		#define DBshow(x)	Serial.print(x)
		#define DBshown(x)	Serial.println(x)
	#else
		#define DBshow(x)	
		#define DBshown(x)	
	#endif
	
	void DB_init();
	
	void init(void (*p_void_)(), uint16_t baud, String _CountryCode);	// Khi dung o nuoc ngoai
	void init(void (*p_void_)(), uint16_t baud);
	void Re_init();
	void call(String _callNumber);
	void call(unsigned long _callNumber);
	void holdcall();
	void sendsms(String _callNumber,String _content);
	void sendsms(unsigned long _callNumber,String _content);
	void deleteSms(unsigned char);
	void atcm(String);
	void read();
	void Setbaud(uint16_t baud);
	void set_timeWaitRespond(unsigned long);
	void setUserFunct(void (*_p_UserFunct)());
	void handle();
	void checkConnect();
	void GSM_funct();
	String getDataGSM();
	
	void (*p_UserFunct)();
	void VitualFunction();
	
	String at;
	String crlf;
	String atd;
	String CountryCode;
	
	unsigned long ul_timeWaitResp;
	unsigned long ul_timeCheckConnect;
	bool isGetdata;
	unsigned char uc_CountErr;		// if 	uc_CountErr = 2 -> Re_init().
	enum _isRespond{
		_no_act,
		_re_act,
		_tr_act
	};
	_isRespond isSendSMS;
	_isRespond isRespond;
	
};

#endif		// end _HSHOP_GSM_

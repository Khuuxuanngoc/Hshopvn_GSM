/************************************************************************
Tác giả:		Khưu Xuân Ngọc
Email: 			xuanngoc1992@gmail.com
Website: 		http://hshop.vn/ 
Date:			02/02/2017
Link download:	https://github.com/Khuuxuanngoc/Hshopvn_GSM
Version:		1.0.0

*************************************************************************/
#ifndef _HSHOP_GSM_
#define _HSHOP_GSM_

// #define hardwareSerial
// #define GSML_DB

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
	
	void init(void (*p_void_)(), long baud, String _CountryCode);	// Khi dung o nuoc ngoai
	void init(void (*p_void_)(), long baud);
	void Re_init();
	void call(String _callNumber);
	void call(unsigned long _callNumber);
	void hangcall();
	void answer();
	void sendsms(String _callNumber,String _content);
	void sendsms(unsigned long _callNumber,String _content);
	void deleteSms(unsigned char);
	void atcm(String);
	void read();
	void Setbaud(long baud);
	void set_timeWaitRespond(unsigned long);
	void setUserFunct(void (*_p_UserFunct)());
	void handle();
	void checkConnect();
	void GSM_funct();
	void delay(unsigned long timeDelay);		// thay thế ham delay của Arduino
	void begin(long baud);
	
	String getDataGSM();
	void clearData();
	void addMoney(String _code);
	void checkMoney();							// Use in VietNam
	bool checkData(String StringNeedCheck);
	bool checkData(unsigned long NumberNeedCheck);
	
	String splitString(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset);
	
	void (*p_UserFunct)();
	void VitualFunction();
	
	String at;
	String crlf;
	String atd;
	String CountryCode;
	String UserData;
	
	unsigned long ul_timeWaitResp;
	unsigned long ul_timeCheckConnect;
	bool isGetdata;
	unsigned char uc_CountErr;		// nếu 	uc_CountErr = 2 -> Re_init().
	
	unsigned char isUser;
	unsigned char isSendSMS;
	unsigned char isRespond;
	bool isComplete;
	
	enum _isRespond{
		_no_act,
		_re_act,
		_tr_act
	};
	
};

#endif		// end _HSHOP_GSM_

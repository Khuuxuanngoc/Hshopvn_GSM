#include "Hshopvn_GSM.h"

#ifdef hardwareSerial
	HshopGSM::HshopGSM(HardwareSerial *refSer){
#else
	#if ARDUINO >= 100
	  HshopGSM::HshopGSM(SoftwareSerial *refSer){
	#else
	  HshopGSM::HshopGSM(NewSoftSerial *refSer){
	#endif
#endif
		myGMS = refSer;
		at = "AT+";
		crlf = "\r\n";
		atd = "ATD";
		ul_timeCheckConnect = millis();
		// p_UserFunct = &VitualFunction;
		set_timeWaitRespond(1000);
	  }

void HshopGSM::init(void (*p_void_)(), uint16_t baud, String _CountryCode){
	myGMS->begin(baud);
	setUserFunct(p_void_);
	DB_init();
	
	if(_CountryCode.indexOf("+")>-1){
		CountryCode = _CountryCode;
	}else{
		CountryCode = "+84";
	}
	
	Re_init();
}

void HshopGSM::init(void (*p_void_)(), uint16_t baud){
	myGMS->begin(baud);
	setUserFunct(p_void_);
	
	CountryCode = "+84";
	
	Re_init();
}

void HshopGSM::Re_init(){
	isGetdata = false;
	uc_CountErr = 0;
	
	/*Hien thi noi dung tin nhan truc tiep*/	
	atcm(at + "CMNI=2,2");
	
	/*Chon che do Text*/
	atcm(at + "CMGF=1");
	atcm(at + "CSCS=\"GSM\"");
	
	/* Hien thi SDT goi den*/
	atcm(at + "CLIP=1");
	
	getData = "";
	
	isSendSMS = _no_act;
	isRespond = _no_act;
}

void HshopGSM::call(String _callNumber){
	atcm(atd + _callNumber + ";");
}

void HshopGSM::call(unsigned long _callNumber){
	atcm(atd + CountryCode + _callNumber + ";");
}

void HshopGSM::holdcall(){
	atcm("ATH");
}

void HshopGSM::sendsms(String _callNumber,String _content){
	atcm(at + "CMGF=1");
	isSendSMS = _tr_act;
	atcm(at + "CMGS=\"" + _callNumber + "\"");
	if(isSendSMS == _re_act){
		myGMS->print(_content);
		myGMS->write(26);		// Ctrl + Z		see more Ascii table: http://www.asciitable.com/
		isSendSMS == _no_act;
	}else;
}

void HshopGSM::sendsms(unsigned long _callNumber,String _content){
	atcm(at + "CMGF=1");
	isSendSMS = _tr_act;
	atcm(at + "CMGS=\"" + String(_callNumber) + "\"");
	if(isSendSMS == _re_act){
		myGMS->print(_content);
		myGMS->write(26);		// Ctrl + Z		see more Ascii table: http://www.asciitable.com/
		isSendSMS == _no_act;
	}else;
}

void HshopGSM::deleteSms(unsigned char Pos_){
	if(Pos_ == 0){
		atcm(at + "CMGDA=\"DEL ALL\"");
	}else{
		atcm(at + "CMGD=" + String(Pos_));
	}
}

void HshopGSM::read(){
	char temp_char;
	
	while(myGMS->available() && (temp_char != '\n')){
		temp_char = myGMS->read();
		
		if(temp_char != '\n'){
			getData += temp_char;
			delayMicroseconds(200);
		}else;
	}
	
	if(getData.length() >2){
		isGetdata = true;
		
		GSM_funct();
		p_UserFunct();
		
		getData = "";
	}else;
}

void HshopGSM::atcm(String _atcm_){
	myGMS->print(_atcm_ + crlf);
	isRespond = _tr_act;
	isGetdata = false;
	unsigned long _gstart = millis();

	while(((millis() - _gstart) < ul_timeWaitResp) && isGetdata == false){
		read();
		p_UserFunct();
	}
	
	if(isGetdata == false){
		GSM_funct();
	}else;
}

/* Baud default: 9600 */
void HshopGSM::Setbaud(uint16_t baud){
	if(baud == 0 || baud == 1200 || baud == 2400 || baud == 4800 || baud == 9600 || baud == 19200 || baud == 38400 || baud == 57600 || baud == 115200){
		atcm(at+"IPR="+String(baud));
	}else{
		atcm(at+"IPR=9600");
	}
}

void HshopGSM::set_timeWaitRespond(unsigned long _set_time_wait){
	ul_timeWaitResp = _set_time_wait;
}

void HshopGSM::setUserFunct(void (*_p_UserFunct)()){
	p_UserFunct = _p_UserFunct;
}

void HshopGSM::handle(){
	read();
	
	if(millis() - ul_timeCheckConnect >=5000){
		ul_timeCheckConnect = millis();
		checkConnect();
		DBshow(uc_CountErr);
		DBshown(" Check connect");			// just for Debug
	}else;
}

void HshopGSM::checkConnect(){
	if(uc_CountErr >= 2){
		Re_init();
	}else;
}

void HshopGSM::GSM_funct(){
	if(isRespond == _tr_act){
		if(isSendSMS == _tr_act && getData.indexOf(">") > -1){
			isSendSMS = _re_act;
			isRespond = _re_act;
			getData = "";
			DBshown(">");
		}else if(getData.indexOf("OK") > -1){
			isRespond = _re_act;
			DBshown("G");
		}else{
			uc_CountErr++;
			isRespond = _no_act;
			DBshown("F");
			DBshown(uc_CountErr);
		}
	}else;
}

String HshopGSM::getDataGSM(){
	return getData;
}

#ifdef GSML_DB
	void HshopGSM::DB_init(){
		Serial.begin(9600);
		Serial.println("DEBUG GMS START!");
	}
	
#else
	void HshopGSM::DB_init(){
		
	}
#endif

void HshopGSM::VitualFunction(){
	// just make program work!
}
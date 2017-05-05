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
		set_timeWaitRespond(1000);
	  }

void HshopGSM::init(void (*p_void_)(), long baud, String _CountryCode){
	begin(baud);
	// myGMS->begin(baud);
	setUserFunct(p_void_);
	DB_init();
	
	if(_CountryCode.indexOf("+")>-1){
		CountryCode = _CountryCode;
	}else{
		CountryCode = "+84";
	}
	
	Re_init();
}

void HshopGSM::init(void (*p_void_)(), long baud){
	begin(baud);
	// myGMS->begin(baud);
	setUserFunct(p_void_);
	
	CountryCode = "+84";
	
	Re_init();
}

void HshopGSM::Re_init(){
	isGetdata = false;
	uc_CountErr = 0;
	
	/*Tat che do phan hoi*/
	atcm("ATE0");
	
	/*Bat che do hien thi thong tin cua nha mang*/
	atcm(at+"CUSD=1");
	
	/*Bat che do DTMF*/
	atcm(at+"DDET=1");
	
	/*Hien thi noi dung tin nhan truc tiep*/	
	atcm(at + "CNMI=2,2");
	
	/*Chon che do Text*/
	atcm(at + "CMGF=1");
	atcm(at + "CSCS=\"GSM\"");
	
	/* Hien thi SDT goi den*/
	atcm(at + "CLIP=1");
	
	getData = "";
	
	isSendSMS = _no_act;
	isRespond = _no_act;
	isUser = _no_act;
}

void HshopGSM::call(String _callNumber){
	atcm(atd + _callNumber + ";");
}

void HshopGSM::call(unsigned long _callNumber){
	atcm(atd + CountryCode + _callNumber + ";");
}

void HshopGSM::hangcall(){
	// myGMS->print("ATH"+crlf);
	atcm("ATH"+crlf);
}

void HshopGSM::answer(){
	// myGMS->print("ATA"+crlf);
	atcm("ATA"+crlf);
}

void HshopGSM::sendsms(String _callNumber,String _content){
	// atcm(at + "CMGF=1");
	isSendSMS = _tr_act;
	atcm(at + "CMGS=\"" + _callNumber + "\"");
	if(isSendSMS == _re_act){
		myGMS->print(_content);
		myGMS->write(26);		// Ctrl + Z		see more Ascii table: http://www.asciitable.com/
		isSendSMS == _no_act;
	}else;
}

void HshopGSM::sendsms(unsigned long _callNumber,String _content){
	// atcm(at + "CMGF=1");
	isSendSMS = _tr_act;
	atcm(at + "CMGS=\"" + CountryCode + String(_callNumber) + "\"");
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
			delayMicroseconds(1000);
			
		}else if(temp_char == '\n'){
			isComplete = true;
		}else;
	}
	
	if((getData.length() > 2) && isComplete == true){
		isGetdata = true;
		UserData += getData;
		GSM_funct();
		
		// if(isUser == _no_act){
			// isUser = _tr_act;
			// p_UserFunct();
			// isUser = _no_act;
		// }else;
		
		getData = "";
		isComplete = false;
	}else;
}

void HshopGSM::atcm(String _atcm_){
	myGMS->print(_atcm_ + crlf);
	// if(isUser == _no_act){
		isRespond = _tr_act;
		isGetdata = false;
		unsigned long _gstart = millis();

		while(((millis() - _gstart) < ul_timeWaitResp) && isGetdata == false){
			read();
			
			// isUser = _tr_act;
			// p_UserFunct();
			// isUser = _no_act;
		}
		
		if(isGetdata == false){
			GSM_funct();
		}else;
	// }else;
}

/* Baud default: 9600 */
void HshopGSM::Setbaud(long baud){
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
	
	if(isUser == _no_act){
		isUser = _tr_act;
		if(p_UserFunct != NULL){
			p_UserFunct();
		}else;
		isUser = _no_act;
		UserData = "";
	}else;
	// UserData = "";
	
	if(millis() - ul_timeCheckConnect >=5000){
		ul_timeCheckConnect = millis();
		checkConnect();
		// DBshow(uc_CountErr);
		// DBshown(" Check connect");			// just for Debug
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
			// DBshown(">");
		}else if(getData.indexOf("OK") > -1){
			isRespond = _re_act;
			// DBshown("G");
		}else{
			uc_CountErr++;
			isRespond = _no_act;
			// DBshown("F");
			// DBshown(uc_CountErr);
		}
	}else;
}

void HshopGSM::delay(unsigned long timeDelay){
	unsigned long temp_time = millis();
	while(millis() - temp_time < timeDelay){
		handle();
	}
}

void HshopGSM::begin(long baud){
	myGMS->begin(baud);
}

String HshopGSM::getDataGSM(){
	// return getData;
	return UserData;
}

void HshopGSM::clearData(){
	getData = "";
}

void HshopGSM::addMoney(String _code){
	myGMS->print(atd + "*100*" + _code + "#" + crlf);
}

void HshopGSM::checkMoney(){
	myGMS->print(atd + "*101#" + crlf);
}

bool HshopGSM::checkData(String StringNeedCheck){
	if(UserData.indexOf(StringNeedCheck)>-1){
	// if(getData.indexOf(StringNeedCheck)>-1){
		return true;
	}else{
		return false;
	}
}

bool HshopGSM::checkData(unsigned long NumberNeedCheck){
	if(UserData.indexOf(String(NumberNeedCheck))>-1){
		return true;
	}else{
		return false;
	}
}

String HshopGSM::splitString(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset){
	unsigned char lenOfCommand=v_G_Command.length();
    unsigned char posOfCommand=v_G_motherString.indexOf(v_G_Command);
    int PosOfStartSymbol=v_G_motherString.indexOf(v_G_Start_symbol,posOfCommand+lenOfCommand);
	
    while(v_G_Offset>0){
        v_G_Offset--;
        PosOfStartSymbol=v_G_motherString.indexOf(v_G_Start_symbol,PosOfStartSymbol+1);
    }
	
    int PosOfStopSymbol=v_G_motherString.indexOf(v_G_Stop_symbol,PosOfStartSymbol+1);
	
	return v_G_motherString.substring(PosOfStartSymbol+1,PosOfStopSymbol);
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

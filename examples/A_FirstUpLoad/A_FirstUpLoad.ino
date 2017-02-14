/*7/2/2017
Only Upload and wait!
*/

#include <SoftwareSerial.h>

SoftwareSerial sim800ds(2, 3);

unsigned long timeTest = 0;

long baudArray[7]={9600,2400,4800,19200,38400,57600,115200};

uint8_t countArray=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start scan baudrate!");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Set baud: " + String(baudArray[countArray]));
  sim800ds.begin(baudArray[countArray]);
  
  readSim(baudArray[countArray]);
  
  if(countArray < 6){
    countArray++;
  }else{
    Serial.println("___Fail___");
    Serial.println("Please check connect again!");
    countArray = 0;
  }
}

void readSim(long _baud){
  unsigned long Starttime=millis();
  String tempdata= "";
  bool stopwhile = false;
  sim800ds.print("AT+IPR=9600\r\n");
  while((millis() - Starttime <=400)){
    if(sim800ds.available()){
      char uu = sim800ds.read();
      delay(1);
      tempdata += uu;
    }else;
  }
  
  sim800ds.print("AT+IPR=9600\r\n");
  Starttime=millis();
  while((millis() - Starttime <=400)){
    if(sim800ds.available()){
      char uu = sim800ds.read();
      tempdata += uu;
    }else;
  }
  
  if(tempdata.indexOf("OK") > -1){
    Serial.println(" Finished OK " + String(_baud));
    if(_baud != 9600){
      Serial.println(" Reset to " + String(_baud));
    }else;
    while(1);
  }else;
}

#include <TimerOne.h>
#include "EmonLib.h"
boolean interrupt = false;
boolean displayed = false;
int i=0;
int counter=0;
boolean flag=0;
unsigned long time;
unsigned long loopCount=0;
unsigned long beforeTime=0;
unsigned long afterTime=0;
EnergyMonitor emon1;

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
    delay(1000);
  }
  Timer1.initialize(50000);
  Timer1.attachInterrupt(sensorInterrupt);
  emon1.current(1,5.55);  
}

void sensorInterrupt(void){

    interrupt=true;

}
void loop(void) {
  // put your main code here, to run repeatedly:
  float Irms=emon1.calcIrms(100);
  
  if(Serial.available()){
      char ch=Serial.read();
      if(ch=='s'){
        flag=1;
      }else if(ch=='d'){
        flag=0;
      }else if(ch=='w'){
        counter++;
      }
  }
  
  if(interrupt){
    interrupt=false;
        if (flag==1) {
    Serial.print(Irms,7);
    Serial.print(";");
    time=millis();
    Serial.print(time);
    Serial.print(";");
    Serial.println(counter);
    }
  }
  
}

#include<iostream>
#include<conio.h>
#include"Servo.cpp"
using namespace std;


class Servo{
private:
  int iCr;

public:
  uint8_t pIn;
  void attach(uint8_t nUm) ;      //F_CPU=clock frequency and num=pin no.to be attached
  void write(int vAl) ;          //PIN=servo pin no. on mega,vAl=angle F_CPU for the servo at pin
  void dettach(int pin1);                   //pin1=pin no. to be deattached
  long mapAngle(long x, long in_min, long in_max, long out_min, long out_max);
  long constraint(long nUm,long lOwer,long uPper);
    
}
  

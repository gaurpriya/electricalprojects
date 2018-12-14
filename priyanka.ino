
#define SERIAL_DEBUG //debugging serial port
//ANALOG A0 PIN TO POTENTIOMETER

#define ADC1 A0

//MAX7219 DIGITAL 10 PINS
#define DIN 22
#define CLOCK 26
#define LOAD 24

#include<LedControl.h>

//inputs:DIN pin, CLOCK pin,LOAD pin, no. of chips

LedControl mydisplay=LedControl(DIN,CLOCK,LOAD,1);
unsigned int val=0; //initialisation

void setup()
{
  mydisplay.shutdown(0,false);//turn on display
  mydisplay.setIntensity(0,15);//15=brightest
  mydisplay.setDigit(0,0,9,false);
  mydisplay.setDigit(0,1,8,false);
  mydisplay.setDigit(0,2,7,false);
  mydisplay.setDigit(0,3,6,false);
  mydisplay.setDigit(0,4,5,true);
  mydisplay.setDigit(0,5,4,false);
  mydisplay.setDigit(0,6,3,false);
  mydisplay.setDigit(0,7,2,false);

 #ifdef SERIAL_DEBUG
 Serial.begin(9600);//initializes the serial connection at 9600 bits per second.
 Serial.print("ten turn potentiometer test");//Prints data to the serial port as human-readable ASCII text.
 #endif
 //2 second delay
 delay(2000);
  
}

unsigned int num,one,ten,hundread=0;
void loop()
{
  //read the ten turn potentiometer input pin
  val=analogRead(A0);
  float converted = fmap(val,0,1023,0.0,5.00);

  #ifdef SERIAL_DEBUG
  Serial.println(converted);
  #endif
  //clear display
  mydisplay.clearDisplay(0);
  //display the ADC valueon max7219
  if(converted>0.0 && converted<=5.00)//for printing decimal values

  {
    num=converted*100;
    one=num%10;
    ten=(num/10)%10;
    hundread=(num/100)%10;
    mydisplay.setDigit(0,0,(byte)one,0);
    //mydisplay.setdigit(addr,digits,value,dp);
    mydisplay.setDigit(0,1,(byte)ten,0);
    mydisplay.setDigit(0,2,(byte)hundread,1);
  }
  //1000ms delay
  delay(1000);
  
}
//float interpolation function,for mapping the ADC reading
float fmap(float X,float in_min,float in_max,float out_min,float out_max)

{
  return(X-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}

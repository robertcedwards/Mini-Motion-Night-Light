/*
Attiny13 proximity sensor
by Dustin Andrews 2012
License: Creative Commons Unported http://creativecommons.org/licenses/by/3.0/
*/

//Do some low level AVR pin writing to save instructions. 1010 of 1024. Close!
#define SetPin(Bit)    PORTB |= (1 << Bit)
#define ClearPin(Bit)    PORTB &= ~(1 << Bit)


//wire your IR led to this pin. (chip pin 5?);
#define irOutPin 3

//This pin goes high when the sensor detects and obstacle. (chip pin 6)
#define outPin 1

// wire this pin to your phototrans vcc-->phototrans-->pin4-->1M res-->gnd(chip pin3)
#define sensorInPin 2


void setup()
{               
pinMode(irOutPin, OUTPUT);
pinMode(outPin, OUTPUT);
//pinMode(2, OUTPUT);
analogReference(0);//analogread won't work on Atiny13 w/o this line. Won't work on others WITH it prob'ly.
}

void loop()
{
static long difference = 0;
unsigned static long lastTime = 0;
SetPin(irOutPin);
delay1();
unsigned int r1 =  analogRead(sensorInPin);
ClearPin(irOutPin);
delay1();
unsigned int r2 = analogRead(sensorInPin);
difference += r1 - r2;

if(millis() - lastTime > 5)//might get a smoother response with bigger delays
{
   if(difference > 0)
   {
      SetPin(outPin);
   }
   else
   {
      ClearPin(outPin);    
   }
  
   difference = 0;
   lastTime = millis();
}
}

void delay1()
{
   //delay(1) is too costly in memory. Why is this so much cheaper? :D
long start = millis();
while(true)
{
   if(millis() - start > 1){break;}
}
}

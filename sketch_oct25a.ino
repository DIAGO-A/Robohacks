#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <Servo.h>

Servo servo;
Servo cervo;
int d,e,f,g=0;

char auth[] = "f3e31020607b4c18ad2f97771812d133";
char ssid[] = "Ayan@Home";
char pass[] = "AG_CO.LTD";



SimpleTimer timer;

int CountdownRemainReset;
int CountdownRemain;
int CountdownTimer;
int ay,by;
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  servo.attach(15); // NodeMCU D8 pin
cervo.attach(12); // NodeMCU D6 pin
pinMode(5,OUTPUT);
  CountdownTimer = timer.setInterval(1000, CountdownTimerFunction);
  timer.disable(CountdownTimer); 
}
void loop() {
  Blynk.run();
  timer.run();
}
void CountdownTimerFunction() {
  CountdownRemain--; // remove 1 every second
  CountdownShowFormatted(CountdownRemain);
  if (!CountdownRemain) { // check if CountdownRemain == 0/FALSE/LOW
    timer.disable(CountdownTimer); 
    Blynk.virtualWrite(1, LOW); 
    Blynk.virtualWrite(0, "TIMER COMPLETE");//here   
    if(ay==1)
    {Blynk.virtualWrite(0, "PUTTING OFF");
     Blynk.virtualWrite(V10,LOW);
  Blynk.virtualWrite(V11,LOW);
  Blynk.virtualWrite(V8,LOW);
  Blynk.virtualWrite(V23,35);
  Blynk.virtualWrite(V12,LOW);
  d=0;
  g=0;
  Blynk.virtualWrite(V3,LOW);
   servo.write(135);
    }
    else
    {Blynk.virtualWrite(0, "PUTTING 1"); 
    Blynk.virtualWrite(V11,LOW);
Blynk.virtualWrite(V8,LOW);
     Blynk.virtualWrite(V12,LOW);
     d=0;
  servo.write(0);
    }
  } 
}

BLYNK_WRITE(1) {
  if (param.asInt()) 
  {
     if (ay==1 or by==1 ) 
     {
    if (CountdownRemain) { 
      timer.enable(CountdownTimer);
      
    } else {
      Blynk.virtualWrite(1, LOW); 
      Blynk.virtualWrite(0, "TIME NOT SET");
    }
     }
   else 
  {
    Blynk.virtualWrite(0, "WORK NOT SET");
    Blynk.virtualWrite(1, LOW); 
    Blynk.virtualWrite(5, LOW); 
    Blynk.virtualWrite(6, LOW); 
    
  }
  }
  else 
  {
  timer.disable(CountdownTimer);
}
  }
BLYNK_WRITE(5)
{
  ay=param.asInt();
   Blynk.virtualWrite(6, LOW); 
}
BLYNK_WRITE(6)
{
  by=param.asInt();
   Blynk.virtualWrite(5, LOW); 
}

BLYNK_WRITE(4) {
  if (timer.isEnabled(CountdownTimer)) { // only update if timer not running
    Blynk.virtualWrite(4, param.asInt() ); // if running, refuse to let use change slider
  } else {
    CountdownRemainReset = param.asInt() * 60 + 1; // + 1 set the timer to 1:00:00 instead of 00:59:59
    CountdownRemain = param.asInt() * 60;
    CountdownShowFormatted(CountdownRemain);
  }
}

void CountdownShowFormatted(int seconds) {
  long days = 0;
  long hours = 0;
  long mins = 0;
  long secs = 0;
  String secs_o = ":";
  String mins_o = ":";
  String hours_o = ":";
  secs = seconds; 
  mins = secs / 60; 
  hours = mins / 60; 
  days = hours / 24; 
  secs = secs - (mins * 60); 
  mins = mins - (hours * 60); 
  hours = hours - (days * 24); 
  if (secs < 10) {
    secs_o = ":0";
  }
  if (mins < 10) {
    mins_o = ":0";
  }
  if (hours < 10) {
    hours_o = ":0";
  }
  Blynk.virtualWrite(0, days + hours_o + hours + mins_o + mins + secs_o + secs);

}
 BLYNK_WRITE(V23)
{
  e=param.asInt();
 if(d == 1)
 {servo.write(e);
  }
}
BLYNK_WRITE(V7)
{
  if (param.asInt()==1) {
    digitalWrite(5,HIGH);
    delay(1000);
    digitalWrite(5,LOW);
    cervo.write(45);
    
    }
}

BLYNK_WRITE(V8)
{ 
  if(g>0)
{d=param.asInt();
  Blynk.virtualWrite(V10,LOW);
  Blynk.virtualWrite(V12,LOW);
  Blynk.virtualWrite(V11,LOW);
  servo.write(0);
}
else
Blynk.virtualWrite(V8,LOW);
}
BLYNK_WRITE(V3)
{
   cervo.write(0);
   Blynk.virtualWrite(V10,HIGH);      //the total working will be done here
   Blynk.virtualWrite(V11,LOW);
    Blynk.virtualWrite(V12,LOW);
    Blynk.virtualWrite(V9,LOW);
    d=0;
    g=param.asInt();
    servo.write(0);

     
  
}

BLYNK_WRITE(V10)
{ if(g>0)
{
  Blynk.virtualWrite(V11,LOW);
Blynk.virtualWrite(V8,LOW);
     Blynk.virtualWrite(V12,LOW);
     d=0;
  servo.write(0);
}else
Blynk.virtualWrite(V10,LOW);

  
}
BLYNK_WRITE(V11)
{ if(g>0)
{
  Blynk.virtualWrite(V10,LOW);
Blynk.virtualWrite(V8,LOW);
     Blynk.virtualWrite(V12,LOW);
     d=0;
  servo.write(48);
  
  
}else
Blynk.virtualWrite(V11,LOW);
}
BLYNK_WRITE(V12)
{if(g>0)
{
   Blynk.virtualWrite(V11,LOW);
   Blynk.virtualWrite(V8,LOW);
     Blynk.virtualWrite(V10,LOW);
     d=0;
  servo.write(56);
 
}else
Blynk.virtualWrite(V12,LOW);
}
BLYNK_WRITE(V9)
{
 
  Blynk.virtualWrite(V10,LOW);
  Blynk.virtualWrite(V11,LOW);
  Blynk.virtualWrite(V8,LOW);
  Blynk.virtualWrite(V23,35);
  Blynk.virtualWrite(V12,LOW);
  d=0;
  g=0;
  Blynk.virtualWrite(V3,LOW);
   servo.write(135);
  
 
  
}


#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);  

int sensor = 8; 

unsigned long prevmillis; // To store time
unsigned long duration; // To store time difference
unsigned long lcdrefresh; // To store time for lcd to refresh

int rpm; 

boolean currentstate; // Current state of IR input scan
boolean prevstate; // State of IR sensor in previous scan

void setup()
{
  pinMode(sensor,INPUT);
  lcd.begin(16,2);     
  prevmillis = 0;
  prevstate = LOW;  
}

void loop()
{
 // RPM Measurement
  currentstate = digitalRead(sensor); // Read IR sensor state
 if( prevstate != currentstate) // If there is change in input
   {
     if( currentstate == HIGH ) // If input only changes from LOW to HIGH
       {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         rpm = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
         prevmillis = micros(); // store time for nect revolution calculation
       }
   }
  prevstate = currentstate; // store this scan (prev scan) data for next scan
  
  // LCD Display
  if( ( millis()-lcdrefresh ) >= 100 )
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed of Motor");
      lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(rpm);         
      lcdrefresh = millis();   
    }

}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int S = 00; // count seconds 
int M = 10; // count minutes
int H = 00; // count hours

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

signed short minutes, secondes;
char timeline[16];

void setup()
{
 lcd.begin();//set up the LCD's number of columns and rows
}
void loop()
{
 lcd.setCursor(2,0); 
 lcd.print ("STEAL AND ESCAPE");
 lcd.setCursor(6,1);
 lcd.print(":");
 lcd.setCursor(9,1);
 lcd.print(":");
 
 S--;
 delay(1000);
  
 if(S<0)
 {
   M--;
   S=59;
 }
 if(M<0)
 {
   H--;
   M=59;
 }
 if(H<0) { H=23; M=59; S=59; } if(M>9)
 {
   lcd.setCursor(7,1);
   lcd.print("GAME OVER");
   delay(500000);
 }
 else
 {
   lcd.setCursor(7,1);
   lcd.print("0"); 
   lcd.setCursor(8,1);
   lcd.print(M);
   lcd.setCursor(9,1);
   lcd.print(":");
 }
  
 if(S>9)
 {
   lcd.setCursor(10,1);
   lcd.print(S);
 }
 else
 {
   lcd.setCursor(10,1);
   lcd.print("0"); 
   lcd.setCursor(11,1);
   lcd.print(S);
   lcd.setCursor(12,1);
   lcd.print(" ");
 }
  
 if(H>9)
 {
   lcd.setCursor(4,1);
   lcd.print (H);
 }
 else
 {
   lcd.setCursor(4,1);
   lcd.print("0"); 
   lcd.setCursor(5,1);
   lcd.print(H);
   lcd.setCursor(6,1);
   lcd.print(":");
 }
}

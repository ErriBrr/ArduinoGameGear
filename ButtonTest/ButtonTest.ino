// author : ErriBrr
//simple test for buttons and potentiometer


// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

 
 int sensorReading = 0;

void setup() {


  // set up the lcd's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the lcd.
   


}

void loop() {
//    lcd_key = read_LCD_buttons();


  
 /* // read the potentiometer on A0:
  int sensorReading = analogRead(A0);
  // map the result to 200 - 1000:
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  // set the cursor to the bottom row, 5th position: */

 
 sensorReading = analogRead(0);
 lcd.print(sensorReading);
 delay(1000);
 lcd.clear();

}







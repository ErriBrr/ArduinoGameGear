// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons(){               // read the buttons
    int adc_key_in = analogRead(0);       // read the value from the sensor
 
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result
 
    if (adc_key_in > 1000) return btnNONE;
    
    if (adc_key_in < 50)   return btnRIGHT; 
    if (adc_key_in < 250)  return btnUP;
    if (adc_key_in < 450)  return btnDOWN;
    if (adc_key_in < 650)  return btnLEFT;
    if (adc_key_in < 850)  return btnSELECT; 
 
    return btnNONE;                // when all others fail, return this.
}

void explod (int x, int y) {
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.write(3);
  delay(150);
  lcd.setCursor(x - 1, y);
  lcd.write(4);
  lcd.setCursor(x + 1, y);
  lcd.write(5);
  delay(600);
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.write(6);
  delay(150);
  lcd.setCursor(x - 1, y);
  lcd.write(7);
  lcd.setCursor(x + 1, y);
  lcd.write(8);
  delay(600);
}

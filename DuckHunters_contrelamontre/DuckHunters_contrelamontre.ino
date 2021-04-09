// author :  ErriBrr


// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key     = 0;
int adc_key_in  = 0;
int mode = 0;
int i, j, k, l, xcible, ycible, xchasseur, ychasseur, xpos;
int kills=0;
 
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor
 
    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result
 
    if (adc_key_in > 1000) return btnNONE;
    
    if (adc_key_in < 50)   return btnRIGHT; 
    if (adc_key_in < 150)  return btnUP;
    if (adc_key_in < 405)  return btnDOWN;
    if (adc_key_in < 500)  return btnLEFT;
    if (adc_key_in < 850)  return btnSELECT; 
 
    return btnNONE;                // when all others fail, return this.
}

void explod() {
  lcd.clear();
  lcd.setCursor(xchasseur,ychasseur);
  lcd.write(3);
  delay(150);
  lcd.setCursor(xchasseur-1,ychasseur);
  lcd.write(4);
  lcd.setCursor(xchasseur+1,ychasseur);
  lcd.write(5);
  delay(600);
  lcd.clear();
  lcd.setCursor(xchasseur,ychasseur);
  lcd.write(6);
  delay(150);
  lcd.setCursor(xchasseur-1,ychasseur);
  lcd.write(7);
  lcd.setCursor(xchasseur+1,ychasseur);
  lcd.write(8);
  delay(600);
}

void setup() {
    // create a new character
  lcd.createChar(1, viseur);
  lcd.createChar(2, canard);
  lcd.createChar(3, exploa);
  lcd.createChar(4, explob);
  lcd.createChar(5, exploc);
  lcd.createChar(6, tas1);
  lcd.createChar(7, tas2);
  lcd.createChar(8, tas3);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  lcd_key = read_LCD_buttons();

  if (mode==0) {
    lcd.setCursor(0,0);
    lcd.print(" DUCKS  HUNTER");
    lcd.setCursor(0,1);
    lcd.print(" start : Select");
  }
 
  if (mode!=1 && lcd_key==btnSELECT) {
    kills=0;
    mode=1;
    lcd.clear();
    xcible=random(16);
    ycible=random(2);
    xchasseur=random(16);
    ychasseur=random(2);
    lcd.setCursor(0,0);
    lcd.print("shoot le canard!");
    lcd.setCursor(0,1);
    lcd.print("[select : tirer]");
    delay(1200);
    lcd_key=btnNONE;
    i=millis();
    k=millis();
  }
  
  if (mode==1) {
    lcd.clear();
    lcd.setCursor(xcible,ycible);
    lcd.write(2);
    lcd.setCursor(xchasseur,ychasseur);
    lcd.write(1);
    delay(10);
   if(lcd_key==btnRIGHT) {
      xchasseur++;
       if (xchasseur>=15) {
          xchasseur=15;
          }
      delay(80);
       }
  if(lcd_key==btnLEFT) {
      xchasseur--;
       if (xchasseur<=0) {
          xchasseur=0;
          }
      delay(80);
       }
  if(lcd_key==btnUP) {
      ychasseur--;
       if (ychasseur<=0) {
          ychasseur=0;
          }
      delay(50);
       }
       
  if(lcd_key==btnDOWN) {
      ychasseur++;
      if (ychasseur>=1) {
          ychasseur=1;
          }
      delay(50);
      }
  j=millis()-k;
  l=millis()-i;
  }
  
  if(mode==1 && xchasseur==xcible && ychasseur==ycible && lcd_key==btnSELECT) {
        lcd_key==btnNONE;
        kills++;
        xpos=0;
        explod();
        xcible=random(16);
        ycible=random(2);
        k=millis();
  }

  if (mode==1 && (j>=2500 || lcd_key==btnSELECT)){
      xcible=random(16);
      ycible=random(2);
      if(xcible==xchasseur && ycible==ychasseur) {
          xcible=random(16);
          ycible=random(2);
      }
      k=millis();
  }
       
 if(l>=30000) {  
      lcd.clear();
      lcd.setCursor(xpos,0);
      lcd.print("TIME OUT!!!!!");
          if(xpos==15) {
            xpos=-1 ;
          }
      lcd.setCursor(2,1);
      lcd.print( kills );
      lcd.print("  dead ducks");
      xpos++;
      delay(350);
      i=0;
      k=0;
      mode=2;
  }
}

// author : ErriBrr

#include "img_runner.h"
#include "init_console.h"


int lcd_key = 0;
int adc_key_in = 0;
int course1, course2;
int time, t0;
boolean GchAppuye, DrtAppuye, mode, fin;
int A, B, img1, img2;
boolean tab1 = 0;
boolean tab2 = 0;
int n = 0;


void setup() {
  lcd.createChar(1, un);
  lcd.createChar(2, deux);
  lcd.createChar(3, trois);
  lcd.createChar(4, quatre);
  lcd.createChar(5, cinq);
  lcd.createChar(6, six);
  lcd.createChar(7, sept);
  lcd.createChar(8, huit);
  lcd.begin(16, 2);
}


void loop() {

  lcd_key = read_LCD_buttons();
  lcd.clear();
  
  if(fin==0){time=millis()-t0;}
  
  if(A>=9){A=1;}
  if(B>=9){B=1;}

  if(course1>=75 && course2>=75){
    lcd.home();
    lcd.print("EGALITE");
    fin=1;
    lcd.setCursor(0,1);
    lcd.print(time);
    lcd.print("millis");
  }
  else if(course1>=75 && course2<=75){
    lcd.home();
    lcd.print("B gagne!");
    fin=1;
    lcd.setCursor(0,1);
    lcd.print(time);
    lcd.print("millis");
  }
  else if(course2>=75 && course1<=75){
    lcd.home();
    lcd.print("A gagne!");
    fin=1;
    lcd.setCursor(0,1);
    lcd.print(time);
    lcd.print("millis");
  }
  
  if (mode==0 && tab1==0 && tab2==0){
    course1=0;
    course2=0;
    fin=0;
    GchAppuye=0;
    DrtAppuye=0;
    // t0=millis();
    A=1;
    B=1;
    time=0;
    
    lcd.home();
    lcd.print(" OLYMPIC  GAMES");
    lcd.setCursor(0,1);
    lcd.print("  press  start");
    delay(700);
    
    if(lcd_key==btnSELECT){ tab1=1; lcd_key=btnNONE; }
  }
  
   if(tab1==1){   
      lcd.clear();
      lcd.home();
      lcd.print("  Select sport");  
      lcd.setCursor(0,1);
      switch (lcd_key) {
        case btnLEFT :
          n--;
          break;
        case btnRIGHT :
          n++;
          break;
        }
        if(n>=1){n=1;}
        if(n<=-1){n=-1;}
      switch (n) {
        case -1 :
          lcd.print("   < rien >");
          break;
        case 0 :
          lcd.print("   < 200m >");
          break;
        case 1 :
          lcd.print("   < rien >");
          break;
      }
      delay(600);
      if(lcd_key==btnSELECT){ tab1=0; tab2=1; n=0; lcd_key=btnNONE;}
 }
 
 if (tab2==1){
   lcd.home();
   lcd.print("nbr de joueurs ?");
         switch (lcd_key) {
        case btnLEFT :
          n--;
          break;
        case btnRIGHT :
          n++;
          break;
        }
        if(n>=1){n=1;}
        if(n<=0){n=0;}
        lcd.setCursor(0,1);
      switch (n) {
        case 0 :
          lcd.print("        < 1 >");
          break;
        case 1 :
          lcd.print("        < 2 >");
          break;
      }
    delay(600);
    if (lcd_key == btnSELECT){mode=1; tab2=0; lcd_key=btnNONE; t0=millis();}
}
  
  if (mode==1 && fin==0){
  lcd.setCursor(((course2)/5),0);
  lcd.write(A);
  
  lcd.setCursor(((course1)/5),1);
  lcd.write(B);
  

  if(lcd_key==btnRIGHT) {
      DrtAppuye=1;
       }
  if(lcd_key==btnNONE && (DrtAppuye==1)) {
      DrtAppuye=0;
      course2++ ;
      A++;
  }
  if(lcd_key==btnLEFT) {
      GchAppuye=1;
       }
  if(lcd_key==btnNONE && (GchAppuye==1)) {
      GchAppuye=0;
      course1++ ;
      B++;
  }
  }

delay(5);
if (fin==1) {delay(200);}
  
}

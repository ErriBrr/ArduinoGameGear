// author : ErriBrr

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


byte un[8] = {
  0b00100,
  0b00101,
  0b01110,
  0b10100,
  0b00100,
  0b00110,
  0b01001,
  0b10001
};

byte deux[8] = {
  0b00100,
  0b00101,
  0b01110,
  0b10100,
  0b00100,
  0b00110,
  0b01010,
  0b10010
};

byte trois[8] = {
  0b00100,
  0b00101,
  0b01110,
  0b10100,
  0b00100,
  0b01100,
  0b01100,
  0b10100
};

byte quatre[8] = {
  0b00100,
  0b00110,
  0b01110,
  0b01100,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

byte cinq[8] = {
  0b00100,
  0b00100,
  0b01110,
  0b01110,
  0b00100,
  0b00110,
  0b00110,
  0b00101
};

byte six[8] = {
  0b00100,
  0b01100,
  0b01110,
  0b00110,
  0b00100,
  0b00110,
  0b01001,
  0b10001
};

byte sept[8] = {
  0b00100,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b00110,
  0b01001,
  0b10001
};

byte huit[8] = {
  0b00100,
  0b00101,
  0b01110,
  0b10100,
  0b00100,
  0b01010,
  0b11001,
  0b00000
};

int lcd_key = 0;
int adc_key_in = 0;
int course1, course2;
int time, t0;
boolean GchAppuye, DrtAppuye, mode, fin;
int A, B, img1, img2;
boolean tab1 = 0;
boolean tab2 = 0;
int n = 0;


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
 
    // For V1.1 us this threshold
    /// j'ai totalement bidouillé sur ces chiffres de potentiometre... à corriger manuellement si nécessaire
    if (adc_key_in < 50)   return btnRIGHT; 
    if (adc_key_in < 150)  return btnUP;
    if (adc_key_in < 405)  return btnDOWN;
    if (adc_key_in < 500)  return btnLEFT;
    if (adc_key_in < 750)  return btnSELECT; 
   
   // For V1.0 comment the other threshold and use the one below:
   /*
     if (adc_key_in < 50)   return btnRIGHT; 
     if (adc_key_in < 150)  return btnUP;
     if (adc_key_in < 400)  return btnDOWN;
     if (adc_key_in < 555)  return btnLEFT;
     if (adc_key_in < 790)  return btnSELECT;  
   */
 
    return btnNONE;                // when all others fail, return this.
}



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



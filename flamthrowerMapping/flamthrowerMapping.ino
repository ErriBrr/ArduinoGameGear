//author : ErriBrr

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// make some custom characters:
byte rambo[8] = {
  0b01000,
  0b01100,
  0b01000,
  0b11100,
  0b11111,
  0b01000,
  0b11100,
  0b10010
};

byte ramboinv[8] = {
  0b00010,
  0b00110,
  0b00010,
  0b00111,
  0b11111,
  0b00010,
  0b00111,
  0b01001
};


byte zombie[8] = {
  0b01000,
  0b01001,
  0b01110,
  0b01010,
  0b01001,
  0b01000,
  0b10100,
  0b10100
};

byte zzombie[8] = {
  0b01001,
  0b01010,
  0b01110,
  0b01001,
  0b01000,
  0b01000,
  0b10100,
  0b10100
};

byte zzombieinv[8] = {
  0b10010,
  0b01010,
  0b01110,
  0b10010,
  0b00010,
  0b00010,
  0b00101,
  0b00101
};

byte zombieinv[8] = {
  0b00010,
  0b10010,
  0b01110,
  0b01010,
  0b10010,
  0b00010,
  0b00101,
  0b00101
};

byte blocfeufingch[8] = {
  0b00001,
  0b01000,
  0b00001,
  0b00111,
  0b01001,
  0b00001,
  0b00010,
  0b00000
};

byte blocfeufindrt[8] = {
  0b10000,
  0b00100,
  0b10000,
  0b11000,
  0b10010,
  0b00000,
  0b01100,
  0b00000
};

int lcd_key = 0;
int adc_key_in = 0;
int mode = 0;
int xz, yz, xz1, yz1, xz2, yz2, yz3, xz3, yz4, xz4, yz5, xz5, yz6, xz6;
int xchasseur, ychasseur;
boolean droite, z1, z2, z, z3, z4, z5, z6, z7, z8, z9, z10, z11, z12;
int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t; 
int d, d1, d2, d3, d4, d5, d6; // pour savoir si le zombie est a droite ou a gauch
int h, zone, xcase, ycase, harchive;
int timer0, timer1;
int score;

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


void feu1drt() {
  lcd.setCursor(xchasseur+1,ychasseur);
  lcd.write(8);
  lcd.write(8);
  lcd.write(8);
  lcd.write(7);
  lcd.setCursor(xchasseur+1,ychasseur-1);
  lcd.write(8);
  lcd.write(7);
  lcd.setCursor(xchasseur+1,ychasseur+1);
  lcd.write(8);
  lcd.write(7);
  }
  
void feu2drt() {
  lcd.setCursor(xchasseur+1,ychasseur);
  lcd.write(7);
  lcd.write(7);
  lcd.write(7);
  lcd.write(8);
  lcd.setCursor(xchasseur+1,ychasseur-1);
  lcd.write(7);
  lcd.write(8);
  lcd.setCursor(xchasseur+1,ychasseur+1);
  lcd.write(7);
  lcd.write(8);
  }

void feu1gch() {
  lcd.setCursor(xchasseur-1, ychasseur);
  lcd.write(8);
  lcd.setCursor(xchasseur-2,ychasseur);
  lcd.write(8);
  lcd.setCursor(xchasseur-3,ychasseur);
  lcd.write(7);
  lcd.setCursor(xchasseur-4,ychasseur);
  lcd.write(8);
  lcd.setCursor(xchasseur-1,ychasseur-1);
  lcd.write(8);
  lcd.setCursor(xchasseur-2,ychasseur-1);
  lcd.write(8);
  lcd.setCursor(xchasseur-1,ychasseur+1);
  lcd.write(8);
  lcd.setCursor(xchasseur-2,ychasseur+1);
  lcd.write(8);
  }
  
void feu2gch() {
  lcd.setCursor(xchasseur-1, ychasseur);
  lcd.write(7);
  lcd.setCursor(xchasseur-2, ychasseur);
  lcd.write(7);
  lcd.setCursor(xchasseur-3, ychasseur);
  lcd.write(8);
  lcd.setCursor(xchasseur-4, ychasseur);
  lcd.write(7);
  lcd.setCursor(xchasseur-1, ychasseur-1);
  lcd.write(7);
  lcd.setCursor(xchasseur-2, ychasseur-1);
  lcd.write(7);
  lcd.setCursor(xchasseur-1, ychasseur+1);
  lcd.write(7);
  lcd.setCursor(xchasseur-2, ychasseur+1);
  lcd.write(7);
  }
  
void ifz() {
  lcd.setCursor(xz,yz);
  if (z==0) {
    if(d==1) {lcd.write(4);}
    else  {lcd.write(3);}
    if(t>=5){
      z=1;
      t=0;   }
            }
  if (z==1) {
    if (d==1) {lcd.write(6);}
    else {lcd.write(5) ;}
    if (t>=5){
      z=0;
      t=0;    }
             }
            }
            
void vibrations(){
        for (int positionCounter = 0; positionCounter < 1; positionCounter++) {
        lcd.scrollDisplayRight(); 
        delay(200);
                    }
      for (int positionCounter = 0; positionCounter < 2; positionCounter++) {
        lcd.scrollDisplayLeft(); 
        delay(200);
                    }
      for (int positionCounter = 0; positionCounter < 2; positionCounter++) {
        lcd.scrollDisplayRight(); 
        delay(200);
                    }
      for (int positionCounter = 0; positionCounter < 1; positionCounter++) {
        lcd.scrollDisplayLeft(); 
        delay(200);
                    }
}
              
void gameover() {
    if (((xz==xchasseur) && (yz==ychasseur)) || (timer1>=122)) {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("GAME OVER");
      vibrations();
      vibrations();
      vibrations();
      delay(1000);
      mode=0;
      
                                            }
    if (t>=6){
      if(d==1){
        xz=xz-random(3);
        yz=yz+random(2);
        if (xz<=(xchasseur-3)){ d=0;}
               }
      else{
        xz=xz+random(3);
        yz=yz+random(2);
        if (xz>=(xchasseur+3)){ d=1;}
               } 
      if(yz>=2) {yz=0 ;}
      if(xz<=0) {xz=0 ;}
      if(xz>=15) {xz=15 ;}
      t=0;
              }
                 }  
     
void resetz(){
   d1=1;
   t2=0; 
   t1=15;
   
   d2=0;
   t3=15;
   t4=0;
   
   d3=0;
   t5=15;
   t6=0;
   
   d4=1;
   t7=15; 
   t8=0;
   
   d5=0;
   t9=15;
   t10=0;
   
   d6=0;
   t11=15;
   t12=0;
   
 
   z1=0;
   z2=0;
   
   z3=0;
   z4=0;

   z5=0;
   z6=0;
   
   z7=0;
   z8=0;
   
   z9=0;
   z10=0;
   
   z11=0;
   z12=0; 
            }
/*            
void brulagauch(){
  
}

void bruladroit(){
  if ((xz==(xchasseur+1) || xz==(xchasseur+2) || xz==(xchasseur+3)) && yz==ychasseur) {
          z=0;        
          t=0;   }
}*/
  
                
void setup() {
  // create a new character
  lcd.createChar(1, rambo);
  lcd.createChar(2, ramboinv);
  lcd.createChar(3, zombie);
  lcd.createChar(4, zzombieinv);
  // create a new character
  lcd.createChar(5, zzombie);
  // create a new character
  lcd.createChar(6, zombieinv);
  // create a new character
  lcd.createChar(7, blocfeufindrt);  
  // create a new character
  lcd.createChar(8, blocfeufingch);  

  // set up the lcd's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the lcd.
             }

void loop() {
 lcd_key = read_LCD_buttons();
  
// lcd.clear();
 
 timer1=((millis()/1000)-timer0);
 if(timer1>=120) {lcd.clear(); lcd.home(); lcd.print("BOOOMMM!!"); delay(1000);}
 
 if(mode==0) {
   lcd.clear();
   lcd.print("  FLAMETHROWER");
   lcd.setCursor(0,1);
   lcd.print("   VS ZOMBIES");
   xchasseur=7;
   ychasseur=1;
   droite=1;
   if(lcd_key==btnSELECT){ lcd.clear(); lcd.home(); lcd.print("RUNAWAY! ZOMBIE!!!!"); lcd.setCursor(0,1); lcd.print("2 min to escape"); delay(1200); lcd.clear(); lcd.home(); lcd.print(" Nuclear Launch"); lcd.setCursor(0,1); lcd.print("DETECTED! RUN!!!"); delay(1200); lcd.clear(); lcd.home();  lcd.print("find the way out"); lcd.setCursor(0,1); lcd.print("<-? ->? up? down");delay(1200);  delay(1500);mode=1;}
   score=0;
   resetz();
   zone=0;
   h=random(1,5);
   timer0=(millis()/1000);
             }

if(mode==1){
  lcd.clear();
if(score<=10){
   if(lcd_key==btnRIGHT){
      xchasseur=xchasseur+1;
      if (droite==0){xchasseur--;}
      droite=1;
                        }
       
  if(lcd_key==btnLEFT) {
      xchasseur=xchasseur-1;
      if (droite==1){xchasseur++;}
      droite=0;
                        }
       
  if(lcd_key==btnDOWN) {
      ychasseur=ychasseur+1;
                       }
       
  if(lcd_key==btnUP) {
      ychasseur=ychasseur-1;
                     }


switch (zone) {
case 0 :
break;
case 1 :
if(xchasseur<=13){xchasseur=13;}
if(ychasseur<=0){ychasseur=0;}
if(ychasseur>=1){ychasseur=1;}
for (ycase=0; ycase<=2; ycase++){
for (xcase=0 ; xcase<=12 ; xcase++){
lcd.setCursor(xcase, ycase);
lcd.write(8);
				   }
				 }
break;
case 2 :
if(xchasseur>=15){xchasseur=15;}
if(xchasseur<=0){xchasseur=0;}
if(ychasseur<=0){ychasseur=1;}
ycase=0;
for (xcase=0 ; xcase<=16 ; xcase++){
lcd.setCursor(xcase, ycase);
lcd.write(8);
				   }
break;
case 3 :
if(xchasseur>=2){xchasseur=2;}
if(ychasseur<=0){ychasseur=0;}
if(ychasseur>=1){ychasseur=1;}
for (ycase=0; ycase<=2; ycase++){
for (xcase=3 ; xcase<=16 ; xcase++){
lcd.setCursor(xcase, ycase);
lcd.write(8);
				   }
				 }
break;
case 4 :
if(xchasseur>=15){xchasseur=15;}
if(xchasseur<=0){xchasseur=0;}
if(ychasseur>=1){ychasseur=0;}
ycase=1;
for (xcase=0 ; xcase<=16 ; xcase++){
lcd.setCursor(xcase, ycase);
lcd.write(8);
				   }
break;
}

      if (ychasseur<=-1){
        ychasseur=1;
        resetz();
        if (h==2){ 
          if(zone==0){
            h=4;
            while (h==4){h=random(1,5);}
            ;score++;}
          else{h=harchive; zone=0 ;}
                  }
        else {
          harchive=h;
          h=4;
          zone=2;
	      }
			}

     if (ychasseur>=2){
        ychasseur=0;
        resetz();
        if (h==4){
         if(zone==0){
           h=2;
           while(h==2){h=random(1,5);}
           score++;}
         else{h=harchive; zone=0 ;}
                  } 
        else {
          harchive=h;
          h=2;
          zone=4;
	      }
		      }

      if (xchasseur<=-1){
        xchasseur=15;
        resetz();
        if (h==1){
           if(zone==0){ 
             h=3;
             while(h==3){h=random(1,5);}
             score++ ; }
           else {h=harchive; zone=0;}
                  }
        else {
          harchive=h;
          h=3;
          zone=1;
              }
  			}

      if (xchasseur>=16){
        xchasseur=0;
        resetz();
        if (h==3){ 
            if(zone==0){
              h=1;
              while(h==1){h=random(1,5);}
              score++ ; }
            else{h=harchive; zone=0;}
                  }
        else {
          harchive=h;
          h=1;
          zone=3;
	      }
		        }

 if(z1 == 1) {
   xz=xz1;
   yz=yz1;
   t=t1;
   d=d1;
   gameover();
   t1=t;
   d1=d;
   xz1=xz;
   yz1=yz;
      
   xz=xz1;
   yz=yz1;
   z=z2;
   d=d1;
   t=t2;
   ifz(); 
   z2=z;
   t2=t;   }
   
 if(z3 == 1) {
   xz=xz2;
   yz=yz2;
   t=t3;
   d=d2;
   gameover();
   t3=t;
   d2=d;
   xz2=xz;
   yz2=yz;
   
   xz=xz2;
   yz=yz2;
   z=z4;
   d=d2;
   t=t4;
   ifz(); 
   z4=z;
   t4=t;     }

 if(z5 == 1) {
   xz=xz3;
   yz=yz3;
   t=t5;
   d=d3;
   gameover();
   t5=t;
   d3=d;
   xz3=xz;
   yz3=yz;
      
   xz=xz3;
   yz=yz3;
   z=z6;
   d=d3;
   t=t6;
   ifz(); 
   z6=z;
   t6=t;   }
   
 if(z7 == 1) {
   xz=xz4;
   yz=yz4;
   t=t7;
   d=d4;
   gameover();
   t7=t;
   d4=d;
   xz4=xz;
   yz4=yz;
   
   xz=xz4;
   yz=yz4;
   z=z8;
   d=d4;
   t=t8;
   ifz(); 
   z8=z;
   t8=t;     }
   
 if(z9 == 1) {
   xz=xz5;
   yz=yz5;
   t=t9;
   d=d5;
   gameover();
   t9=t;
   d5=d;
   xz5=xz;
   yz5=yz;
      
   xz=xz5;
   yz=yz5;
   z=z10;
   d=d5;
   t=t10;
   ifz(); 
   z10=z;
   t10=t;   }
   
 if(z11 == 1) {
   xz=xz6;
   yz=yz6;
   t=t11;
   d=d6;
   gameover();
   t11=t;
   d6=d;
   xz6=xz;
   yz6=yz;
   
   xz=xz6;
   yz=yz6;
   z=z12;
   d=d6;
   t=t12;
   ifz(); 
   z12=z;
   t12=t;     }
   
lcd.setCursor(xchasseur , ychasseur);        
if(droite==0) { lcd.write(2); }
if(droite==1) { lcd.write(1); }


if(lcd_key==btnSELECT) {
    if(droite==1) {
        if(z1==1) {
              if (((xz1==(xchasseur+1) || xz1==(xchasseur+2) || xz1==(xchasseur+3) || xz1==(xchasseur+4)) && yz1==ychasseur) || ((xz1==(xchasseur+1) || xz1==(xchasseur+2)) && yz1==(ychasseur+1)) || ((xz1==(xchasseur+1) || xz1==(xchasseur+2)) && yz1==(ychasseur-1))) {
                
                z1=0;        
                t1=0;   }
                  }
        if(z3==1) {
               if (((xz2==(xchasseur+1) || xz2==(xchasseur+2) || xz2==(xchasseur+3) || xz2==(xchasseur+4)) && yz2==ychasseur) || ((xz2==(xchasseur+1) || xz2==(xchasseur+2)) && yz2==(ychasseur+1)) || ((xz2==(xchasseur+1) || xz2==(xchasseur+2)) && yz2==(ychasseur-1))) {
          z3=0;        
          t3=0;   }
                  }
        if(z5==1) {
                if (((xz3==(xchasseur+1) || xz3==(xchasseur+2) || xz3==(xchasseur+3) || xz3==(xchasseur+4)) && yz3==ychasseur) || ((xz3==(xchasseur+1) || xz3==(xchasseur+2)) && yz3==(ychasseur+1)) || ((xz3==(xchasseur+1) || xz3==(xchasseur+2)) && yz3==(ychasseur-1))) {
          z5=0;        
          t5=0;   }
                  }
        if(z7==1) {
              if (((xz4==(xchasseur+1) || xz4==(xchasseur+2) || xz4==(xchasseur+3) || xz4==(xchasseur+4)) && yz4==ychasseur) || ((xz4==(xchasseur+1) || xz4==(xchasseur+2)) && yz4==(ychasseur+1)) || ((xz4==(xchasseur+1) || xz4==(xchasseur+2)) && yz4==(ychasseur-1))) {
          z7=0;        
          t7=0;   }
                  }
        if(z9==1) {
               if (((xz5==(xchasseur+1) || xz5==(xchasseur+2) || xz5==(xchasseur+3) || xz5==(xchasseur+4)) && yz5==ychasseur) || ((xz5==(xchasseur+1) || xz5==(xchasseur+2)) && yz5==(ychasseur+1)) || ((xz5==(xchasseur+1) || xz5==(xchasseur+2)) && yz5==(ychasseur-1))) {
          z9=0;        
          t9=0;   }
                  }
        if(z11==1) {
               if (((xz6==(xchasseur+1) || xz6==(xchasseur+2) || xz6==(xchasseur+3) || xz6==(xchasseur+4)) && yz6==ychasseur) || ((xz6==(xchasseur+1) || xz6==(xchasseur+2)) && yz6==(ychasseur+1)) || ((xz6==(xchasseur+1) || xz6==(xchasseur+2)) && yz6==(ychasseur-1))) {
          z11=0;        
          t11=0;   }
                  }
      
      lcd.setCursor(xchasseur+1 , ychasseur);
      lcd.write(8);
      delay(90);
      lcd.write(8);
      delay(90);
      feu1drt();
      delay(350); 
      feu2drt();
      delay(250);
      
                  }
  else {
      if(z1==1) {
        if (((xz1==(xchasseur-1) || xz1==(xchasseur-2) || xz1==(xchasseur-3) || xz1==(xchasseur-4)) && yz1==ychasseur) || ((xz1==(xchasseur-1) || xz1==(xchasseur-2)) && yz1==(ychasseur+1)) || ((xz1==(xchasseur-1) || xz1==(xchasseur-2)) && yz1==(ychasseur-1))) {
          z1=0; 
          t1=0;                                                                                    }
                }
      if(z3==1) {
        if (((xz2==(xchasseur-1) || xz2==(xchasseur-2) || xz2==(xchasseur-3) || xz2==(xchasseur-4)) && yz2==ychasseur) || ((xz2==(xchasseur-1) || xz2==(xchasseur-2)) && yz2==(ychasseur+1)) || ((xz2==(xchasseur-1) || xz2==(xchasseur-2)) && yz2==(ychasseur-1))) {
          z3=0; 
          t3=0;                                                                                    }
                }
      if(z5==1) {
        if (((xz3==(xchasseur-1) || xz3==(xchasseur-2) || xz3==(xchasseur-3) || xz3==(xchasseur-4)) && yz3==ychasseur) || ((xz3==(xchasseur-1) || xz3==(xchasseur-2)) && yz3==(ychasseur+1)) || ((xz3==(xchasseur-1) || xz3==(xchasseur-2)) && yz3==(ychasseur-1))) {
          z5=0;        
          t5=0;   }
                  }
      if(z7==1) {
        if (((xz4==(xchasseur-1) || xz4==(xchasseur-2) || xz4==(xchasseur-3) || xz4==(xchasseur-4)) && yz4==ychasseur) || ((xz4==(xchasseur-1) || xz4==(xchasseur-2)) && yz4==(ychasseur+1)) || ((xz4==(xchasseur-1) || xz4==(xchasseur-2)) && yz4==(ychasseur-1))) {
          z7=0;        
          t7=0;   }
                  }
      if(z9==1) {
        if (((xz5==(xchasseur-1) || xz5==(xchasseur-2) || xz5==(xchasseur-3) || xz5==(xchasseur-4)) && yz5==ychasseur) || ((xz5==(xchasseur-1) || xz5==(xchasseur-2)) && yz5==(ychasseur+1)) || ((xz5==(xchasseur-1) || xz5==(xchasseur-2)) && yz5==(ychasseur-1))) {
          z9=0;        
          t9=0;   }
                  }
      if(z11==1) {
        if (((xz6==(xchasseur-1) || xz6==(xchasseur-2) || xz6==(xchasseur-3) || xz6==(xchasseur-4)) && yz6==ychasseur) || ((xz6==(xchasseur-1) || xz6==(xchasseur-2)) && yz6==(ychasseur+1)) || ((xz6==(xchasseur-1) || xz6==(xchasseur-2)) && yz6==(ychasseur-1))) {
          z11=0;        
          t11=0;   }
                  }
      lcd.setCursor(xchasseur-1 , ychasseur);
      lcd.write(7);
      delay(90);
      lcd.setCursor(xchasseur-1 , ychasseur);
      lcd.write(7);
      delay(90);
      feu1gch();
      delay(350);
      feu2gch();
      delay(250);  }
 }


 
 t1++;
 t2++;
 
 t3++;
 t4++;
 
 t5++;
 t6++;
 
 t7++;
 t8++;
 
 t9++;
 t10++;
 
 t11++;
 t12++;
 
if (t1>=20) {
 if (z1==0 ) {
   z1=1;
   xz1=15;
   yz1=0; 
   t1=0;      }
            }  
           
if (t3>=20) {
 if (z3==0 ) {
   z3=1;
   xz2=0;
   yz2=0; 
   t3=0;      }
            } 
          
if (t5>=20) {
 if (z5==0 ) {
   z5=1;
   xz3=15;
   yz3=1; 
   t5=0;      }
            } 
          
if (t7>=20) {
 if (z7==0 ) {
   z7=1;
   xz4=0;
   yz4=1; 
   t7=0;      }
            } 
          
if (t9>=20) {
 if (z9==0 ) {
   z9=1;
   xz5=15;
   yz5=0; 
   t9=0;      }
            }   

if (t11>=20) {
 if (z11==0 ) {
   z11=1;
   xz6=0;
   yz6=0; 
   t11=0;      }
            } 
}

else{
  lcd.clear();
  lcd.home();
  lcd.print("You are safe!!!!!");
  lcd.setCursor(4,1);
  lcd.print("Congrats");
  delay(150);
  mode=2;
  if(lcd_key==btnSELECT){ mode=0;}
}
}



delay(175);  // delai pour ralentir histoire d'eviter les bugs de l'horloge,  et aussi pour permettre l'incrementale a la place de t1=millis()

                         
                          
  // j'ai mis une incrémentale au lieu d'une comparaison entre millis() parce que au bout de trois-quatre réapparition du z1 y'avait un bug du genre le z1 se déplace à une vitesse folle, donc j'essaye ici d'éviter un bug du timer
lcd_key=btnNONE ; //ne marche si au debut, bloque tout
}

// author :  ErriBrr

#include "img_canard.h"
#include "img_explosion.h"
#include "img_viseur.h"
#include "init_console.h"
#include "coords.h"
#include "duck.h"
#include "scope.h"

int lcd_key = 0;

int mode = 0;
int i, j, k, l;
int kills=0;
 
int xpos_title=0;

duck *duck_target;
scope *rifle_scope;

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
  
  // home page
  if (mode==0) {
    xpos_title = 0;
    lcd.setCursor(xpos_title,0);
    lcd.print(" DUCKS  HUNTER");
    lcd.setCursor(0,1);
    lcd.print(" start : Select");
  }
  
  // game is starting
  if (mode!=1 && lcd_key==btnSELECT) {
    kills=0;
    mode=1;
    lcd.clear();
    duck_target = new coords();
    rifle_scope = new coords();
    lcd.setCursor(0,0);
    lcd.print("shoot le canard!");
    lcd.setCursor(0,1);
    lcd.print("[select : tirer]");
    delay(1200);
    lcd_key=btnNONE;
    i=millis();
    k=millis();
  }
  
  // game loop
  if (mode==1) {
    lcd.clear();
    lcd.setCursor(duck_target->get_abs(),duck_target->get_ord());
    lcd.write(2);
    lcd.setCursor(rifle_scope->get_abs(),rifle_scope->get_ord());
    lcd.write(1);
    delay(10);
    rifle_scope->move(lcd_key);
    delay(80);
    j=millis()-k;
    l=millis()-i;
  }
  
  // duck shooted
  if(mode==1 && lcd_key==btnSELECT) {
    if (duck_target->is_equal(rifle_scope)){
        lcd_key==btnNONE;
        kills++;
        explod(duck_target->get_abs(), duck_target->get_ord());
        delete duck_target;
        duck_target = new coords();
        k=millis();
        xpos_title=0;
    }
  }
  
  // the duck is moving
  if (mode==1 && (j>=2500 || lcd_key==btnSELECT)){
      delete duck_target;
      duck_target = new coords();
      if(duck_target->is_equal(rifle_scope)) {
          delete duck_target;
          duck_target = new coords();
      }
      k=millis();
      delay(100);
  }
  
  // end of game
  if(l>=30000) {
      if (mode==1){
        delete duck_target;
        delete rifle_scope;
        mode=2;
      }
      lcd.clear();
      lcd.setCursor(xpos_title,0);
      lcd.print("TIME OUT!!!!!");
          if(xpos_title==15) {
            xpos_title=-1 ;
          }
      lcd.setCursor(2,1);
      lcd.print( kills );
      lcd.print("  dead ducks");
      xpos_title++;
      delay(350);
  }
}

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "duck.h"

duck::duck () : coords()
{
  
}

duck::~duck ()
{
  
}

void duck::explod(LiquidCrystal *lcd)
{
  int x = this->get_abs();
  int y = this->get_ord();
  lcd->clear();
  lcd->setCursor(x, y);
  lcd->write(3);
  delay(150);
  lcd->setCursor(x - 1, y);
  lcd->write(4);
  lcd->setCursor(x + 1, y);
  lcd->write(5);
  delay(600);
  lcd->clear();
  lcd->setCursor(x, y);
  lcd->write(6);
  delay(150);
  lcd->setCursor(x - 1, y);
  lcd->write(7);
  lcd->setCursor(x + 1, y);
  lcd->write(8);
  delay(600);
}

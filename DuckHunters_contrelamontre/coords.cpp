#include "coords.h"
// include the library code:
#include <Arduino.h>

coords::coords()
{
  x = random(16);
  y = random(2);
}

coords::coords(int x, int y)
{
    this->x = x;
    this->y = y;
}

coords::~coords()
{
    //dtor
}

int coords::get_abs()
{
    return x;
}

int coords::get_ord()
{
    return y;
}

void coords::set_coords(int x, int y)
{
    if (x>15) {
        x=15;
    }
    if (x<0) {
        x=0;
    }
    if (y<0) {
        y=0;
    }
    if (y>1) {
        y=1;
    }
    this->x = x;
    this->y = y;
}

bool coords::is_equal(coords *other)
{ 
  if (this->x==other->get_abs() && this->y==other->get_ord()){
    return true;
  } else {
    return false;
  }
}

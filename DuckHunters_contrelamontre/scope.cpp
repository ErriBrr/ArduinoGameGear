#include "scope.h"
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

scope::scope () : coords()
{

}

scope::~scope ()
{
  
}

void scope::move (int lcd_key)
{
    if (lcd_key==btnRIGHT) {
        set_coords(get_abs() + 1, get_ord());
    } else if (lcd_key==btnLEFT) {
        set_coords(get_abs() - 1, get_ord());
    } else if (lcd_key==btnUP) {
        set_coords(get_abs(), get_ord() - 1);
    } else if (lcd_key==btnDOWN) {
        set_coords(get_abs(), get_ord() + 1);
    }
}

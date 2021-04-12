#include "coords.h"

class scope : public coords
{
  public :
    scope ();
    ~scope ();
    void move (int lcd_key);
};

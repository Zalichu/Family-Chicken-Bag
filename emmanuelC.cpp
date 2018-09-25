//Emmanuel Chavez
#include "fonts.h"

using namespace std;

void showEmmanuelName(int x, int y)
{	
    Rect r;
    unsigned int c = 0x00ffff44;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 16, c, "Emmanuel Chavez");
}

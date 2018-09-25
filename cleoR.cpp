// 
//
//  
 

#include <iostream>
#include "fonts.h"

using namespace std;

void showCleoName(int x, int y) 
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "Cleophas Reaves III");
}

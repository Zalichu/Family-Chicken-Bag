// Author: Mason Denning
// Lab 5 - 3350 - Software Engineering
// Team 1
#include <iostream>
#include "fonts.h"

void showMasonName(int x, int y)
{
    // Display name here.
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff000, "Mason Denning");
}



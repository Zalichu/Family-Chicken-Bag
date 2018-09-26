//Author: Mohammed bakraa
//Date: 25/09/2018

#include<iostream>
#include<math.h> 
#include<GL/glx.h>
#include "fonts.h"

using namespace std; 

void showMohammedName(int x, int y) { 
    Rect r; 
    r.bot = y;
    r.left = x;
    r.center = 0; 
    ggprint8b(&r, 16, 0x00ff0000, "Mohammed Bakraa"); 
} 

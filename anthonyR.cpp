#include <iostream>
#include "fonts.h"

using namespace std;

void printAnthony(int x, int y)
{
	Rect c;
	//glClearColor(0.1,0.1,0.1,1.0);

	c.bot = y;
	c.left = x;
	c.center = 0;
	ggprint8b(&c, 16, 0x00ff0000, "Anthony Rodriguez");
}


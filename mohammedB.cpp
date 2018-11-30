//Author: Mohammed bakraa
//Date: 25/09/2018

#include<iostream>
#include<GL/glx.h>
#include "fonts.h"
#include "global.h"
using namespace std; 
// Porpuse: tiles system. 

class Tile {
public:
	Tile();
	void setTile(); 
	int tx;
	int ty; 
	int ncols_to_render;
	int col; 
	Flt dd;
	Flt offx;
	Flt offy;
	Flt cdd;
	Flt flo;
	Flt dec;	
private:

};

Tile::Tile() {
	
}



void showMohammedName(int x, int y) { 
    Rect r; 
    r.bot = y;
    r.left = x;
    r.center = 0; 
    ggprint8b(&r, 16, 0x00ff0000, "Mohammed Bakraa"); 
}

void showMohammedPicture(int x, int y, GLuint texid) { 
    glColor3ub(255, 255, 255);
    int wid = 40;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();
    glPopMatrix();	
} 

// set fixed game background
void showBackground(int x, int y, GLuint texid) { 
    glColor3ub(255, 255, 255);
    int wid = 480;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();
    glPopMatrix();	
} 



//Author: Mohammed bakraa
//Date: 25/09/2018

#include<iostream>
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

void showMohammedPicture(int x, int y, GLuint texid) { 
    /*static float angle = 0.0f; 
    float fx = (float)x;
    float fy = (float)y;
    float a = sin(angle) * 10.0f;
    fx += a; 
    angle += 0.2f;*/
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

// CS3350 - Software Engineering 
// Cleophas Reaves III
// Last Modified: 11/30/ 18
//

#include <iostream>
#include "fonts.h"
#include <GL/glx.h>

using namespace std;

void showCleoName(int x, int y) 
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "Cleophas Reaves III");
}
void showCleoPicture(int x, int y, GLuint texid)
{
    /*
    static float angle = 0.0f;
    float fx = (float)x;
    float fy = (float)y;
    float a += sin(angle) * 10.f;
    fx += a;
    angle += 0.2f;
    */ 

       glColor3ub(255, 255, 255);
       int wid=40;
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


void showTitlePic(int x, int y, GLuint texid)
{
       glColor3ub(255, 255, 255);
       int wid=200;
       int hgt=160;
       glPushMatrix();
       glTranslatef(x, y, 0);
       glBindTexture(GL_TEXTURE_2D, texid);
       glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -hgt);
            glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, hgt);
            glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, hgt);
            glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -hgt);
       glEnd();
       glPopMatrix();
}

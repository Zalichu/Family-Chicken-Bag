// Author: Mason Denning
// Lab 5 - 3350 - Software Engineering
// Team 1
#include <iostream>
#include "fonts.h"
#include <GL/glx.h>


void showMasonName(int x, int y)
{
    // Display name here.
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff000, "Mason Denning");
}

void showMasonPicture(int x, int y, GLuint texid)
{
    glColor3ub(255, 255, 255);
    int wid = 40;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();
    glPopMatrix();
};

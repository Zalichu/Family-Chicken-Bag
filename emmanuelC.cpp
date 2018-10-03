//Emmanuel Chavez
#include "fonts.h"
#include <GL/glx.h>

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
void showEmmanuelPic(int x, int y, GLuint texid)
{
	glColor3ub(255,255,255);
        int wid=40;
        glPushMatrix();
        glTranslatef(x,y,0);
        glBindTexture(GL_TEXTURE_2D, texid);
        glBegin(GL_QUADS);
        	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
        	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
       		glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
        	glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
         glEnd();
         glPopMatrix();

}

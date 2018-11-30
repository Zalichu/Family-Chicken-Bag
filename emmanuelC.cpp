//Author: Emmanuel Chavez
//Fall 2018
//Purpose:
//Shows author's name and image

#include "fonts.h"
#include <GL/glx.h>
#include "emmanuelC.h"

extern Timers timers;
extern Global gl;
extern Level lev;

//prints author's name
void showEmmanuelName(int x, int y)
{	
	Rect r;
	unsigned int c = 0x00ffff44;
	r.bot = y;
	r.left = x;
	r.center = 0;
	ggprint8b(&r, 16, c, "Emmanuel Chavez");
}
//shows author's image
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
int showPunch(int frame)
{
	//man is walking...
	//when time is up, advance the frame.
	timers.recordTime(&timers.timeCurrent);
	double timeSpan = timers.timeDiff(&timers.walkTime, &timers.timeCurrent);
	if (timeSpan > gl.delay) {
		//advance
		++gl.walkFrame;
		frame++;
		if (gl.walkFrame >= 14)
			gl.walkFrame -= 14;
		timers.recordTime(&timers.walkTime);
	}
	for (int i=0; i<20; i++) {
		gl.box[i][0] -= 1.0 * (0.05 / gl.delay);
		if (gl.box[i][0] < -10.0)
			gl.box[i][0] += gl.xres + 10.0;
		gl.camera[0] += 2.0/lev.tilesize[0] * (0.05 / gl.delay);
		if (gl.camera[0] < 0.0)
			gl.camera[0] = 0.0;
	}
	if (gl.exp.onoff) {
		gl.exp.pos[0] -= 2.0 * (0.05 / gl.delay);
	}
	if (gl.exp44.onoff) {
		gl.exp44.pos[0] -= 2.0 * (0.05 / gl.delay);
	}
	return frame;
}

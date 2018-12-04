//Author: Mohammed bakraa
//Date: 25/09/2018

#include <iostream>
#include <GL/glx.h>
#include "fonts.h"
#include "emmanuelC.h"
//#include "global.h"
#include "mohammedB.h"
using namespace std; 
//Ground grnd;
// Porpuse: tiles system.
extern Global gl;

/// Start Tile class functions ////
Tile::Tile() {
	
}

void Tile::render() { 

}

void Tile::physics() {

}

Tile::~Tile() {
	
}


/// End Tile class functions ////

//// Start Ground class function ////
Ground::Ground() { 
	glGenTextures(1, &groundTexture);
	width = grndImg[1].width; 
	height = grndImg[1].height;
	glBindTexture(GL_TEXTURE_2D, groundTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grndImg[1].data); 
	glViewport(0, 0, xCord, yCord);
}

void Ground::appendGround(GLuint *texId, Image img) {
	this->groundTexture = *texId;
	glGenTextures(1, texId); 
	int width = img.width;
	int height = img.height;
	glBindTexture(GL_TEXTURE_2D, *texId); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height,
					0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
}

void Ground::drawGround() { 
	int maxW = 256;
	int maxH = 256; 
	for (int i = 0; i < 3; i ++) { 
			for (int j = 0; j < 15; j++) { 
				glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(j*maxW+maxW/2, 140+i*maxH+maxH/2, 0);
				glBindTexture(GL_TEXTURE_2D, groundTexture);
				glBegin(GL_QUADS); 
					glTexCoord2f(0.0f, 1.0f); 
					glVertex2i(-maxW/2, -maxH/2);
					glTexCoord2f(0.0f, 0.0f);
					glVertex2i(-maxW/2, maxH/2);
					glTexCoord2f(1.0f, 0.0f); 
					glVertex2i(maxW/2, maxH/2);
	                glTexCoord2f(1.0f, 1.0f); 
					glVertex2i(maxW/2, -maxH/2);
				glEnd();
				glPopMatrix();
			}

	}
}

void Ground::render() { 
		glColor3ub(255, 255, 255);
     	glPushMatrix();
     	glTranslatef(xCord, yCord, 0);
     	glBindTexture(GL_TEXTURE_2D, groundTexture);
     	glBegin(GL_QUADS);
         glTexCoord2f(0.0f, 1.0f); glVertex2i(0, yCord);
         glTexCoord2f(0.0f, 0.0f); glVertex2i(xCord, 0);
         glTexCoord2f(1.0f, 0.0f); glVertex2i(0, 0);
         glTexCoord2f(1.0f, 1.0f); glVertex2i(width, -width);
     	glEnd();
    	glPopMatrix();

}

void Ground::physics() {

}

Ground::~Ground() { 

} 


//// End Ground class function ////

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


void appendTile(GLuint *texId, Image img) { 
	glGenTextures(1, texId); 
	int width = img.width;
	int height = img.height;
	glBindTexture(GL_TEXTURE_2D, *texId); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height,
					0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
}


void appendGround(int x, int y, GLuint texid) { 
         glColor3ub(255, 255, 255);
         int wid=400;
         int hgt=300;
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

void setBackset(Image img) {
	  glGenTextures(1, &gl.backsetTexture);
      int backSetW = img.width;
      int backSetH = img.height;
      glBindTexture(GL_TEXTURE_2D, gl.backsetTexture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      glTexImage2D(GL_TEXTURE_2D,0,3,backSetW,backSetH,0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
      glViewport(0, 0, gl.xres, gl.yres);
}

void showBackSet(int x, int y, GLuint texid) { 
         glColor3ub(255, 255, 255);
         int wid=400;
         int hgt=300;
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

void setTile(Image img) {
	  glGenTextures(1, &gl.tileTexture);
      int tileW = img.width;
      int tileH = img.height;
      glBindTexture(GL_TEXTURE_2D, gl.tileTexture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      glTexImage2D(GL_TEXTURE_2D,0,3,tileW,tileH,0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
      glViewport(0, 0, gl.xres, gl.yres);
}

void appendTile(int x, int y, GLuint texid) { 
         glColor3ub(255, 255, 255);
         int wid=50;
         int hgt=80;
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

void setHealthBooster(Image img) {
	  glGenTextures(1, &gl.healthBoosterTexture);
      int boosterW = img.width;
      int boosterH = img.height;
      glBindTexture(GL_TEXTURE_2D, gl.healthBoosterTexture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      glTexImage2D(GL_TEXTURE_2D,0,3,boosterW,boosterH,0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
      glViewport(0, 0, gl.xres, gl.yres);
}

void appendHealthBooster(int x, int y, GLuint texid) { 
         glColor3ub(255, 255, 255);
         int wid=400;
         int hgt=300;
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


void setTreePos(Image img) {
	  glGenTextures(1, &gl.treeTexture);
      int treeW = img.width;
      int treeH = img.height;
      glBindTexture(GL_TEXTURE_2D, gl.treeTexture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      glTexImage2D(GL_TEXTURE_2D,0,3,treeW,treeH,0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
      glViewport(0, 0, gl.xres, gl.yres);
}

void insertTree(int x, int y, GLuint texid) { 
         glColor3ub(255, 255, 255);
         int wid=100;
         int hgt=300;
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


void setHeart(GLuint *texId, Image img) {
	glGenTextures(1, texId); 
	int width = img.width;
	int height = img.height;
	glBindTexture(GL_TEXTURE_2D, *texId); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height,
					0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
}

Heart::Heart(int x, int y, GLuint tex) {
	posx = x;
	posy = y; 
	texid = tex;
}

void Heart::physics() { 

}

void Heart::render() { 

      int wid = 25;
      glPushMatrix();
      glTranslatef(posx - gl.camera[0], posy, 0);
      glBindTexture(GL_TEXTURE_2D, texid);
      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_GREATER, 0.0f);
      glColor4ub(255,255,255,255);
      glBegin(GL_QUADS); 
          glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
          glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
          glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
          glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
      glEnd();
      glPopMatrix();
      glBindTexture(GL_TEXTURE_2D, 0);
      glDisable(GL_ALPHA_TEST);
}

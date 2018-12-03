//Author: Mohammed bakraa
//Date: 25/09/2018

#include <iostream>
#include <GL/glx.h>
#include "fonts.h"
#include "emmanuel.h"
#include "global.h"
#include "mohammedB.h"
using namespace std; 

// Porpuse: tiles system.

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
Ground::Ground(int xCord, int yCord) { 
    	this->xCord = xCord; 
	this->yCord = yCord; 
	this->img[1] = {
	    "./images/objects/background/ground.png"
	};
	glGenTextures(1, &groundTexture);
	this->width = img[1].width; 
	this->height = img[1].height;
	glBindTexture(GL_TEXTURE_2D, this->groundTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->img[1].data); 
	glViewport(0, 0, xCord, yCord); 
}

void Ground::render() { 
	glColor3ub(255, 255, 255);
     	glPushMatrix();
     	glTranslatef(xCord, yCord, 0);
     	glBindTexture(GL_TEXTURE_2D, groundTexture);
     	glBegin(GL_QUADS);
         glTexCoord2f(0.0f, 1.0f); glVertex2i(-width, -width);
         glTexCoord2f(0.0f, 0.0f); glVertex2i(-width, width);
         glTexCoord2f(1.0f, 0.0f); glVertex2i(width, width);
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

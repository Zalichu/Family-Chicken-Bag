//Author: Anthony Rodriguez

//What this file includes:
//	Credits
// 	My Name
//  Pause Menu
//  Color System
//  Many Rendered Images
//  User Interface
//	Some Misc. Functions

#include <iostream>
#include "fonts.h"
#include <GL/glx.h>
#include "anthonyR.h"
#include "global.h"
#include <string>

extern Collision A;
extern Enemy enemy1;
extern int locationX;
extern Global gl;

using namespace std;

int colorFont(string);
void showText(int x, int y, int colorText, const char* text);

/* TEXT FUNCTIONS 
--------------------------------------------------------------*/
void showAnthonyName(int x, int y)
{
	//Credits
	Rect credit;
	credit.bot = y + 50;
	credit.left = x;
	credit.center = 0;
	ggprint8b(&credit, 16, colorFont("white"), "CREDITS: ");

	//My Name
	Rect c;
	c.bot = y;
	c.left = x;
	c.center = 0;
	ggprint8b(&c, 16, colorFont("white"), "Anthony Rodriguez");
}

void showText(int x, int y, int colorText, const char* text)
{
	//TextBox Function
	Rect credit;
	credit.bot = y + 50;
	credit.left = x;
	credit.center = 0;
	ggprint8b(&credit, 16, colorText, text);
}

/*	GRAPHICS
--------------------------------------------------------------*/
void showAnthonyPicture(int x, int y, GLuint texid)
{
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

void showHealthbar(int x, int y, GLuint texid)
{
    glColor3ub(255, 255, 255);
    int wid = 80;
	int height = 80;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
    glEnd();
    glPopMatrix();
}

void arrowKeysPicture(int x, int y, GLuint texid)
{
    glColor3ub(255, 255, 255);
    int wid = 80;
	int height = 80;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
    glEnd();
    glPopMatrix();
}

void showHealth(int x, int y, int playerHealth, GLuint texid)
{
    glColor3ub(255, 255, 255);
    int wid = playerHealth;
	int height = 80;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
    glEnd();
    glPopMatrix();
}

void enemyHealth(int x, int y, int wid, int height, Enemy &enemy1)
{
	wid = enemy1.health;
	glColor3ub(229,31,31);
	glPushMatrix();
	glTranslatef(x,y,0);
	glBegin(GL_QUADS);	
        glVertex2i(-wid, -height);
    	glVertex2i(-wid, height);
    	glVertex2i(wid, height);
    	glVertex2i(wid, -height);
	glEnd();
	glPopMatrix();
}

void pauseScreen(int x, int y)
{
	Rect menu;
	//Play Game Button
	menu.bot = y;
	menu.left = x;
	menu.center = 0;
	ggprint8b(&menu, 20, colorFont("red"), "PLAY");

	//Credits Button
	menu.bot = y - 50;
	menu.left = x;
	menu.center = 0;
	ggprint8b(&menu, 20, colorFont("white"), "CREDITS");
}

void Controls_UI(int x, int y) //WIP 
{	
	int boxSize = 70;
	int borderSize = 5;

	//Red Border
 	glColor3ub(204, 0, 0);
    int wid = boxSize + borderSize;
	int height = boxSize + borderSize;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
    glEnd();
    glPopMatrix();
	//Light Grey Box 
 	glColor3ub(160, 160, 160);
    wid -= borderSize;
	height -= borderSize;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
    glEnd();
    glPopMatrix();	
	//Score Box
 	glColor3ub(96, 96, 96);
    wid = wid;
	height = 25;
    glPushMatrix();
    glTranslatef(x, y-45, 0);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
    glEnd();
    glPopMatrix();	
	showText(x-52, y-90, colorFont("green"), "SCORE: ");
	//showText(int x, int y, int colorText, const char* text)
	showText(x-52, y-8, colorFont("yellow"), "Q | Kick");
	showText(x-52, y-28, colorFont("yellow"), "R | Punch");
	showText(x-52, y-48, colorFont("yellow"), "Space | Jump");
}

void DEBUG(int x, int y) //WIP 
{	
	int boxSize = 70;
	int borderSize = 5;
	
	//Red Border
 	glColor3ub(204, 0, 0);
    int wid = boxSize + borderSize;
	int height = boxSize + borderSize;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
    glEnd();
    glPopMatrix();
	//Light Grey Box 
 	glColor3ub(160, 160, 160);
    wid -= borderSize;
	height -= borderSize;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
    	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
    	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
    	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
    glEnd();
    glPopMatrix();
	showText(x-52, y+5, colorFont("red"), "DEBUGGING");	
	showText(x-52, y, colorFont("red"), "==========");
	showText(x-52, y-65, colorFont("yellow"), "range: ");
	//showText(int x, int y, int colorText, const char* text)
	showText(x-52, y-13, colorFont("yellow"), "punching: ");
	showText(x-52, y-33, colorFont("yellow"), "damage done: ");
	showText(x-52, y-49, colorFont("yellow"), "hit detected: ");
}
/*LOGIC FUNCTIONS 
--------------------------------------------------------------*/

void checkCollision()
{
	if (A.Within_Range(locationX)) {
		std::cout << " - in range ";
		if (A.Punching(gl.punch) == true)
		{
			std::cout << " - Dmg: " << A.Damage();
			enemy1.health -= A.Damage();
			std::cout << " - ENEMY HEALTH: " << enemy1.health;
			A.restrict = false;
		}
	}
}

void createEnemyHitbox(char eLetter, Enemy &enemyA, int i, int j, 
						int tx, int ty, Flt dd, Flt offy, Flt offx,
						int col, int row) 
{
	extern Level lev;
	
	if (lev.arr[row][col] == eLetter) {
		locationX = (Flt)j*dd+offx;
		A.Within_Range(locationX);
				
		std::cout << locationX;

        glColor3f(75, 0, 130);
        glPushMatrix();
        glTranslated((Flt)j*dd+offx, (Flt)i*lev.ftsz[1]+offy, 0);
        glBegin(GL_QUADS);
        	glVertex2i( 0,  0);
         	glVertex2i( 0, ty);
            glVertex2i(tx, ty);
            glVertex2i(tx,  0);
        glEnd();
        glPopMatrix();
		if (enemyA.health < 0) 
				enemyA.health = 0;
			enemyHealth(locationX, 170, enemyA.health, 14, enemyA);
		if (enemyA.health != 0)
    		showText(locationX, 80, colorFont("red"), " Enemy Health");
	}
}

/* MISC. FUNCTIONS
--------------------------------------------------------------*/
int colorFont(string colorChoice)
{
	//Replaces the need to use hex codes
	if (colorChoice == "red") {
		return 0xff0000;
	}
	if (colorChoice == "green") {
		return 0xf000;
	}
	if (colorChoice == "yellow") {
		return 0xffff33;
	}
	if (colorChoice == "blue") {
		return 0x0000ff;
	}
	if (colorChoice == "purple") {
		return 0xFF00FF;
	}
	if (colorChoice == "orange") {
		return 0xFFBB52;
	}
	if (colorChoice == "black") {
		return 0x000000;
	}
	if (colorChoice == "white") {
		return 0xffffff;
	}
	return 0x0ff0000; //Default's to red
}

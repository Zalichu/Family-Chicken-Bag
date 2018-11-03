//Author: Anthony Rodriguez

//What this file includes:
//	Credits
// 	My Name
//  Pause Menu
//  Color System

#include <iostream>
#include "fonts.h"
#include <GL/glx.h>

using namespace std;

int colorFont(string);

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
	Rect credit;
	credit.bot = y + 50;
	credit.left = x;
	credit.center = 0;
	ggprint8b(&credit, 16, colorText, text);
}

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

void titleScreen(int x, int y)
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

//Replaces the need to use hex codes
int colorFont(string colorChoice)
{
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

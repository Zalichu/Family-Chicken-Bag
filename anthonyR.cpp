//Author: Anthony Rodriguez

//What this file includes:
//  Color System
//  Collision Logic 
//  Many Rendered Images/Functions 
//  Functionality Improvements
//  User Interface
//	Some Misc. Functions

#include <iostream>
#include "fonts.h"
#include <GL/glx.h>
#include "anthonyR.h"
#include <string>

using namespace std;

extern Image *img;
extern unsigned char *buildAlphaData(Image *img);
extern Collision A;
extern Peter peter;
extern int enemy1xPos;
extern Enemy enemy1;
extern int locationX;
extern Global gl;
extern float gcy;

static int playerScore = 0;
int currentLevel = 1;
extern int theCurrentLevel;
extern int numOfLevels;
int enemy1Count = 0; //To keep count of how many points to give
extern Spike spike1;
Level2 lev2;

int colorFont(string);
void showText(int x, int y, int colorText, string text);

/* TEXT FUNCTIONS 
   -----------------------------------------------------------*/
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

void showText(int x, int y, int colorText, string text)
{
	//TextBox Function
	const char *tex = text.c_str(); //Converting string to const char*
	Rect credit;
	credit.bot = y + 50;
	credit.left = x;
	credit.center = 0;
	ggprint8b(&credit, 16, colorText, tex);
}

/*	GRAPHICS
	--------------------------------------------------------------*/
//Note: These are the new and improved graphics functions
void intializeTexture(int index, GLuint texid) //Every Image needs
{
	glGenTextures(1, &texid);
	int frameW = img[index].width; 
	int frameH = img[index].height; 
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, frameW, frameH, 0, GL_RGB,
			GL_UNSIGNED_BYTE, img[index].data);
	glViewport(0, 0, gl.xres, gl.yres);	
}

void makeTransparent(GLuint *tex, Image *img)
{
	glGenTextures(1, tex);
	int w = img->width;
	int h = img->height;
	glBindTexture(GL_TEXTURE_2D, *tex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
	unsigned char *xData = buildAlphaData(img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, xData);
	free(xData);
}

void showImage(int x, int y, int width, int height, GLuint texid)
{
	glPushMatrix();
	glColor3ub(255,255,255);
	glTranslatef(x, y, 0); 
	glBindTexture(GL_TEXTURE_2D, texid);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-width/2, -height/2);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(width/2, -height/2);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(width/2, height/2);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-width/2, height/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0); 
	glPopMatrix();
}

void showStar(int x, int y, int wid, int height, GLuint texid)
{
	static float angle = 0.0f;
	static float angle2 = 0.0f;
	static float fx = 0.0f;
	angle += 0.1;
	fx = sin(angle);
	//fx += sin(angle) * 10.0f;
	angle += 0.2f;	
	glColor3ub(255, 255, 255);
	glPushMatrix();
	glTranslatef(x + (int)(fx*20.0), y, 0);
	glRotatef(angle2, 0.0f, 0.0f, 1.0f);
	angle2 += 50;
	glBindTexture(GL_TEXTURE_2D, texid);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid/2, -height/2);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid/2, -height/2);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid/2, height/2);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid/2, height/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glPopMatrix();	
}

//Note: Graphic functions down here are before I knew how header files
// worked. It's very inefficient.
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

//Old Health - Not currently in use
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
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -height);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, height);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, height);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -height);
	glEnd();
	glPopMatrix();
}

void peterHealth(int x, int y, int height, Peter &peter)
{
	int wid = peter.health;
	glColor3ub(73, 230, 99);
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
	showImage(x+30,y,50,50,gl.keysTexture);
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
	string SplayerScore = to_string(playerScore);
	currentLevel = 1 + theCurrentLevel;
	string ScurrentLevel = to_string(currentLevel);
	showText(x-52, y-90, colorFont("green"), ("SCORE: " + SplayerScore));
	showText(x-52, y-110, colorFont("green"), ("Level: " + ScurrentLevel));
	//showText(int x, int y, int colorText, const char* text)
	showText(x-52, y-8, colorFont("yellow"), "+ | Speed Up");
	showText(x-52, y-28, colorFont("yellow"), "- | Slow Down");
	showText(x-52, y-48, colorFont("yellow"), "R | Punch");
}

Level2::Level2() {
	tilesize[0] = 32;
	tilesize[1] = 32;
	ftsz[0] = (Flt)tilesize[0];
	ftsz[1] = (Flt)tilesize[1];
	tile_base = 220.0;
	//read level
	FILE *fpi = fopen("level2.txt","r");
	if (fpi) {
		nrows=0;
		char line[100];
		while (fgets(line, 100, fpi) != NULL) {
			removeCrLf(line);
			int slen = strlen(line);
			ncols = slen;
			//Log("line: %s\n", line);
			for (int j=0; j<slen; j++) {
				arr[nrows][j] = line[j];
			}
			++nrows;
		}
		fclose(fpi);
		//printf("nrows of background data: %i\n", nrows);
	}
	for (int i=0; i<nrows; i++) {
		for (int j=0; j<ncols; j++) {
			printf("%c", arr[i][j]);
		}
		printf("\n");
	}
}

void Level2::removeCrLf(char *str) {
	//remove carriage return and linefeed from a Cstring
	char *p = str;
	while (*p) {
		if (*p == 10 || *p == 13) {
			*p = '\0';
			break;
		}
		++p;
	}
}

/*COLLISION FUNCTIONS  
  --------------------------------------------------------------*/
bool Collision::Within_Range(int range) 
{
	if (range > 400 && range < 600) {
		this->range = range;
		if (gl.last_position == 'l') 
			return false;
		if (gl.last_position == 'r')
			return true;
	}
	if (range > 220 && range < 400) {
		this->range = range;
		if (gl.last_position == 'r')
			return false;
		if (gl.last_position == 'l')
			return true;
	}
	return false;
}

bool Collision::Punching(bool flag) 
{
	punching = flag;
	return flag;
}

int Collision::Damage() 
{
	if (restrict == true)	
		return 20;
	if (punching == true)
		return 0;
	return 20;		
}

void Collision::Check_For_Hit() 
{
	if (punching) {
		contact = true;
		//Damage();
	}		
}

void Spike::Within_Range(int x, Peter &peter) 
{
	if (x > xHitBoxLEFT+20 && x < xHitBoxRIGHT-20) {
		if (gcy<418) {
			peter.health = 0;
			//std::cout << " - Peter be dead \n";
		}
	}
}

bool Peter::Alive() 
{
	if (health <= 0) {
		return false;
	}
	return true;
}

void Peter::getPeterPos()
{
	extern float gcy;
	extern float gcx;
	peter.x = gcx;
	peter.y = gcy;
}

void enemyHealth_and_star()
{
	//Show Enemies 
	if (enemy1.showImage == true) {
		showImage(enemy1.x, enemy1.y, 200, 200, gl.deathTexture);
		showStar((enemy1.x - enemy1xPos++), enemy1.y-50, 100, 100, gl.ninjaStarTexture);
		//std::cout << "enemy1.y: " << enemy1.y << endl;	
		if ((enemy1.x-enemy1xPos) > peter.xHitBoxLEFT && (enemy1.x-enemy1xPos) < peter.xHitBoxRIGHT) {
			if (gcy<345)
				peter.health -= 20;
			if (!peter.Alive()) {
				//std::cout << "he ded";
			}
		}
		if (enemy1.x-enemy1xPos++ < 100) {
			enemy1xPos=0;	
			showStar((enemy1.x - enemy1xPos++), enemy1.y-50, 100, 100, gl.ninjaStarTexture);	
		}
	}
}
//void NinjaStar::Hit() 
//{
//}

void checkCollision()
{
	if (A.Within_Range(locationX)) {
		//std::cout << " - in range ";
		if (A.Punching(gl.punch) == true) {
			//std::cout << " - Dmg: " << A.Damage();
			enemy1.health -= A.Damage();
			//std::cout << " - ENEMY HEALTH: " << enemy1.health;
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
		int elocationY = (Flt)i*lev.ftsz[1]+offy;
		A.Within_Range(locationX);

		enemyA.x = locationX;
		enemyA.y = elocationY + 80;
		//std::cout << locationX;

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
		//showImage(locationX, elocationY+70, 200, 200, gl.deathTexture);
		if (enemyA.health < 0) {
			enemyA.health = 0;
		}
		enemyHealth(locationX, 170, enemyA.health, 14, enemyA);
		if (enemyA.health != 0)
			showText(locationX, 80, colorFont("red"), " Enemy Health");
		if (enemyA.health <= 0) {
			if (++enemy1Count <= 1)
				playerScore++;
			enemyA.showImage = false; 
		}
	}
}

void Peter::Jump(float &gcy) 
{
	//std::cout << "Peter Y: " << gcy << std::endl;
	if (gcy > 500) {
		//std::cout << "False\n";
		gl.jumping = false;
	}
	if (!gl.jumping) {
		//std::cout << "Falling\n";
		if (gcy>=300)
			gcy-=8;
	}
	if (gl.jumping) {
		//std::cout << "True\n";
		gcy+=8;
	}
}

void createSpike(char eLetter, Spike &spikeA, int i, int j, 
		Flt dd, Flt offy, Flt offx,
		int col, int row) 
{
	extern Level lev;
	if (lev.arr[row][col] == eLetter) {
		int SlocationX = (Flt)j*dd+offx;
		int SlocationY = (Flt)i*lev.ftsz[1]+offy;
		//std::cout << "SpikeX: " << SlocationX << " - ";
		//std::cout << "SpikeY: " << SlocationY;
		spikeA.Within_Range(SlocationX, peter);
		showImage(SlocationX, SlocationY, 150, 150, gl.spikeTexture);
	}
}

/*void createDeath(char eLetter, Death &deathA, int i, int j, 
  int tx, int ty, Flt dd, Flt offy, Flt offx,
  int col, int row) 
  {
  extern Level lev;
  if (lev.arr[row][col] == eLetter) {
  int DlocationX = (Flt)j*dd+offx;
  int DlocationY = (Flt)i*lev.ftsz[1]+offy;
  std::cout << "DeathX: " << DlocationX << " - ";
  std::cout << "DeathY: " << DlocationY;

//spikeA.Within_Range(DlocationX, DlocationY, peter);
makeTransparent(&gl.deathTexture, &img[13]);
showImage(DlocationX, DlocationY, 150, 150, gl.deathTexture);
}
}*/

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

//Ignore this::For ease of access
void renderLevel2() {
	if (theCurrentLevel==1) {
		//========================
		//Render the tile system
		//========================
		int tx = lev2.tilesize[0];
		int ty = lev2.tilesize[1];
		Flt dd = lev2.ftsz[0];
		Flt offy = lev2.tile_base;
		int ncols_to_render = gl.xres / lev2.tilesize[0] + 2;
		int col = (int)(gl.camera[0] / dd);
		col = col % lev2.ncols;
		//Partial tile offset must be determined here.
		//The leftmost tile might be partially off-screen.
		//cdd: camera position in terms of tiles.
		Flt cdd = gl.camera[0] / dd;
		//flo: just the integer portion
		Flt flo = floor(cdd);
		//dec: just the decimal portion
		Flt dec = (cdd - flo);
		//offx: the offset to the left of the screen to start drawing tiles
		Flt offx = -dec * dd;
		//Log("gl.camera[0]: %lf   offx: %lf\n",gl.camera[0],offx);
		for (int j=0; j<ncols_to_render; j++) {
			int row = lev2.nrows-1;
			for (int i=0; i<lev2.nrows; i++) {
				if (lev2.arr[row][col] == 'w') {
					glColor3f(0.8, 0.8, 0.6);
					glPushMatrix();
					//put tile in its place
					glTranslated((Flt)j*dd+offx, (Flt)i*lev2.ftsz[1]+offy, 0);
					glBegin(GL_QUADS);
					glVertex2i( 0,  0);
					glVertex2i( 0, ty);	
					glVertex2i(tx, ty);
					glVertex2i(tx,  0);
					glEnd();
					glPopMatrix();
					//cout << "\nbrown tile pos-> x: " << j*dd+offx << " y: " << i*lev.ftsz[1]+offy << endl;
				}
				if (lev2.arr[row][col] == 'b') {
					glColor3f(0.9, 0.2, 0.2);
					glPushMatrix();
					glTranslated((Flt)j*dd+offx, (Flt)i*lev2.ftsz[1]+offy, 0);
					glBegin(GL_QUADS);
					glVertex2i( 0,  0);
					glVertex2i( 0, ty);
					glVertex2i(tx, ty);
					glVertex2i(tx,  0);
					glEnd();
					glPopMatrix();
					//cout << "\nred tile pos-> x: " << j*dd+offx << " y: " << i*lev.ftsz[1]+offy << endl;
				}
				if (lev2.arr[row][col] == 'r') {	
					glColor3f(75, 0, 130);
					glPushMatrix();
					glTranslated((Flt)j*dd+offx, (Flt)i*lev2.ftsz[1]+offy, 0);
					glBegin(GL_QUADS);
					glVertex2i( 0,  0);
					glVertex2i( 0, ty);
					glVertex2i(tx, ty);
					glVertex2i(tx,  0);
					glEnd();
					glPopMatrix();
				}
				if (lev2.arr[row][col] == 'g') {	
					glColor3f(0.2, 0.2, 0.2);
					glPushMatrix();
					glTranslated((Flt)j*dd+offx, (Flt)i*lev2.ftsz[1]+offy, 0);
					glBegin(GL_QUADS);
					glVertex2i( 0,  0);
					glVertex2i( 0, ty);
					glVertex2i(tx, ty);
					glVertex2i(tx,  0);
					glEnd();
					glPopMatrix();
				}
				if (lev2.arr[row][col] == 'o') {	
					glColor3f(255, 255, 255);
					glPushMatrix();
					glTranslated((Flt)j*dd+offx, (Flt)i*lev2.ftsz[1]+offy, 0);
					glBegin(GL_QUADS);
					glVertex2i( 0,  0);
					glVertex2i( 0, ty);
					glVertex2i(tx, ty);
					glVertex2i(tx,  0);
					glEnd();
					glPopMatrix();
				}
				if (lev2.arr[row][col] == 'l') {	
					glColor3f(0, 0, 0);
					int localX = (Flt)j*dd+offx;
					if (localX > 410 && localX < 430) {
						if (theCurrentLevel+1 == numOfLevels) {
							while(1) {
								//void showEndPic(int x, int y, GLuint texid);
								//showEndPic(800,600,gl.endTexture);
								std::cout << "VICTORY\n";
							}
						}
						theCurrentLevel++;
						break;
					}
					glPushMatrix();
					glTranslated((Flt)j*dd+offx, (Flt)i*lev2.ftsz[1]+offy, 0);
					glBegin(GL_QUADS);
					glVertex2i( 0,  0);
					glVertex2i( 0, ty);
					glVertex2i(tx, ty);
					glVertex2i(tx,  0);
					glEnd();
					glPopMatrix();
				}
				createSpike('s', spike1, i, j, dd, offy, offx, col, row);
				createEnemyHitbox('c', enemy1, i, j, tx, ty, dd, offy, offx, col, row);
				--row;
			}
			col = (col+1) % lev2.ncols;
		} 
	}
}

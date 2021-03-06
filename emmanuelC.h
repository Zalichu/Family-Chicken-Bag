// global.h
#ifndef emmanuelC_H
#define emmanuelC_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include <string>
#include <iostream>

//defined types
typedef double Flt;
typedef double Vec[3];
typedef Flt	Matrix[4][4];

//-----------------------------------------------------------------------------
//Setup timers
class Timers {
public:
	double physicsRate;
	double oobillion;
	struct timespec timeStart, timeEnd, timeCurrent;
	struct timespec walkTime;
	
    Timers();
	double timeDiff(struct timespec *start, struct timespec *end);
	void timeCopy(struct timespec *dest, struct timespec *source);
	void recordTime(struct timespec *t);
};
//-----------------------------------------------------------------------------


// Past image class here. if it did not work.

class Image;


class Sprite {
public:
	int onoff;
	int frame;
	double delay;
	Vec pos;
	Image *image;
	GLuint tex;
	struct timespec time;
	Sprite();
};


class Global {
public:
	//PLAYER 
	int playerHealth;
	//
	unsigned char keys[65536];
	int xres, yres;
	int movie, movieStep;
	int walk;
    int punch;
    int cActive;
	int walkFrame;
	double delay;
	bool showDeath; //added
	bool credits; //Added
	bool menu; // Added
	bool End; //Added
	bool Title; //added
	bool jumping; //added
	bool background; // fixed background
	char last_position;
	Image *walkImage;
	GLuint walkTexture;
	GLuint chickenTexture;
	int chickenFrame;
	Vec box[20];
	Sprite exp;
	Sprite exp44;
	Vec ball_pos;
	Vec ball_vel;
	//camera is centered at (0,0) lower-left of screen. 
	Flt camera[2];
	GLuint tigerTexture;
	GLuint dogTexture;
	GLuint subaruTexture;
	GLuint kfcTexture;
	GLuint anthonyTexture;
	GLuint backgroundTexture;
	GLuint healthbarTexture;	
	GLuint healthTexture;
	GLuint keysTexture;
	GLuint titleTexture;
	GLuint endTexture;
	GLuint spikeTexture;
	GLuint deathTexture;
	GLuint ninjaStarTexture;
	GLuint health2Texture;
	GLuint groundTexture;
	GLuint backsetTexture;
	GLuint tileTexture;
	GLuint healthBoosterTexture;
	GLuint treeTexture;
	~Global();
	Global();
};

class Level {
public:
	unsigned char arr[16][80];
	int nrows, ncols;
	int tilesize[2];
	Flt ftsz[2];
	Flt tile_base;
	//vector<Heart> heart;
    Level();
	void removeCrLf(char *str);
};

class Level2 {
public:
	unsigned char arr[16][80];
	int nrows, ncols;
	int tilesize[2];
	Flt ftsz[2];
	Flt tile_base;

    	Level2();
	void removeCrLf(char *str);
};

//X Windows variables
class X11_wrapper {
private:
	Display *dpy;
	Window win;
public:
	~X11_wrapper();
	void setTitle();
	void setupScreenRes(const int w, const int h);
	X11_wrapper();
	void reshapeWindow(int width, int height);
	void checkResize(XEvent *e);
	bool getXPending();
	XEvent getXNextEvent();
	void swapBuffers();
};

class Image {
public:
	int width, height;
	unsigned char *data;
	
    ~Image();
	Image(const char *fname);
};
#endif

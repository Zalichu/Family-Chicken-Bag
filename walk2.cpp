/*	Modified by: Family-Chicken-Bag Team : Anthony | Emmanuel | Cleo | Mohammed 
    Original Author: Gordon Griesel
    This program includes:
    multiple sprite-sheet animations
    a level tiling system
    parallax scrolling of backgrounds
    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
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
#include "anthonyR.h"
#include "emmanuelC.h"
#include "mohammedB.h"
extern Timers timers;
extern Global gl;
extern Level lev;
extern X11_wrapper x11;

Image img[21] = {
    "./images/walk.gif",
    "./images/exp.png",
    "./images/exp44.png",
    "./images/tiger.jpg",
    "./images/subaru.jpg",
    "./images/dog.jpg",
    "./images/KFC.png",
    "./images/anthony.jpg",
    "./images/objects/HealthBarUI.png",
    "./images/objects/health.png",
    "./images/objects/arrowKeys.png",
    "./images/FCBTitle.png",
    "./images/FCBEnd.png",	    
    "./images/spike.png",
    "./images/death.gif",
    "./images/ninjaStar.png",
    "./images/health2.png",
    "./images/background/ground.png",
    "./images/objects/tile.png",
    "./images/objects/heart.png",
    "./images/background/tree.png"
};

Image backgroundImg[3] = {
    "./images/background/clam-parking.jpg",
    "./images/background/background.png",
    "./images/background/clam-noparking.gif"
};

typedef double Flt;
typedef double Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define MakeVector(v, x, y, z) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
                             (c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]
const float timeslice = 1.0f;
const float gravity = -0.2f;
int countp = 0;
#define ALPHA 1

void initOpengl();
void checkMouse(XEvent *e);
int checkKeys(XEvent *e);
void init();
void physics();
void render();

// TESTING
int locationX;
Collision A;
Enemy enemy1;
Peter peter;
Spike spike1;
void createEnemyHitbox(char eLetter, Enemy &enemyA, int i, int j, 
        int tx, int ty, Flt dd, Flt offy, Flt offx,
        int col, int row);
void createSpike(char eLetter, Spike &spikeA, int i, int j, 
        Flt dd, Flt offy, Flt offx,
        int col, int row);
extern void makeTransparent(GLuint *tex, Image *img);
extern void showImage(int,int,int,int,GLuint);	
extern void showStar(int,int,int,int,GLuint);
extern void renderLevel2();	
float gcy = 300;
float gcx;
int enemy1xPos = enemy1.x;
int theCurrentLevel = 0;
int numOfLevels = 2;

int main(void)
{
    srand (time(NULL));
    initOpengl();
    init();
    int done = 0;
    while (!done) {
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            x11.checkResize(&e);
            checkMouse(&e);
            done = checkKeys(&e);
        }
        physics();
        render();
        x11.swapBuffers();
    }
    cleanup_fonts();
    return 0;
}

unsigned char *buildAlphaData(Image *img)
{
    //add 4th component to RGB stream...
    int i;
    unsigned char *newdata, *ptr;
    unsigned char *data = (unsigned char *)img->data;
    newdata = (unsigned char *)malloc(img->width * img->height * 4); 
    ptr = newdata;
    unsigned char a,b,c;
    //use the first pixel in the image as the transparent color.
    unsigned char t0 = *(data+0);
    unsigned char t1 = *(data+1);
    unsigned char t2 = *(data+2);
    //cout << "buildAlphaData() clear color is:  (" << (int)t0 << ", " << (int)t1 << ", " << (int)t2 << ")" << endl;
    for (i=0; i<img->width * img->height * 3; i+=3) {
        a = *(data+0);
        b = *(data+1);
        c = *(data+2);
        *(ptr+0) = a;
        *(ptr+1) = b;
        *(ptr+2) = c;
        *(ptr+3) = 1;
        if (a==t0 && b==t1 && c==t2)
            *(ptr+3) = 0;
        //-----------------------------------------------
        ptr += 4;
        data += 3;
    }   
    return newdata;
}

void initOpengl(void)
{
    //TIGER 
    glGenTextures(1, &gl.tigerTexture);
    int tigerW = img[3].width; 
    int tigerH = img[3].height; 
    glBindTexture(GL_TEXTURE_2D, gl.tigerTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,tigerW,tigerH,0, GL_RGB, GL_UNSIGNED_BYTE, img[3].data);
    glViewport(0, 0, gl.xres, gl.yres);

    //Background  
    glGenTextures(1, &gl.backgroundTexture);
    int randBack = 1;	//Current Background Image
    int backgroundW = backgroundImg[randBack].width; 
    int backgroundH = backgroundImg[randBack].height; 
    glBindTexture(GL_TEXTURE_2D, gl.backgroundTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,backgroundW,backgroundH,0, GL_RGB, GL_UNSIGNED_BYTE, backgroundImg[randBack].data);
    glViewport(0, 0, gl.xres, gl.yres);

    //SUBARU
    glGenTextures(1, &gl.subaruTexture);
    int subaruW = img[4].width; 
    int subaruH = img[4].height; 
    glBindTexture(GL_TEXTURE_2D, gl.subaruTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, subaruW, subaruH, 0, GL_RGB,
            GL_UNSIGNED_BYTE, img[4].data);
    glViewport(0, 0, gl.xres, gl.yres);	

    //DOG
    glGenTextures(1, &gl.dogTexture);
    int dogW = img[5].width; 
    int dogH = img[5].height; 
    glBindTexture(GL_TEXTURE_2D, gl.dogTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, dogW, dogH, 0, GL_RGB,
            GL_UNSIGNED_BYTE, img[5].data);
    glViewport(0, 0, gl.xres, gl.yres);	

    //KFC
    glGenTextures(1, &gl.kfcTexture);
    int kfcW = img[6].width; 
    int kfcH = img[6].height; 
    glBindTexture(GL_TEXTURE_2D, gl.kfcTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kfcW, kfcH, 0, GL_RGB,
            GL_UNSIGNED_BYTE, img[6].data);
    glViewport(0, 0, gl.xres, gl.yres);	

    //Anthony Credits Image
    glGenTextures(1, &gl.anthonyTexture);
    int anthonyW = img[7].width; 
    int anthonyH = img[7].height; 
    glBindTexture(GL_TEXTURE_2D, gl.anthonyTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,anthonyW,anthonyH,0, GL_RGB, GL_UNSIGNED_BYTE, img[7].data);
    glViewport(0, 0, gl.xres, gl.yres);

    //Health
    glGenTextures(1, &gl.healthTexture);
    int healthW = img[9].width; 
    int healthH = img[9].height; 
    glBindTexture(GL_TEXTURE_2D, gl.healthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,healthW,healthH,0, GL_RGB, GL_UNSIGNED_BYTE, img[9].data);
    glViewport(0, 0, gl.xres, gl.yres);

    //Health Bar UI 
    glGenTextures(1, &gl.healthbarTexture);
    int healthbarW = img[8].width; 
    int healthbarH = img[8].height; 
    glBindTexture(GL_TEXTURE_2D, gl.healthbarTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,healthbarW,healthbarH,0, GL_RGB, GL_UNSIGNED_BYTE, img[8].data);
    glViewport(0, 0, gl.xres, gl.yres);

    //Arrow Keys
    glGenTextures(1, &gl.keysTexture);
    int keyimageW = img[10].width; 
    int keyimageH = img[10].height; 
    glBindTexture(GL_TEXTURE_2D, gl.keysTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,keyimageW,keyimageH,0, GL_RGB, GL_UNSIGNED_BYTE, img[10].data);
    glViewport(0, 0, gl.xres, gl.yres);
    makeTransparent(&gl.keysTexture, &img[10]);

    //Title Screen
    glGenTextures(1, &gl.titleTexture);
    int TimageW = img[11].width; 
    int TimageH = img[11].height; 
    glBindTexture(GL_TEXTURE_2D, gl.titleTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,TimageW,TimageH,0, GL_RGB, GL_UNSIGNED_BYTE, img[11].data);
    glViewport(0, 0, gl.xres, gl.yres);

    //End Screen
    glGenTextures(1, &gl.endTexture);
    int EimageW = img[12].width; 
    int EimageH = img[12].height; 
    glBindTexture(GL_TEXTURE_2D, gl.endTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,EimageW,EimageH,0, GL_RGB, GL_UNSIGNED_BYTE, img[12].data);
    glViewport(0, 0, gl.xres, gl.yres);

    //Initialize matrices
    //Spike 	
    glGenTextures(1, &gl.spikeTexture);
    int SimageW = img[13].width; 
    int SimageH = img[13].height; 
    glBindTexture(GL_TEXTURE_2D, gl.spikeTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,SimageW,SimageH,0, GL_RGB, GL_UNSIGNED_BYTE, img[13].data);
    glViewport(0, 0, gl.xres, gl.yres);
    makeTransparent(&gl.spikeTexture, &img[13]);


    //Ninja Star 	
    glGenTextures(1, &gl.ninjaStarTexture);
    int NimageW = img[15].width; 
    int NimageH = img[15].height; 
    glBindTexture(GL_TEXTURE_2D, gl.ninjaStarTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,NimageW,NimageH,0, GL_RGB, GL_UNSIGNED_BYTE, img[15].data);
    glViewport(0, 0, gl.xres, gl.yres);
    makeTransparent(&gl.ninjaStarTexture, &img[15]);

    //Death Character 	
    glGenTextures(1, &gl.deathTexture);
    int DimageW = img[14].width; 
    int DimageH = img[14].height; 
    glBindTexture(GL_TEXTURE_2D, gl.deathTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,DimageW,DimageH,0, GL_RGB, GL_UNSIGNED_BYTE, img[14].data);
    glViewport(0, 0, gl.xres, gl.yres);
    makeTransparent(&gl.deathTexture, &img[14]);

    //Health v.2	
    glGenTextures(1, &gl.health2Texture);
    int H2imageW = img[16].width; 
    int H2imageH = img[16].height; 
    glBindTexture(GL_TEXTURE_2D, gl.health2Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,H2imageW,H2imageH,0, GL_RGB, GL_UNSIGNED_BYTE, img[16].data);
    glViewport(0, 0, gl.xres, gl.yres);



    //ground tile
    glGenTextures(1, &gl.groundTexture);
    int groundW = img[17].width; 
    int groundH = img[17].height; 
    glBindTexture(GL_TEXTURE_2D, gl.groundTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,groundW,groundH,0, GL_RGB, GL_UNSIGNED_BYTE, img[17].data);
    glViewport(0, 0, gl.xres, gl.yres);


    // backset
    extern void setBackset(Image);
    setBackset(backgroundImg[2]);

    // tile set
    extern void setTile(Image); 
    setTile(img[18]);

    // setHealthBooster 
    extern void setHealthBooster(Image img); 
    setHealthBooster(img[19]);

    // set tree position
    extern void setTreePos(Image);
    setTreePos(img[20]);

    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();

    //This sets 2D mode (no perspective)
    glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);

    //Clear the screen
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //Do this to allow fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();

    //load the images file into a ppm structure.
    int w = img[0].width;
    int h = img[0].height;

    //create opengl texture elements
    glGenTextures(1, &gl.walkTexture);

    //-------------------------------------------------------------------------
    //	TRANSPARENCY SECTION
    //-------------------------------------------------------------------------
    //this is similar to a sprite graphic
    glBindTexture(GL_TEXTURE_2D, gl.walkTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    //must build a new set of data...
    unsigned char *walkData = buildAlphaData(&img[0]);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, walkData);
    free(walkData);		

    //create opengl texture elements
    glGenTextures(1, &gl.chickenTexture);

    //-------------------------------------------------------------------------
    //	TRANSPARENCY SECTION
    //-------------------------------------------------------------------------
    //this is similar to a sprite graphic
    glBindTexture(GL_TEXTURE_2D, gl.chickenTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    //must build a new set of data...
    unsigned char *chickenData = buildAlphaData(&img[0]);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, chickenData);
    free(chickenData);		
    //
    //HEALTH <3
    //-------------------------------------------------------------------------
    //create opengl texture elements
    w = img[9].width;
    h = img[9].height;
    glGenTextures(1, &gl.exp.tex);

    glBindTexture(GL_TEXTURE_2D, gl.healthTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *healtherData = buildAlphaData(&img[9]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, healtherData);
    free(healtherData);
    //
    //HEALTH BAR
    //-------------------------------------------------------------------------
    //create opengl texture elements
    w = img[8].width;
    h = img[8].height;
    //glGenTextures(1, &gl.exp.tex);

    glBindTexture(GL_TEXTURE_2D, gl.healthbarTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *healthData = buildAlphaData(&img[8]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, healthData);
    free(healthData);
    //
    // ARROW KEYS <3
    //-------------------------------------------------------------------------
    //create opengl texture elements
    w = img[10].width;
    h = img[10].height;
    glGenTextures(1, &gl.keysTexture);

    glBindTexture(GL_TEXTURE_2D, gl.keysTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *theKeyData = buildAlphaData(&img[10]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, theKeyData);
    free(theKeyData);
    //
    //-------------------------------------------------------------------------
    //create opengl texture elements
    w = img[1].width;
    h = img[1].height;
    glGenTextures(1, &gl.exp.tex);
    //-------------------------------------------------------------------------
    //this is similar to a sprite graphic
    glBindTexture(GL_TEXTURE_2D, gl.exp.tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //must build a new set of data...
    unsigned char *xData = buildAlphaData(&img[1]);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, xData);
    free(xData);
    //-------------------------------------------------------------------------
    w = img[2].width;
    h = img[2].height;
    //create opengl texture elements
    glGenTextures(1, &gl.exp44.tex);
    //-------------------------------------------------------------------------
    //this is similar to a sprite graphic
    glBindTexture(GL_TEXTURE_2D, gl.exp44.tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //must build a new set of data...
    xData = buildAlphaData(&img[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, xData);
    free(xData);
}

void init() {

}

void checkMouse(XEvent *e)
{
    //printf("checkMouse()...\n"); fflush(stdout);
    //Did the mouse move?
    //Was a mouse button clicked?
    static int savex = 0;
    static int savey = 0;
    //
    if (e->type != ButtonRelease && e->type != ButtonPress &&
            e->type != MotionNotify)
        return;
    if (e->type == ButtonRelease) {
        return;
    }
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) {
            //Left button is down
        }
        if (e->xbutton.button==3) {
            //Right button is down
        }
    }
    if (e->type == MotionNotify) {
        if (savex != e->xbutton.x || savey != e->xbutton.y) {
            //Mouse moved
            savex = e->xbutton.x;
            savey = e->xbutton.y;
        }
    }
}

void screenCapture()
{
    static int fnum = 0;
    static int vid = 0;
    if (!vid) {
        system("mkdir ./vid");
        vid = 1;
    }
    unsigned char *data = (unsigned char *)malloc(gl.xres * gl.yres * 3);
    glReadPixels(0, 0, gl.xres, gl.yres, GL_RGB, GL_UNSIGNED_BYTE, data);
    char ts[32];
    sprintf(ts, "./vid/pic%03i.ppm", fnum);
    FILE *fpo = fopen(ts,"w");	
    if (fpo) {
        fprintf(fpo, "P6\n%i %i\n255\n", gl.xres, gl.yres);
        unsigned char *p = data;
        //go backwards a row at a time...
        p = p + ((gl.yres-1) * gl.xres * 3);
        unsigned char *start = p;
        for (int i=0; i<gl.yres; i++) {
            for (int j=0; j<gl.xres*3; j++) {
                fprintf(fpo, "%c",*p);
                ++p;
            }
            start = start - (gl.xres*3);
            p = start;
        }
        fclose(fpo);
        char s[256];
        sprintf(s, "convert ./vid/pic%03i.ppm ./vid/pic%03i.gif", fnum, fnum);
        system(s);
        unlink(ts);
    }
    ++fnum;
}

int checkKeys(XEvent *e)
{
    //keyboard input?
    static int shift=0;
    if (e->type != KeyPress && e->type != KeyRelease)
        return 0;
    int key = XLookupKeysym(&e->xkey, 0);
    gl.keys[key]=1;
    if (e->type == KeyRelease) {
        gl.keys[key]=0;
        if (key == XK_Shift_L || key == XK_Shift_R)
            shift=0;
        return 0;
    }
    gl.keys[key]=1;
    if (key == XK_Shift_L || key == XK_Shift_R) {
        shift=1;
        return 0;
    }
    (void)shift;
    switch (key) {
        case XK_s:
            screenCapture();
            break;
        case XK_m:
            gl.movie ^= 1;
            break;
        case XK_w:
            timers.recordTime(&timers.walkTime);
            gl.walk ^= 1;
            break;
        case XK_e:
            gl.exp.pos[0] = 200.0;
            gl.exp.pos[1] = -60.0;
            gl.exp.pos[2] =   0.0;
            timers.recordTime(&gl.exp.time);
            gl.exp.onoff ^= 1;
            break;
        case XK_f:
            gl.exp44.pos[0] = 200.0;
            gl.exp44.pos[1] = -60.0;
            gl.exp44.pos[2] =   0.0;
            timers.recordTime(&gl.exp44.time);
            gl.exp44.onoff ^= 1;
            break;
            //Credits
        case XK_c:
            gl.credits ^= 1; 
            break;
        case XK_r:
            if (countp < 14) {
                A.restrict = true;
                gl.punch ^= 1;
                countp++;
            }
            else
                countp = 0;
            break;
        case XK_l:
            gl.cActive ^= 1;
            break;
            //Menu
        case XK_p:
            gl.menu ^= 1;
            break;
        case XK_b:
            gl.background ^= 1;
            break;
        case XK_Left:
            break;
        case XK_Right:
            break;
        case XK_Up:
            if (gcy < 320) 
                gl.jumping = true;
            break;
        case XK_Down:
            break;
        case XK_equal:
            gl.delay -= 0.005;
            if (gl.delay < 0.005)
                gl.delay = 0.005;
            break;
        case XK_minus:
            gl.delay += 0.005;
            break;
        case XK_space:
            gl.Title = false;
            break;
        case XK_Escape:
            return 1;
            break;
    }
    return 0;
}

Flt VecNormalize(Vec vec)
{
    Flt len, tlen;
    Flt xlen = vec[0];
    Flt ylen = vec[1];
    Flt zlen = vec[2];
    len = xlen*xlen + ylen*ylen + zlen*zlen;
    if (len == 0.0) {
        MakeVector(vec, 0.0, 0.0, 1.0);
        return 1.0;
    }
    len = sqrt(len);
    tlen = 1.0 / len;
    vec[0] = xlen * tlen;
    vec[1] = ylen * tlen;
    vec[2] = zlen * tlen;
    return(len);
}

void physics(void)
{
    if (gl.walk || gl.keys[XK_Right] || gl.keys[XK_Left]) {
        //man is walking...
        //when time is up, advance the frame.
        timers.recordTime(&timers.timeCurrent);
        double timeSpan = timers.timeDiff(&timers.walkTime, &timers.timeCurrent);
        if (timeSpan > gl.delay) {
            //advance
            ++gl.walkFrame;
            if (gl.walkFrame >= 7)
                gl.walkFrame -= 7;
            timers.recordTime(&timers.walkTime);
        }
        for (int i=0; i<20; i++) {
            if (gl.keys[XK_Left]) {
                gl.box[i][0] += 1.0 * (0.05 / gl.delay);
                if (gl.box[i][0] > gl.xres + 10.0)
                    gl.box[i][0] -= gl.xres + 10.0;
                gl.camera[0] -= 2.0/lev.tilesize[0] * (0.05 / gl.delay);
                if (gl.camera[0] < 0.0)
                    gl.camera[0] = 0.0;
            } 
            else if (gl.keys[XK_Right]) {
                gl.box[i][0] -= 1.0 * (0.05 / gl.delay);
                if (gl.box[i][0] < -10.0)
                    gl.box[i][0] += gl.xres + 10.0;
                gl.camera[0] += 2.0/lev.tilesize[0] * (0.05 / gl.delay);
                if (gl.camera[0] < 0.0)
                    gl.camera[0] = 0.0;
            }
        }
    }
    if (gl.punch){
        extern int showPunch(int);
        countp = showPunch(countp);
        if (countp >= 7) {
            gl.punch ^= 1;
            countp = 0;
        }
    }

    extern int physicsChicken();
    int countc = physicsChicken();
    if (countc >= 14) {
        //activation here
    }


    if (gl.exp.onoff) {
        //explosion is happening
        timers.recordTime(&timers.timeCurrent);
        double timeSpan = timers.timeDiff(&gl.exp.time, &timers.timeCurrent);
        if (timeSpan > gl.exp.delay) {
            //advance explosion frame
            ++gl.exp.frame;
            if (gl.exp.frame >= 23) {
                //explosion is done.
                gl.exp.onoff = 0;
                gl.exp.frame = 0;
            } else {
                timers.recordTime(&gl.exp.time);
            }
        }
    }
    if (gl.exp44.onoff) {
        //explosion is happening
        timers.recordTime(&timers.timeCurrent);
        double timeSpan = timers.timeDiff(&gl.exp44.time, &timers.timeCurrent);
        if (timeSpan > gl.exp44.delay) {
            //advance explosion frame
            ++gl.exp44.frame;
            if (gl.exp44.frame >= 16) {
                //explosion is done.
                gl.exp44.onoff = 0;
                gl.exp44.frame = 0;
            } else {
                timers.recordTime(&gl.exp44.time);
            }
        }
    }
    //====================================
    //Adjust position of ball.
    //Height of highest tile when ball is?
    //====================================
    Flt dd = lev.ftsz[0];
    int col = (int)((gl.camera[0]+gl.ball_pos[0]) / dd);
    col = col % lev.ncols;
    int hgt = 0;
    for (int i=0; i<lev.nrows; i++) {
        if (lev.arr[i][col] != ' ') {
            hgt = (lev.nrows-i) * lev.tilesize[1];
            break;
        }
    }
    if (gl.ball_pos[1] < (Flt)hgt) {
        gl.ball_pos[1] = (Flt)hgt;
        MakeVector(gl.ball_vel, 0, 0, 0);
    } else {
        gl.ball_vel[1] -= 0.9;
    }
    gl.ball_pos[1] += gl.ball_vel[1];

}

extern int colorFont(std::string);
extern void showText(int, int, int, std::string);	

void render(void)
{
    if (gl.Title) {
        //std::cout << gl.Title << std::endl;
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        extern void showTitlePic(int x, int y, GLuint txt);
        showTitlePic(400,300,gl.titleTexture);	
        return;
    }
    if (peter.health <= 0) {
        //std::cout << gl.End << std::endl;
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        extern void showEndPic(int x, int y, GLuint txt);
        showEndPic(400,300,gl.endTexture);	
        return;
    }

    //Clear the screen
    glClearColor(0.1, 0.1, 0.1, 1.0);

    while (gl.menu) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        extern void pauseScreen(int x, int y);
        pauseScreen(100, 	gl.yres-100);
        return;
    }

    if (gl.credits) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        //show boxes as background
        for (int i=0; i<20; i++) {
            glPushMatrix();
            glTranslated(gl.box[i][0],gl.box[i][1],gl.box[i][2]);
            glColor3f(0.2, 0.2, 0.2);
            glBegin(GL_QUADS);
            glVertex2i( 0,  0);
            glVertex2i( 0, 30);
            glVertex2i(20, 30);
            glVertex2i(20,  0);
            glEnd();
            glPopMatrix();
        }
        //Prototypes:
        extern void showAnthonyName(int x, int y);
        extern void showMohammedName(int x, int y);
        extern void showCleoName(int x, int y);
        extern void showMasonName(int x, int y);
        extern void showEmmanuelName(int x, int y);

        extern void showMohammedPicture(int x , int y, GLuint);
        extern void showMasonPicture(int, int, GLuint);
        extern void showCleoPicture(int, int, GLuint);
        extern void showEmmanuelPic(int, int, GLuint);
        extern void showAnthonyPicture(int, int, GLuint);

        //Function Calls:
        showAnthonyName(100, gl.yres-100);
        showMohammedName(100, gl.yres-200);
        showCleoName(100, gl.yres-300);
        showMasonName(100, gl.yres-400);
        showEmmanuelName(100, gl.yres-500);

        showMohammedPicture(300, 400, gl.tigerTexture);
        showCleoPicture(300, 300, gl.kfcTexture);
        showMasonPicture(300, 200, gl.subaruTexture);
        showEmmanuelPic(300, 100, gl.dogTexture);
        showAnthonyPicture(300, 500, gl.anthonyTexture);
        return;
    }

    if (gl.background) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        extern void showBackground(int x , int y, GLuint);
        showBackground(400, 400, gl.backgroundTexture);
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    showImage(400,300,800,600,gl.backgroundTexture); 

    //	show ground
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2i(0,       220);
    glVertex2i(gl.xres, 220);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2i(gl.xres,   0);
    glVertex2i(0,         0);
    glEnd();

    peter.Jump(gcy);

    float cx = gl.xres/2.0;
    float cy = gcy;//gl.yres/2.0;
    //
    //show ground
    //int xCord = gl.xres;
    //int yCord = 220;
    extern Ground ground(int, int);
    //ground(xCord, yCord);
    //Ground ground(xCord, yCord);
    //ground.render();
    /*glBegin(GL_QUADS);
      glColor3f(0.2, 0.2, 0.2);
      glVertex2i(0,       220);
      glVertex2i(gl.xres, 220);
      glColor3f(0.4, 0.4, 0.4);
      glVertex2i(gl.xres,   0);
      glVertex2i(0,         0);
      glEnd();
      */


    //show boxes as background
    /*for (int i=0; i<20; i++) {
      glPushMatrix();
      glTranslated(gl.box[i][0],gl.box[i][1],gl.box[i][2]);
      glColor3f(0, 0, 0);
      glBegin(GL_QUADS);
      glVertex2i( 0,  0);
      glVertex2i( 0, 30);
      glVertex2i(20, 30);
      glVertex2i(20,  0);
      glEnd();
      glPopMatrix();
      }*/
    renderLevel2(); 
    if (theCurrentLevel==0) {
        //========================
        //Render the tile system
        //========================
        int tx = lev.tilesize[0];
        int ty = lev.tilesize[1];
        Flt dd = lev.ftsz[0];
        Flt offy = lev.tile_base;
        int ncols_to_render = gl.xres / lev.tilesize[0] + 2;
        int col = (int)(gl.camera[0] / dd);
        col = col % lev.ncols;
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
            int row = lev.nrows-1;
            for (int i=0; i<lev.nrows; i++) {
                if (lev.arr[row][col] == 'w') {
                    glColor3f(0.8, 0.8, 0.6);
                    glPushMatrix();
                    //put tile in its place
                    glTranslated((Flt)j*dd+offx, (Flt)i*lev.ftsz[1]+offy, 0);
                    glBegin(GL_QUADS);
                    glVertex2i( 0,  0);
                    glVertex2i( 0, ty);	
                    glVertex2i(tx, ty);
                    glVertex2i(tx,  0);
                    glEnd();
                    glPopMatrix();
                    //cout << "\nbrown tile pos-> x: " << j*dd+offx << " y: " << i*lev.ftsz[1]+offy << endl;
                }
                if (lev.arr[row][col] == 'b') {
                    glColor3f(0.9, 0.2, 0.2);
                    glPushMatrix();
                    glTranslated((Flt)j*dd+offx, (Flt)i*lev.ftsz[1]+offy, 0);
                    glBegin(GL_QUADS);
                    glVertex2i( 0,  0);
                    glVertex2i( 0, ty);
                    glVertex2i(tx, ty);
                    glVertex2i(tx,  0);
                    glEnd();
                    glPopMatrix();
                    //cout << "\nred tile pos-> x: " << j*dd+offx << " y: " << i*lev.ftsz[1]+offy << endl;
                }
                if (lev.arr[row][col] == 'r') {	
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
                }
                if (lev.arr[row][col] == 'g') {	
                    glColor3f(64, 64, 64);
                    glPushMatrix();
                    glTranslated((Flt)j*dd+offx, (Flt)i*lev.ftsz[1]+offy, 0);
                    glBegin(GL_QUADS);
                    glVertex2i( 0,  0);
                    glVertex2i( 0, ty);
                    glVertex2i(tx, ty);
                    glVertex2i(tx,  0);
                    glEnd();
                    glPopMatrix();
                }
                if (lev.arr[row][col] == 'o') {	
                    glColor3f(255, 255, 255);
                    glPushMatrix();
                    glTranslated((Flt)j*dd+offx, (Flt)i*lev.ftsz[1]+offy, 0);
                    glBegin(GL_QUADS);
                    glVertex2i( 0,  0);
                    glVertex2i( 0, ty);
                    glVertex2i(tx, ty);
                    glVertex2i(tx,  0);
                    glEnd();
                    glPopMatrix();
                }
                if (lev.arr[row][col] == 'l') {	
                    glColor3f(0, 0, 0);
                    int localX = (Flt)j*dd+offx;
                    if (localX > 410 && localX < 430) {
                        if (theCurrentLevel+1 == numOfLevels) {
                            while(1) {
                                std::cout << "GAME OVER\n";
                            }
                        }
                        theCurrentLevel++;
                        break;
                    }
                    glPushMatrix();
                    glTranslated((Flt)j*dd+offx, (Flt)i*lev.ftsz[1]+offy, 0);
                    glBegin(GL_QUADS);
                    glVertex2i( 0,  0);
                    glVertex2i( 0, ty);
                    glVertex2i(tx, ty);
                    glVertex2i(tx,  0);
                    glEnd();
                    glPopMatrix();
                }
                /*extern void enemyHealth(int x, int y, int w, int h, Enemy &enemy1);
                  if (lev.arr[row][col] == 'c') {
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
                  if (enemy1.health < 0) 
                  enemy1.health = 0;
                  enemyHealth(locationX, 170, enemy1.health, 14, enemy1);
                  showText(locationX, 80, colorFont("red"), " Enemy Health");
                  }*/

                createSpike('s', spike1, i, j, dd, offy, offx, col, row);
                createEnemyHitbox('c', enemy1, i, j, tx, ty, dd, offy, offx, col, row);
                --row;
            }
            col = (col+1) % lev.ncols;
        } 
    }
    glColor3f(1.0, 1.0, 0.1);
    glPushMatrix();
    //put ball in its place
    glTranslated(gl.ball_pos[0], lev.tile_base+gl.ball_pos[1], 0);
    glBegin(GL_QUADS);
    glVertex2i(-10, 0);
    glVertex2i(-10, 20);
    glVertex2i( 10, 20);
    glVertex2i( 10, 0);
    glEnd();
    glPopMatrix();
    //--------------------------------------
#ifdef SHOW_FAKE_SHADOW
    glColor3f(0.25, 0.25, 0.25);
    glBegin(GL_QUADS);
    glVertex2i(cx-60, 150);
    glVertex2i(cx+50, 150);
    glVertex2i(cx+50, 130);
    glVertex2i(cx-60, 130);
    glEnd();
#endif
    //--------------------------------------
    float h = 200.0;
    float w = h * 0.5;
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.walkTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.walkFrame % 7;
    int iy = 0;
    if (gl.walkFrame >= 7)
        iy = 1;
    float fx = (float)ix / 7.0;
    float fy = (float)iy / 2.0;
    glBegin(GL_QUADS);
    if (gl.keys[XK_Left]) {
        glTexCoord2f(fx+.125, fy+.5); glVertex2i(cx-w, cy-h);
        glTexCoord2f(fx+.125, fy);    glVertex2i(cx-w, cy+h);
        glTexCoord2f(fx,      fy);    glVertex2i(cx+w, cy+h);
        glTexCoord2f(fx,      fy+.5); glVertex2i(cx+w, cy-h);
        gl.last_position = 'l';
    } 
    else if (gl.keys[XK_Right]) {
        glTexCoord2f(fx,      fy+.5); glVertex2i(cx-w, cy-h);
        glTexCoord2f(fx,      fy);    glVertex2i(cx-w, cy+h);
        glTexCoord2f(fx+.125, fy);    glVertex2i(cx+w, cy+h);
        glTexCoord2f(fx+.125, fy+.5); glVertex2i(cx+w, cy-h);
        gl.last_position = 'r';
    }
    else {
        if (gl.last_position == 'l') {
            glTexCoord2f(fx+.125, fy+.5); glVertex2i(cx-w, cy-h);
            glTexCoord2f(fx+.125, fy);    glVertex2i(cx-w, cy+h);
            glTexCoord2f(fx,      fy);    glVertex2i(cx+w, cy+h);
            glTexCoord2f(fx,      fy+.5); glVertex2i(cx+w, cy-h);
        }
        else {
            glTexCoord2f(fx,      fy+.5); glVertex2i(cx-w, cy-h);
            glTexCoord2f(fx,      fy);    glVertex2i(cx-w, cy+h);
            glTexCoord2f(fx+.125, fy);    glVertex2i(cx+w, cy+h);
            glTexCoord2f(fx+.125, fy+.5); glVertex2i(cx+w, cy-h);
        }
    }

    glEnd();
    glPopMatrix();
    if (gl.cActive) {
        extern void chicken();
        chicken();
    }
    //Show Health
    //extern void peterHealth(int, int, int, Peter &peter);
    //peterHealth(100, 500, 80, peter);
    //extern void showHealth(int, int, int, GLuint);
    //showHealth(100, 500, gl.playerHealth, gl.healthTexture);
    showImage(100,520,peter.health,20,gl.health2Texture);
    //Show Healthbar UI	
    //extern void showHealthbar(int, int, GLuint);
    //showHealthbar(100 ,500 ,gl.healthbarTexture);

    //For Text Color
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);

    //Health Bar Text
    showText(50, gl.yres-166, colorFont("white"), "Health");

    //UI Help UI_Display
    //extern void arrowKeysPicture(int, int, GLuint);
    extern void Controls_UI(int, int);
    Controls_UI(620,515);

    //arrowKeysPicture(500, 500, gl.keysTexture);

    //Test
    //showImage(200,200,100,100,gl.spikeTexture);
    //std::cout << "peterX: " << peter.x;
    makeTransparent(&gl.deathTexture, &img[14]);

    if (enemy1.showImage == false) {
        showImage(0,0,0,0,gl.deathTexture);
        showStar(0,0,0,0,gl.ninjaStarTexture);
    }
    extern void enemyHealth_and_star();
    enemyHealth_and_star();

    //Collision
    extern void checkCollision();
    checkCollision();
    //std::cout << std::endl;

    /*	unsigned int c = 0x00ffff44;
        r.bot = gl.yres - 20;
        r.left = 10;
        r.center = 0;
        ggprint8b(&r, 16, c, "W   Walk cycle");
        ggprint8b(&r, 16, c, "E   Explosion");
        ggprint8b(&r, 16, c, "+   faster");
        ggprint8b(&r, 16, c, "-   slower");
        ggprint8b(&r, 16, c, "right arrow -> walk right");
        ggprint8b(&r, 16, c, "left arrow  <- walk left");
        ggprint8b(&r, 16, c, "frame: %i", gl.walkFrame); */
    if (gl.movie) {
        screenCapture();
    } 
}

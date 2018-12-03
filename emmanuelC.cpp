//Author: Emmanuel Chavez
//Fall 2018
//Purpose:
//Shows author's name and image

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
#include "anthonyR.h"
#include "emmanuelC.h"

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define MakeVector(v, x, y, z) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
                             (c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]

Timers timers;
Global gl;
Level lev;
X11_wrapper x11;

Timers::Timers() {
    physicsRate = 1.0 / 30.0;
    oobillion = 1.0 / 1e9;
}
double Timers::timeDiff(struct timespec *start, struct timespec *end) {
    return (double)(end->tv_sec - start->tv_sec ) +
        (double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void Timers::timeCopy(struct timespec *dest, struct timespec *source) {
    memcpy(dest, source, sizeof(struct timespec));
}
void Timers::recordTime(struct timespec *t) {
    clock_gettime(CLOCK_REALTIME, t);
}

class Image;

Sprite::Sprite() {
    onoff = 0;
    frame = 0;
    image = NULL;
    delay = 0.1;
}


Global::~Global() {
    logClose();
}
Global::Global() {
    playerHealth = 80;
	 Title = true;
    menu = false;
    credits = 0;
    background= false;
    logOpen();
    camera[0] = camera[1] = 0.0;
    movie=0;
    movieStep=2;
    xres=800;
    yres=600;
    walk=0;
    punch=0;
    walkFrame=0;
    walkImage=NULL;
	 last_position='r';
    MakeVector(ball_pos, 520.0, 0, 0);
    MakeVector(ball_vel, 0, 0, 0);
    delay = 0.1;
    exp.onoff=0;
    exp.frame=0;
    exp.image=NULL;
    exp.delay = 0.02;
    exp44.onoff=0;
    exp44.frame=0;
    exp44.image=NULL;
    exp44.delay = 0.022;
    for (int i=0; i<20; i++) {
        box[i][0] = rnd() * xres;
        box[i][1] = rnd() * (yres-220) + 270; //Image Movement
        box[i][2] = 0.0;
    }
    memset(keys, 0, 65536);
}

Level::Level() {
    tilesize[0] = 32;
    tilesize[1] = 32;
    ftsz[0] = (Flt)tilesize[0];
    ftsz[1] = (Flt)tilesize[1];
    tile_base = 220.0;
    //read level
    FILE *fpi = fopen("level1.txt","r");
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
void Level::removeCrLf(char *str) {
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

//X Windows variables
X11_wrapper::~X11_wrapper() {
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}
void X11_wrapper::setTitle() {
    //Set the window title bar.
    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Family Chicken Bag");
}
void X11_wrapper::setupScreenRes(const int w, const int h) {
    gl.xres = w;
    gl.yres = h;
}
X11_wrapper::X11_wrapper() {
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
    XSetWindowAttributes swa;
    setupScreenRes(gl.xres, gl.yres);
    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        printf("\n\tcannot connect to X server\n\n");
        exit(EXIT_FAILURE);
    }
    Window root = DefaultRootWindow(dpy);
    XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
    if (vi == NULL) {
        printf("\n\tno appropriate visual found\n\n");
        exit(EXIT_FAILURE);
    } 
    Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
        StructureNotifyMask | SubstructureNotifyMask;
    win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
            vi->depth, InputOutput, vi->visual,
            CWColormap | CWEventMask, &swa);
    GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);
    setTitle();
}
void X11_wrapper::reshapeWindow(int width, int height) {
    //window has been resized.
    setupScreenRes(width, height);
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
    setTitle();
}
void X11_wrapper::checkResize(XEvent *e) {
    //The ConfigureNotify is sent by the
    //server if the window is resized.
    if (e->type != ConfigureNotify)
        return;
    XConfigureEvent xce = e->xconfigure;
    if (xce.width != gl.xres || xce.height != gl.yres) {
        //Window size did change.
        reshapeWindow(xce.width, xce.height);
    }
}
bool X11_wrapper::getXPending() {
    return XPending(dpy);
}
XEvent X11_wrapper::getXNextEvent() {
    XEvent e;
    XNextEvent(dpy, &e);
    return e;
}
void X11_wrapper::swapBuffers() {
    glXSwapBuffers(dpy, win);
}

Image::~Image() { delete [] data; }
Image::Image(const char *fname) {
    if (fname[0] == '\0')
        return;
    //printf("fname **%s**\n", fname);
    int ppmFlag = 0;
    char name[40];
    strcpy(name, fname);
    int slen = strlen(name);
    char ppmname[80];
    if (strncmp(name+(slen-4), ".ppm", 4) == 0)
        ppmFlag = 1;
    if (ppmFlag) {
        strcpy(ppmname, name);
    } else {
        name[slen-4] = '\0';
        //printf("name **%s**\n", name);
        sprintf(ppmname,"%s.ppm", name);
        //printf("ppmname **%s**\n", ppmname);

        char ts[100];
        //system("convert eball.jpg eball.ppm");
        sprintf(ts, "convert %s %s", fname, ppmname);
        system(ts);
    }
    //sprintf(ts, "%s", name);
    //printf("read ppm **%s**\n", ppmname); fflush(stdout);
    FILE *fpi = fopen(ppmname, "r");
    if (fpi) {
        char line[200];
        fgets(line, 200, fpi);
        fgets(line, 200, fpi);
        //skip comments and blank lines
        while (line[0] == '#' || strlen(line) < 2)
            fgets(line, 200, fpi);
        sscanf(line, "%i %i", &width, &height);
        fgets(line, 200, fpi);
        //get pixel data
        int n = width * height * 3;
        data = new unsigned char[n];
        for (int i=0; i<n; i++)
            data[i] = fgetc(fpi);
        fclose(fpi);
    } else {
        printf("ERROR opening image: %s\n",ppmname);
        exit(0);
    }
    if (!ppmFlag)
        unlink(ppmname);
}

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
	 if (gl.walkFrame < 8)
		  gl.walkFrame = 8;
    if (timeSpan > gl.delay) {
        //advance
        ++gl.walkFrame;
        frame++;
        if (gl.walkFrame >= 14)
            gl.walkFrame -= 14;
        timers.recordTime(&timers.walkTime);
    }
    for (int i=0; i<20; i++) {
        /*gl.box[i][0] -= 1.0 * (0.05 / gl.delay);
        if (gl.box[i][0] < -10.0)
            gl.box[i][0] += gl.xres + 10.0;
        gl.camera[0] += 2.0/lev.tilesize[0] * (0.05 / gl.delay);
        if (gl.camera[0] < 0.0)
            gl.camera[0] = 0.0; */
    }
    if (gl.exp.onoff) {
        gl.exp.pos[0] -= 2.0 * (0.05 / gl.delay);
    }
    if (gl.exp44.onoff) {
        gl.exp44.pos[0] -= 2.0 * (0.05 / gl.delay);
    }
    return frame;
}

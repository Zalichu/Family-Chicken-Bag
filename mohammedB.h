#include "emmanuelC.h"
extern Image *grndImg;

class Tile {
public:
        int tx;
        int ty;
        int ncols_to_render;
        int col;
        Flt dd;
        Flt offx;
        Flt offy;
        Flt cdd;
        Flt flo;
        Flt dec;
        Tile();
        void render();
        void physics();
        ~Tile();
private:
};

class Ground {
public:
        int width;
        int height;
        int xCord, yCord;
        Image grndImg[1] = {
	    "./images/background/ground.png"
	};;
        GLuint groundTexture;
        Ground();
		void appendGround(GLuint *texId, Image img);
		void drawGround();
        void render();
        void physics();
        ~Ground();
private:
};


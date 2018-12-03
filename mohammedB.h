#include "emmanuelC.h"

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
        Image *img;
        GLuint groundTexture;
        Ground(int, int);
        void render();
        void physics();
        ~Ground();
private:
};

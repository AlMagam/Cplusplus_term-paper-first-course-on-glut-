#pragma once
#include"Eda.h"


class Block { //individ blocks that make up the snake object in the game
public:
    Block(float pX, float pY, float pZ, float pSize = 1.0f) {
        x = pX;
        y = pY;
        z = pZ;
        size = pSize;
        r = bR; g = bG; b = bB; //rgb colors are set to their default (инициализировал уже)
    };
    ~Block();
    void setX(float pX) { x = pX; }; 
    void setY(float pY) { y = pY; };
    void setZ(float pZ) { z = pZ; };
    float getX() { return x; };
    float getY() { return y; };
    float getZ() { return z; };
    void setColor(float pR, float pG, float pB) { r = pR; g = pG; b = pB; }; //... and color
    void draw() { //draw the block
        glPushMatrix();
        glTranslatef(-x, y, z);
        if (r > 1 || g > 1 || b > 1) {
            glColor3ub(r, g, b);
        }
        else {
            glColor3f(r, g, b);
        }
        glCallList(cube);//вызвали список
        glPopMatrix();
    };

private:
    float x, y, z, size, r, g, b;
};
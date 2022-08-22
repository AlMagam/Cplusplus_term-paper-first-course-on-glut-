#pragma once
#include"Utillh.h"

class Fruit {
public:
    Fruit(int pX, int pZ) {
        x = pX;
        z = pZ;
        angle = 0.0f;
    };
    ~Fruit();
    void draw() {
        angle += 2.0f;
        glPushMatrix();
        glTranslatef(-x, 0, z);
        glRotatef(45,0,0,1);
        glRotatef(angle, 0, 1, 0);
        glutSolidCube(1); //буфер глубины//В нем хранятся данные о расстоянии от каждого пиксела монитора до точек в объёмном пространстве оpenGL, принадлежащих этому пикселю
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        float gC = 0.5;
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLES);
        glVertex3f(0 - gC, 0 - gC, 0 - gC);
        glVertex3f(1 - gC, 0 - gC, 0 - gC);
        glVertex3f(0.5 - gC, 0 - gC, 1 - gC);
        glTexCoord2f(0.5, 1); glVertex3f(0.5 - gC, 1 - gC, 0.5 - gC);//set the current texture coordinates 
        glTexCoord2f(0, 0); glVertex3f(0 - gC, 0 - gC, 0 - gC);
        glTexCoord2f(1, 0); glVertex3f(1 - gC, 0 - gC, 0 - gC);
        glTexCoord2f(0.5, 1); glVertex3f(0.5 - gC, 1 - gC, 0.5 - gC);
        glTexCoord2f(1, 0); glVertex3f(0 - gC, 0 - gC, 0 - gC);
        glTexCoord2f(0, 0); glVertex3f(0.5 - gC, 0 - gC, 1 - gC);
        glTexCoord2f(0.5, 1); glVertex3f(0.5 - gC, 1 - gC, 0.5 - gC);
        glTexCoord2f(0, 0); glVertex3f(1 - gC, 0 - gC, 0 - gC);
        glTexCoord2f(1, 0); glVertex3f(0.5 - gC, 0 - gC, 1 - gC);
        glEnd();
         glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
    };
    float getX() { return x; };
    float getZ() { return z; };
    void setX(float pX) { x = pX; };
    void setZ(float pZ) { z = pZ; };
    float getAngle() { return angle; };
private:
    float x, z, angle;
};
static Fruit* fruit = new Fruit(1, 1);//////////
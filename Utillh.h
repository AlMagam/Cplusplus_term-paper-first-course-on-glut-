#pragma once
#include<gl/glut.h>

static float yCamPos = 20.0f;
static float xCamPos = 0.f;//!!!!
static float zCamPos = -5.0f;//!!!!

static float centerX = 0.0f;
static float centerY = 0.0f;
static float centerZ = 0.0f;

static float  upX = 45;
static float upY = 0.1f;
static float upZ = 50;

static int camera_mode = 0;

static GLfloat lightAmbient[] = { 0.5,0.5,0.5,1 };// колір фонового освітлення 
static GLfloat lightDiffuse[] = { 1,1,1,1 };// колір дифузного освітлення 
static GLfloat lightPosition[] = { 0,3,0 };// розташування джерела світла

static GLuint texture[2];
static GLuint cube;

static float cR = 0; static float cG = 1; static float cB = 0; //centre line color
static float eR = 0; static float eG = 1; static float eB = 0; //edge lines color
static float bR = 47; static float bG = 181; static float bB = 243; //дефолт block color

enum Direction {
    D_LEFT, D_RIGHT, D_UP, D_DOWN
};

inline void buildDLs() { //Build display lists, right now only compiles a cube
    //группa команд//Если нужно несколько раз обращаться к одной и той же группе команд,эти команды можно объединить в так называемый список изображений (display list) и вызывать его при необходимости. Для того, чтобы создать новый список изображений надо поместить все команды, которые должны в него войти между командными скобками:
    cube = glGenLists(1);//создали список(полож.целое число)(1)уник.имя
    glNewList(cube, GL_COMPILE);//список + режим
    glBegin(GL_QUADS);//четырёхугольник
    glNormal3f(0, 0, 1);
    glVertex3f(0.5, 0.5, 0.5); //back face
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glNormal3f(0, 0, -1);
    glVertex3f(0.5, 0.5, -0.5); //front face
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glNormal3f(0, -1, 0); //bottom face
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glNormal3f(0, 1, 0); //top face
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glNormal3f(-1, 0, 0); //right face
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glNormal3f(1, 0, 0); //left face
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();
    glEndList();//Конец списка изображений
}

inline void drawGrid(void) { //hardcoded values for grid...
    glColor3ub(24, 221, 0);//клеточки на поле
    glLineWidth(2);
    glBegin(GL_LINES);
    for (float i = -7; i <= 5; i++) {//=11 клеток//длинна
        glVertex3f(-5 - 0.5, 0 - 0.5f, i + 0.5f);
        glVertex3f(6 - 0.5, 0 - 0.5f, i + 0.5f);
    }
    for (float i = -5; i <= 6; i++) {//=11 клеток//ширина
        glVertex3f(i - 0.5, -0.5f, -6 - 0.5f);
        glVertex3f(i - 0.5, -0.5f, 6 - 0.5f);
    }
    glEnd();
    glLineWidth(1);
    glColor3ub(30, 2, 63);//заливка фигурки
    glBegin(GL_QUADS);//залили всё поле
    glNormal3f(0, 1, 0);
    glVertex3f(-5 - 0.5, -0.51, -6.5);
    glVertex3f(-5 - 0.5, -0.51, 6.5);
    glVertex3f(6 - 0.5, -0.51, 6.5);
    glVertex3f(6 - 0.5, -0.51, -6.5);
    glEnd();

    glColor3ub(30, 2, 63);//https://www.cyberforum.ru/opengl/thread1916285.html
    for (int i = -5; i <= 5; i++) {
        glPushMatrix();
        glTranslatef(-6, 0, i);//сам список рисует только один кубик поэтому
        glCallList(cube);//выполнение именованного списка отображения(отрисовывает правую стенку(блоки))

        glColor3f(cR, cG, cB);//цвет вершины
        glLineWidth(10);//провели большую линию
        glBegin(GL_LINES);
        glVertex3f(0, 0.51, -0.5);
        glVertex3f(0, 0.51, 0.5);
        glEnd();
        glLineWidth(2);//контуры справа(маленькие)
        glBegin(GL_LINES);
        glVertex3f(0.5, 0.51, -0.5);
        glVertex3f(0.5, 0.51, 0.5);
        glVertex3f(-0.5, 0.51, -0.5);
        glVertex3f(-0.5, 0.51, 0.5);
        glEnd();
        glColor3ub(30, 2, 63);


        glPopMatrix();
        glPushMatrix();
        glTranslatef(6, 0, i);
        glCallList(cube);//выполнение именованного списка отображения(отрисовывает левую стенку(блоки))

        glColor3f(cR, cG, cB);
        glLineWidth(10);//провели большую линию
        glBegin(GL_LINES);
        glVertex3f(0, 0.51, -0.5);
        glVertex3f(0, 0.51, 0.5);
        glEnd();
        glLineWidth(2);//контуры слева(маленькие)
        glBegin(GL_LINES);
        glVertex3f(0.5, 0.51, -0.5);
        glVertex3f(0.5, 0.51, 0.5);
        glVertex3f(-0.5, 0.51, -0.5);
        glVertex3f(-0.5, 0.51, 0.5);
        glEnd();
        glColor3ub(30, 2, 63);

        glPopMatrix();
        glPushMatrix();
        glTranslatef(i, 0, -6);
        glCallList(cube); //выполнение именованного списка отображения(отрисовывает нижнюю стенку(блоки))

        glColor3f(cR, cG, cB);
        glLineWidth(10);//провели большую линию
        glBegin(GL_LINES);
        glVertex3f(-0.5, 0.51, 0);
        glVertex3f(0.5, 0.51, 0);
        glEnd();
        glLineWidth(2);//контуры снизу(маленькие)
        glBegin(GL_LINES);
        glVertex3f(-0.5, 0.51, 0.5);
        glVertex3f(0.5, 0.51, 0.5);
        glVertex3f(-0.5, 0.51, -0.5);
        glVertex3f(0.5, 0.51, -0.5);
        glEnd();
        glColor3ub(30, 2, 63);

        glPopMatrix();
        glPushMatrix();
        glTranslatef(i, 0, 6);//выполнение именованного списка отображения(отрисовывает верхнюю стенку(блоки))
        glCallList(cube);

        glColor3f(cR, cG, cB);
        glLineWidth(10);//провели большую линию
        glBegin(GL_LINES);
        glVertex3f(-0.5, 0.51, 0);
        glVertex3f(0.5, 0.51, 0);
        glEnd();
        glLineWidth(2);//контуры сверху(маленькие)
        glBegin(GL_LINES);
        glVertex3f(-0.5, 0.51, 0.5);
        glVertex3f(0.5, 0.51, 0.5);
        glVertex3f(-0.5, 0.51, -0.5);
        glVertex3f(0.5, 0.51, -0.5);
        glEnd();
        glColor3ub(30, 2, 63);

        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(6, 0, 6); // сверху слева кубик
    glCallList(cube);
    glColor3f(cR, cG, cB);
    glLineWidth(10);//провели большую линию
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, -0.5);
    glEnd();
    glLineWidth(2);//контуры (маленькие)
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.51, 0.5);
    glVertex3f(0.5, 0.51, 0.5);
    glVertex3f(0.5, 0.51, 0.5);
    glVertex3f(0.5, 0.51, -0.5);
    glVertex3f(-0.51, 0.51, -0.51);
    glVertex3f(-0.51, -0.51, -0.51);
    glEnd();
    glColor3ub(30, 2, 63);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0, 6); // сверху справа кубик
    glCallList(cube);
    glColor3f(cR, cG, cB);
    glLineWidth(10);//провели большую линию
    glBegin(GL_LINES);
    glVertex3f(0.5, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, -0.5);
    glEnd();
    glLineWidth(2);//контуры (маленькие)
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.51, 0.5);
    glVertex3f(0.5, 0.51, 0.5);
    glVertex3f(-0.5, 0.51, 0.5);
    glVertex3f(-0.5, 0.51, -0.5);
    glVertex3f(0.51, 0.51, -0.51);
    glVertex3f(0.51, -0.51, -0.51);
    glEnd();
    glColor3ub(30, 2, 63);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0, -6); // снизу справа кубик
    glCallList(cube);
    glColor3f(cR, cG, cB);
    glLineWidth(10);//провели большую линию
    glBegin(GL_LINES);
    glVertex3f(0.5, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0.5);
    glEnd();
    glLineWidth(2);//контуры (маленькие)
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.51, -0.5);
    glVertex3f(0.5, 0.51, -0.5);
    glVertex3f(-0.5, 0.51, 0.5);
    glVertex3f(-0.5, 0.51, -0.5);
    glVertex3f(0.51, 0.51, 0.51);
    glVertex3f(0.51, -0.51, 0.51);
    glEnd();
    glColor3ub(30, 2, 63);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0, -6); // снизу слева кубик
    glCallList(cube);
    glColor3f(cR, cG, cB);
    glLineWidth(10);//провели большую линию
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0.5);
    glEnd();
    glLineWidth(2);//контуры (маленькие)
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.51, -0.5);
    glVertex3f(0.5, 0.51, -0.5);
    glVertex3f(0.5, 0.51, 0.5);
    glVertex3f(0.5, 0.51, -0.5);
    glVertex3f(-0.51, 0.51, 0.51);
    glVertex3f(-0.51, -0.51, 0.51);
    glEnd();
    glColor3ub(30, 2, 63);
    glPopMatrix();
}
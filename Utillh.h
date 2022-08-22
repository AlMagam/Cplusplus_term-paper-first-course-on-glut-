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

static GLfloat lightAmbient[] = { 0.5,0.5,0.5,1 };// ���� �������� ��������� 
static GLfloat lightDiffuse[] = { 1,1,1,1 };// ���� ��������� ��������� 
static GLfloat lightPosition[] = { 0,3,0 };// ������������ ������� �����

static GLuint texture[2];
static GLuint cube;

static float cR = 0; static float cG = 1; static float cB = 0; //centre line color
static float eR = 0; static float eG = 1; static float eB = 0; //edge lines color
static float bR = 47; static float bG = 181; static float bB = 243; //������ block color

enum Direction {
    D_LEFT, D_RIGHT, D_UP, D_DOWN
};

inline void buildDLs() { //Build display lists, right now only compiles a cube
    //�����a ������//���� ����� ��������� ��� ���������� � ����� � ��� �� ������ ������,��� ������� ����� ���������� � ��� ���������� ������ ����������� (display list) � �������� ��� ��� �������������. ��� ����, ����� ������� ����� ������ ����������� ���� ��������� ��� �������, ������� ������ � ���� ����� ����� ���������� ��������:
    cube = glGenLists(1);//������� ������(�����.����� �����)(1)����.���
    glNewList(cube, GL_COMPILE);//������ + �����
    glBegin(GL_QUADS);//��������������
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
    glEndList();//����� ������ �����������
}

inline void drawGrid(void) { //hardcoded values for grid...
    glColor3ub(24, 221, 0);//�������� �� ����
    glLineWidth(2);
    glBegin(GL_LINES);
    for (float i = -7; i <= 5; i++) {//=11 ������//������
        glVertex3f(-5 - 0.5, 0 - 0.5f, i + 0.5f);
        glVertex3f(6 - 0.5, 0 - 0.5f, i + 0.5f);
    }
    for (float i = -5; i <= 6; i++) {//=11 ������//������
        glVertex3f(i - 0.5, -0.5f, -6 - 0.5f);
        glVertex3f(i - 0.5, -0.5f, 6 - 0.5f);
    }
    glEnd();
    glLineWidth(1);
    glColor3ub(30, 2, 63);//������� �������
    glBegin(GL_QUADS);//������ �� ����
    glNormal3f(0, 1, 0);
    glVertex3f(-5 - 0.5, -0.51, -6.5);
    glVertex3f(-5 - 0.5, -0.51, 6.5);
    glVertex3f(6 - 0.5, -0.51, 6.5);
    glVertex3f(6 - 0.5, -0.51, -6.5);
    glEnd();

    glColor3ub(30, 2, 63);//https://www.cyberforum.ru/opengl/thread1916285.html
    for (int i = -5; i <= 5; i++) {
        glPushMatrix();
        glTranslatef(-6, 0, i);//��� ������ ������ ������ ���� ����� �������
        glCallList(cube);//���������� ������������ ������ �����������(������������ ������ ������(�����))

        glColor3f(cR, cG, cB);//���� �������
        glLineWidth(10);//������� ������� �����
        glBegin(GL_LINES);
        glVertex3f(0, 0.51, -0.5);
        glVertex3f(0, 0.51, 0.5);
        glEnd();
        glLineWidth(2);//������� ������(���������)
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
        glCallList(cube);//���������� ������������ ������ �����������(������������ ����� ������(�����))

        glColor3f(cR, cG, cB);
        glLineWidth(10);//������� ������� �����
        glBegin(GL_LINES);
        glVertex3f(0, 0.51, -0.5);
        glVertex3f(0, 0.51, 0.5);
        glEnd();
        glLineWidth(2);//������� �����(���������)
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
        glCallList(cube); //���������� ������������ ������ �����������(������������ ������ ������(�����))

        glColor3f(cR, cG, cB);
        glLineWidth(10);//������� ������� �����
        glBegin(GL_LINES);
        glVertex3f(-0.5, 0.51, 0);
        glVertex3f(0.5, 0.51, 0);
        glEnd();
        glLineWidth(2);//������� �����(���������)
        glBegin(GL_LINES);
        glVertex3f(-0.5, 0.51, 0.5);
        glVertex3f(0.5, 0.51, 0.5);
        glVertex3f(-0.5, 0.51, -0.5);
        glVertex3f(0.5, 0.51, -0.5);
        glEnd();
        glColor3ub(30, 2, 63);

        glPopMatrix();
        glPushMatrix();
        glTranslatef(i, 0, 6);//���������� ������������ ������ �����������(������������ ������� ������(�����))
        glCallList(cube);

        glColor3f(cR, cG, cB);
        glLineWidth(10);//������� ������� �����
        glBegin(GL_LINES);
        glVertex3f(-0.5, 0.51, 0);
        glVertex3f(0.5, 0.51, 0);
        glEnd();
        glLineWidth(2);//������� ������(���������)
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
    glTranslatef(6, 0, 6); // ������ ����� �����
    glCallList(cube);
    glColor3f(cR, cG, cB);
    glLineWidth(10);//������� ������� �����
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, -0.5);
    glEnd();
    glLineWidth(2);//������� (���������)
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
    glTranslatef(-6, 0, 6); // ������ ������ �����
    glCallList(cube);
    glColor3f(cR, cG, cB);
    glLineWidth(10);//������� ������� �����
    glBegin(GL_LINES);
    glVertex3f(0.5, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, -0.5);
    glEnd();
    glLineWidth(2);//������� (���������)
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
    glTranslatef(-6, 0, -6); // ����� ������ �����
    glCallList(cube);
    glColor3f(cR, cG, cB);
    glLineWidth(10);//������� ������� �����
    glBegin(GL_LINES);
    glVertex3f(0.5, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0.5);
    glEnd();
    glLineWidth(2);//������� (���������)
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
    glTranslatef(6, 0, -6); // ����� ����� �����
    glCallList(cube);
    glColor3f(cR, cG, cB);
    glLineWidth(10);//������� ������� �����
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0);
    glVertex3f(0, 0.51, 0.5);
    glEnd();
    glLineWidth(2);//������� (���������)
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
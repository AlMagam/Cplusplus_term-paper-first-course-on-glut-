
#include<gl/freeglut.h>

#include"Snakes.h"
#include <stdio.h>


#include <time.h>
#include <string>
#include <chrono>



//#pragma comment (lib, "opengl32.lib")
//#pragma comment (lib, "glu32.lib")



void draw(void) { //GLUT doesn't let me change it's main loop so the drawing loop is also where the game update logic goes too

    snake->update(); //update snake position
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();//загружаем еденичную матрицу( сбрасываем матрицу обратно в ее состояние по умолчанию.)
    gluLookAt(//куда смотрит камера
        xCamPos, yCamPos, zCamPos, //eye (позиц.точки камеры)
        0, 0, 0,  //centre поз.точки в которую смотрим
        0, 1, 0   //up
    );
    drawGrid();
    snake->draw();
    fruit->draw();
    glutSwapBuffers();
}

void resize(int w, int h) { //function called on resize of window
    if (h == 0)
        h = 1;
    float ratio = w * 1.0f / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(50, ratio, 1, 200);
    glMatrixMode(GL_MODELVIEW);
}

void keyEvents(unsigned char key, int x, int y) { //function called when normal keys are pressed
    switch (key) {
    case 27: //escape key
        exit(0);
        break;
    }
}

void set_camera()
{
    if (camera_mode > 3)
    {
        camera_mode = 0;
    }else { camera_mode++;}

    glMatrixMode(GL_PROJECTION);


    if (camera_mode == 0)
    {
        xCamPos = 0.0f;
        yCamPos = 20.0f;
        zCamPos = -5.0f;
        centerX = 0.0f;
        centerY = 0.0f;
        centerZ = 0.0f;

    }
    if (camera_mode == 1)
    {
        xCamPos = 5.0f;
        yCamPos = 20.0f;
        zCamPos = -5.0f;
        centerX = 0.0f;
        centerY = 0.0f;
        centerZ = 0.0f;

        
    }
    else if (camera_mode == 2)
    {
        xCamPos = -2.0f;//-2
        yCamPos = 5.0f;//5
        zCamPos = -10.0f;//20
        centerX = 0.0f;
        centerY = 0.0f;
        centerZ = 0.0f;

        
    }
    else if (camera_mode == 3)
    {
        xCamPos = -5.0f;//-2
        yCamPos = 35.0f;//35
        zCamPos = -5.0f;//-5.0
        centerX = 0.0f;
        centerY = 0.0f;
        centerZ = 0.0f;
   
        
    }
    
    glMatrixMode(GL_MODELVIEW);//говорит о том, что работы будет теперь просмотром, а не проектом. для поворота сцені
}


void specialKeys(int key, int x, int y) { //function called when special keys are pressed
    switch (key) {
    case GLUT_KEY_F1:
        set_camera();
        break;
    case GLUT_KEY_LEFT:
        snake->move(D_LEFT);
        break;
    case GLUT_KEY_RIGHT:
        snake->move(D_RIGHT);
        break;
    case GLUT_KEY_UP:
        snake->move(D_UP);
        break;
    case GLUT_KEY_DOWN:
        snake->move(D_DOWN);
        break;
    }
}


void initGL(void) {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
}




void mouseEvents(int button, int dir, int x, int y) { //function called on mouse events
    switch (button) {
    /*case 2:
        printf("ITS KEY\n");
        xCamPos += 5;
        yCamPos -= 0.5;
        zCamPos += 0.5;
        break;*/
    case 3: //scroll up and zoom in
        printf("zoom in\n");
        yCamPos -= 0.5;
        break;
    case 4: //scroll down and zoom out
        printf("zoom out\n");
        yCamPos += 0.5;
        break;
    }
}
//////////////////////



int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("(Snakee)");

    initGL();
    buildDLs();
  

    glutDisplayFunc(draw);
    glutIdleFunc(draw);//эффект движения змейки//kогда ваше приложение простаивает(т. е. ничего не делает.) вызывается эта функция
    glutReshapeFunc(resize);


    
    glutKeyboardFunc(keyEvents);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseEvents);

    //glutPassiveMotionFunc(motionpas);
  
    glutMainLoop();

    return 1;
}

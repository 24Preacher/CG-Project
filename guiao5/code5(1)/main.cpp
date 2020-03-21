#include <stdio.h>

#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>


float alfaview = -M_PI / 4 , betaview = -M_PI / 4, step = 2.0;
float px=10,py=10,pz=10;
float dx,dy,dz;
int mode = GL_LINE;
float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;


float normA (float x ,float y, float z){
    return sqrt(x*x + y*y + z*z);
}

void normaliza (float* x ,float* y, float* z){
    float xx= *x, yy = *y, zz= *z;
    float norma = normA (xx,yy,zz);
    *x = xx/norma;
    *y = yy/norma;
    *z = zz/norma;
}


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}



void arvores(int n){

    float x,z;
    srand((unsigned int)time(NULL));
    int i;
    float posX[n];
    float posZ[n];
    for(i = 0; i<n; i++){

        posX[i] = ((float)rand()/(float)(RAND_MAX))*200.0 - 100.0;
        posZ[i] = ((float)rand()/(float)(RAND_MAX))*200.0 - 100.0;

    }

    for(i = 0; i<n; i++){

        x = posX[i];
        z = posZ[i];


        glPushMatrix();
        glTranslatef(x, 0, z);
        glRotatef(-90,1,0,0);
        glutSolidCone(1, 3, 4, 4);
        glTranslatef(0,0,2.5);
        glutSolidCone(3, 5, 10, 10);
        glPopMatrix();



    }
}






void renderScene(void) {

    float viewx, viewy, viewz;
    viewx = cos(betaview)*sin(alfaview);
    viewy = sin(betaview);
    viewz = cos(betaview)*cos(alfaview);

    normaliza (&viewx,&viewy,&viewz);
    dx = viewx;
    dy = viewy;
    dz = viewz;

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(px, py, pz,
              px + dx, py + dy, pz + dz,
              0.0f,1.0f,0.0f);

    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);

    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);
    glVertex3f(100.0f, 0, 100.0f);

    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK,mode);


    arvores(20);


    glPushMatrix();
    glutSolidTorus(2, 6, 10, 10);
    glPopMatrix();

   // glPushMatrix();
   // glTranslatef(5,0,5);
   // glutSolidTeapot(20);
   // glPopMatrix();
    // End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

    switch (c) {
        case 'd':
            alfaview -= M_PI/64;
            break;
        case 'a':
            alfaview += M_PI/64;
            break;
        case 'w':
            px += step*dx;
            py += step*dy;
            pz += step*dz;
            break;
        case 's':
            px -= step*dx;
            py -= step*dy;
            pz -= step*dz;
            break;
        case 'm':
            if(mode == GL_LINE){
                mode = GL_POINT;
                break;
            }else if(mode == GL_POINT){
                mode = GL_FILL;
                break;
            }else if(mode == GL_FILL){
                mode = GL_LINE;
                break;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_UP :
            betaview += M_PI/64;
            if (betaview > M_PI/3)
                betaview = M_PI / 3;
            break;
        case GLUT_KEY_DOWN:
            betaview -= M_PI/64;
            if (betaview < -M_PI/3)
                betaview = -M_PI / 3;
            break;
        default:
            break;
    }

    glutPostRedisplay();

}




void printInfo() {

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));

    printf("\nUse Arrows to move the camera up/down and left/right\n");
    printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    //spherical2Cartesian();

    printInfo();

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
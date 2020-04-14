

#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

float height=2.0f;
float x = 0.0f;
float z = 0.0f;


float px = 0, py = 0, pz = 0;

float alfaview = 0 , betaview = 0, step = 2.0;
float dx,dy,dz;
float eyev = 2.0;
unsigned int t, tw, th, m;
unsigned char *imageData;
float *vertexB;
GLuint  buffers[1];
int seed = 1;
int mode = GL_LINE;

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

float h(int i, int j){
    return (float) (*(imageData + j*tw + i));
}


float hf(float x, float z){
  int x1 = floor(x);
  int x2 = x1 + 1;
  int z1 = floor(z);
  int z2 = z1 + 1;
  float px,pz;
  float fx = x-x1;
  float fz = z-z1;
  float h_x1_z = h(x1,z1) * (1-fz) + h(x1,z2) * fz;
  float h_x2_z = h(x2,z1) * (1-fz) + h(x2,z2) * fz;
  return (h_x1_z * (1 - fx) + h_x2_z * fx);

}

void arvores(int n){

    float x,z;
    srand(seed);
    int i;
    float posX[n];
    float posZ[n];
    for(i = 0; i<n; i++){

      posX[i] = ((float)rand()/(float)(RAND_MAX))*200.0 - 100.0;
      posZ[i] = ((float)rand()/(float)(RAND_MAX))*200.0 - 100.0;
        if (normA(posX[i],0,posZ[i]) < 50)
        i--;


    }

    for(i = 0; i<n; i++){

        x = posX[i];
        z = posZ[i];


        glPushMatrix();
        glTranslatef(x, hf(x+128,z+128), z);
        glRotatef(-90,1,0,0);
        glColor3f(0.647059,0.164706,0.164706);
        glutSolidCone(1, 3, 4, 4);
        glTranslatef(0,0,2.5);
        glColor3f(0.137255,0.556863,0.137255);
        glutSolidCone(3, 5, 10, 10);
        glPopMatrix();



    }
}
void controlCoordenadas(){
	if (px < -128)
		px = -128;
	if (px > 128)
		px = 128;
	if (pz < -128)
		pz = -128;
	if (pz > 128)
		pz = 128;
}

void drawteepots(int number, float radius){
  float alfa = 0;
  float angleStep = 2*M_PI/number;
  float px, pz;
  int i=0;


    for (i=0; i<number; i++){
      px = radius * sin(alfa);
      pz = radius * cos(alfa);
      glPushMatrix();
      glTranslatef(px,hf(px+128,pz+128)+0.75,pz);
      glRotatef(alfa*180/M_PI -90 ,0,1,0);
      glutSolidTeapot(1);
      alfa += angleStep;
      glPopMatrix();

    }
}

void direcao(){
  float viewX, viewY, viewZ;
  viewX = cos(betaview)*sin(alfaview);
  viewY = sin(betaview);
  viewZ = cos(betaview)*cos(alfaview);

  normaliza (&viewX,&viewY,&viewZ);
  dx = viewX;
  dy = viewY;
  dz = viewZ;
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}







void renderScene(void) {
    int i;
    direcao();

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
  gluLookAt(px,  hf(px+128,pz+128)+ eyev, pz,
            px + dx, hf(px+128,pz+128) + eyev + dy,pz + dz,
            0.0f,1.0f,0.0f);

	// just so that it renders something before the terrain is built
	// to erase when the terrain is ready
  glPolygonMode(GL_FRONT_AND_BACK,mode);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glColor3f(0.5,1,0.5);

	glVertexPointer(3,GL_FLOAT,0,0);
	for(i = 0; i < th -1; i++){
	    glDrawArrays(GL_TRIANGLE_STRIP, i*tw*2, tw*2);
	}



    arvores(100);

    glColor3f(0,0,1);
    drawteepots(6,15);

    glColor3f(1,0,0);
    drawteepots(24,35);

     glPushMatrix();

     glTranslatef(0,hf(128,128),0);
     glColor3f(0.737255,0.560784,0.560784);
     glutSolidTorus(1, 3, 10, 10);
     glPopMatrix();

// End of frame
	glutSwapBuffers();
}


void help() {

        printf ( " ┌-------------------------------------------------HELP---------------------------------------------┐\n");
        printf ( " |                                                                                                  |\n");
        printf ( " |                                                                                                  |\n");
        printf ( " |                                                                                                  |\n");
        printf ( " |      Controls :                                                                                  |\n");
        printf ( " |         move forward: w                                                                          |\n");
        printf ( " |         move backwards: s                                                                        |\n");
        printf ( " |         move right: d                                                                            |\n");
        printf ( " |         move left : a                                                                            |\n");
        printf ( " |         look left: LEFT KEY                                                                      |\n");
        printf ( " |         look right: RIGHT KEY                                                                    |\n");
        printf ( " |         look up: UP KEY                                                                          |\n");
        printf ( " |         look down: DOWN KEY                                                                      |\n");
        printf ( " |         switch drawing mode: m                                                                   |\n");
        printf ( " |         switch tree seed: n                                                                      |\n");
        printf ( " |                                                                                                  |\n");
        printf ( " └--------------------------------------------------------------------------------------------------┘\n");
}



void processKeys(unsigned char c, int xx, int yy) {

    switch (c) {
        case 'd':
            alfaview -= M_PI/2;
            direcao();
            px += step*dx;
            pz += step*dz;
            alfaview += M_PI/2;
            controlCoordenadas();
            break;
        case 'a':
            alfaview += M_PI/2;
            direcao();
            px +=step*dx;
            pz += step*dz;
            alfaview -= M_PI/2;
            controlCoordenadas();
            break;
        case 'w':
            px += step*dx;
            pz += step*dz;
            controlCoordenadas();
            break;
        case 's':
            px -= step*dx;
            pz -= step*dz;
            controlCoordenadas();
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
        case 'n':
            seed = rand();
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
        case GLUT_KEY_RIGHT:
            alfaview -= M_PI/64;
            break;
        case GLUT_KEY_LEFT:
            alfaview += M_PI/64;
            break;
        default:
            break;
    }

    glutPostRedisplay();

}



void plano(){
    float d = 1.0;
    int i, j;


    float x_neg = -(tw/2.0);
    float z_neg = -(th/2.0);

    int n_vertice = (tw*2)*(th-1);

    vertexB = (float *) malloc(sizeof(float) * 3 * (n_vertice));
    m = 0;
    for(i=0; i<th-1; i++){
        for(j=0; j<tw; j++){
            vertexB[m++] = x_neg + d*j;
            vertexB[m++] = h(j,i);
            vertexB[m++] = z_neg + d*i;

            vertexB[m++] = x_neg + d*j;
            vertexB[m++] = h(j, i+1);
            vertexB[m++] = z_neg + d*(i+1);
        }
    }
}




void init() {
    ilInit();
// 	Load the height map "terreno.jpg"
    ilGenImages(1,&t);
    ilBindImage(t);

    ilLoadImage((ILstring)"terreno.jpg");

    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);

    imageData = ilGetData();
    plano();
// 	Build the vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glGenBuffers(1,buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,m*sizeof(float), vertexB, GL_STATIC_DRAW);

// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}


int main(int argc, char **argv) {

  help();
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("CG@DI-UM");
	glewInit();

// Required callback registry
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
  glutSpecialFunc(processSpecialKeys);

	init();

// enter GLUT's main cycle
	glutMainLoop();

	return 0;
}

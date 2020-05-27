#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include "headers/parser.h"


float alfaview = -M_PI / 4 , betaview = -M_PI / 4, step = 0.2;
float px=10,py=10,pz=10;
float dx,dy,dz;
pointsMatrix points;
instructionsMatrix inst;
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

void runInstruction(int i , int j){

	if(inst[i][j].getInstruction() == 'r'){
		glRotatef(inst[i][j].getAngle(),inst[i][j].getX(),inst[i][j].getY(),inst[i][j].getZ());
	}
	else if(inst[i][j].getInstruction() == 't'){
		glTranslatef(inst[i][j].getX(),inst[i][j].getY(),inst[i][j].getZ());
	}
	else if(inst[i][j].getInstruction() == 's'){
		glScalef(inst[i][j].getX(),inst[i][j].getY(),inst[i][j].getZ());
	}
	else if(inst[i][j].getInstruction() == 'c'){
		glColor3f(inst[i][j].getX(),inst[i][j].getY(),inst[i][j].getZ());
	}
}

void drawModel(int i){
	glBegin(GL_TRIANGLES);
	unsigned int j;
	for(j=0;j<points[i].size();j++){
		glVertex3f(points[i][j]->x,points[i][j]->y,points[i][j]->z);
	}
	glEnd();
}

void drawPoints (){
  unsigned int i,j;

	for(i=0;i<points.size();i++){
		glPushMatrix();
		for(j=0;j<inst[i].size();j++){
			runInstruction(i,j);
			}
			drawModel(i);
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

	// Eixos Ordenados.
	glBegin(GL_LINES);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(-100.0f,0.0f,0.0f);
	glVertex3f(100.0f,0.0f,0.0f);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f,-100.0f,0.0f);
	glVertex3f(0.0f,100.0f,0.0f);

	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f,0.0f,-100.0f);
	glVertex3f(0.0f,0.0f,100.0f);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK,mode);
	drawPoints();


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


// put code to process regular keys in here

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
// put code to process special keys in here

}

void help(){
printf ( " ┌-------------------------------------------------HELP---------------------------------------------┐\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣$ ./Engine <XML_INPUT_FILE>                                                                   |\n");
printf ( " |                                                                                                  |\n");
printf ( " |                                                                                                  |\n");
printf ( " |      Controls :                                                                                  |\n");
printf ( " |         move forward: w                                                                          |\n");
printf ( " |         move backwards: s                                                                        |\n");
printf ( " |         look left: a                                                                             |\n");
printf ( " |         look right: d                                                                            |\n");
printf ( " |         look up: UP KEY                                                                          |\n");
printf ( " |         look down: DOWN KEY                                                                      |\n");
printf ( " |         switch drawing mode: m                                                                   |\n");
printf ( " |                                                                                                  |\n");
printf ( " └--------------------------------------------------------------------------------------------------┘\n");
}


int main(int argc, char **argv) {
  std::string arg = argv[1];
	if(argc != 2 )
	printf("invalid input\n");
  if(!arg.compare("-help")){
    help();
    return 1;
  }


  std::string folder = "scenes/";
  folder.append(arg);
  char * path = new char[folder.size() + 1];
  std::copy(folder.begin(), folder.end(), path);
 loadDoc (path,&points,&inst);





// init GLUT and the window
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
 glutInitWindowPosition(100,100);
 glutInitWindowSize(800,800);
 glutCreateWindow("3D ENGINE @ CG 19/20");

 glClearColor(0,0,0,0) ;
 glClear(GL_COLOR_BUFFER_BIT);

// Required callback registry
 glutDisplayFunc(renderScene);
 glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks
 glutKeyboardFunc(processKeys);
 glutSpecialFunc(processSpecialKeys);


//  OpenGL settings
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
 glutMainLoop();

 return 1;
}

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfaview = -M_PI / 4 , betaview = -M_PI / 4, step = 2.0;
float px=10,py=10,pz=10;
float dx,dy,dz;


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

void drawPlane (float comprimento, float largura){

	glBegin(GL_TRIANGLES);

	float cx = comprimento/2;
	float cz = largura/2;

	glVertex3f(cx,0.0,cz);
	glVertex3f(cx,0.0,-cz);
	glVertex3f(-cx,0.0,-cz);
	glVertex3f(cx,0.0,cz);
	glVertex3f(-cx,0.0,-cz);
	glVertex3f(-cx,0.0,cz);

	glEnd();
}

void drawBox (float comprimento, float largura, float altura, int divisoes){


	glBegin(GL_TRIANGLES);
	int i,j;


  float cx = comprimento/2;
 	float cz = largura/2;
	float cy = altura /2;

	float rx = comprimento/divisoes;
	float rz = largura/divisoes;
	float ry = altura/divisoes;

	for (i=0;i<divisoes;i++)
	for (j=0;j<divisoes;j++){
	//Face da frente
 	glVertex3f(-cx + j*rx,-cy + i*ry ,cz);
	glVertex3f(-cx + j*rx + rx,-cy + i*ry, cz);
	glVertex3f(-cx + j*rx + rx, -cy + i*ry + ry, cz);
	glVertex3f(-cx + j*rx,-cy + i*ry ,cz);
	glVertex3f(-cx + j*rx + rx, -cy + i*ry + ry, cz);
	glVertex3f(-cx + j*rx , -cy + i*ry + ry, cz);
	//Face de cima
 	glVertex3f(-cx + j*rx, cy, cz - i*rz);
	glVertex3f(-cx + j*rx + rx, cy, cz - i*rz);
	glVertex3f(-cx + j*rx + rx, cy, cz - i*rz - rz);
	glVertex3f(-cx + j*rx, cy, cz - i*rz);
	glVertex3f(-cx + j*rx + rx, cy, cz - i*rz - rz);
	glVertex3f(-cx + j*rx , cy, cz - i*rz -rz);
	//Face da trás
	glVertex3f(-cx + j*rx,-cy + i*ry ,-cz);
	glVertex3f(-cx + j*rx + rx, -cy + i*ry + ry, -cz);
	glVertex3f(-cx + j*rx + rx,-cy + i*ry, -cz);
	glVertex3f(-cx + j*rx,-cy + i*ry ,-cz);
	glVertex3f(-cx + j*rx , -cy + i*ry + ry, -cz);
	glVertex3f(-cx + j*rx + rx, -cy + i*ry + ry, -cz);
	//Face de baixo
	glVertex3f(-cx + j*rx, -cy, cz - i*rz);
	glVertex3f(-cx + j*rx + rx, -cy, cz - i*rz - rz);
	glVertex3f(-cx + j*rx + rx, -cy, cz - i*rz);
	glVertex3f(-cx + j*rx, -cy, cz - i*rz);
	glVertex3f(-cx + j*rx , -cy, cz - i*rz -rz);
	glVertex3f(-cx + j*rx + rx, -cy, cz - i*rz - rz);
	//Face da esquerda
	glVertex3f(-cx,-cy + i*ry ,cz - j*rz);
	glVertex3f(-cx,-cy + i*ry +ry , cz - j*rz - rz);
	glVertex3f(-cx,-cy + i*ry, cz - j*rz -rz);
	glVertex3f(-cx,-cy + i*ry ,cz - j*rz);
	glVertex3f(-cx,-cy + i*ry + ry , cz - j*rz);
	glVertex3f(-cx,-cy + i*ry +ry , cz - j*rz - rz);
	//Face da direita
	glVertex3f(cx,-cy + i*ry +ry , cz - j*rz - rz);
	glVertex3f(cx,-cy + i*ry ,cz - j*rz);
	glVertex3f(cx,-cy + i*ry, cz - j*rz -rz);
	glVertex3f(cx,-cy + i*ry ,cz - j*rz);
	glVertex3f(cx,-cy + i*ry +ry , cz - j*rz - rz);
	glVertex3f(cx,-cy + i*ry + ry , cz - j*rz);
	}


 	glEnd();


}


void drawSphere (float radius, int slices, int stacks){
    glBegin(GL_TRIANGLES);

    float h_stack = (M_PI/stacks); //altura de cada stack
    float a_slices = 2*M_PI / slices;
    int i, j;
    float alfa, beta = 0;

    for(j=1; j<=stacks; j++){

        alfa = 0;
        for(i=1; i<=slices; i++){
            glVertex3f((radius * sin(beta) * sin(alfa)), (radius * cos(beta)), (radius * sin(beta) * cos(alfa))); //A
            glVertex3f((radius * sin(beta + h_stack) * sin(alfa)), (radius * cos(beta + h_stack)), (radius * sin(beta + h_stack) * cos(alfa)) ); //B
            glVertex3f((radius * sin(beta + h_stack) * sin(alfa + a_slices)), (radius * cos(beta + h_stack)), (radius * sin(beta + h_stack) * cos(alfa + a_slices))); //C

            glVertex3f((radius * sin(beta) * sin(alfa)), (radius * cos(beta)), (radius * sin(beta) * cos(alfa))); //A
            glVertex3f((radius * sin(beta + h_stack) * sin(alfa + a_slices)), (radius * cos(beta + h_stack)), (radius * sin(beta + h_stack) * cos(alfa + a_slices))); //C
            glVertex3f((radius * sin(beta) * sin(alfa + a_slices)), (radius * cos(beta)), (radius * sin(beta) * cos(alfa + a_slices))); //D

        alfa = i*a_slices;
        }
        beta = j * h_stack;
    }


glEnd();

}




void drawCone(float radius, float height, int slices, int stacks){
    glBegin(GL_TRIANGLES);
    int i, j;
    float alt_stacks = height/stacks;
    float ang_slices = 2 * M_PI / slices;

    for(j=0; j<stacks; j++){
        for(i=0; i<slices; i++){

        }
    }





    glEnd();
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

	glColor3f(1.0f,1.0f,1.0f);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//drawPlane(10.0,30.0);
	//drawBox(50.0,50.0,50.0,100);
	drawSphere(5, 10, 10);
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
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}

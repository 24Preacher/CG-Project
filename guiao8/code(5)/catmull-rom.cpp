#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


float camX = 0, camY, camZ = 5;
int startX, startY, tracking = 0;

float alfaview = -M_PI / 4 , betaview = -M_PI / 4, step = 2.0;
float px=10,py=10,pz=10;
float dx,dy,dz;
int mode = GL_LINE;
int curva = 0;

int alpha = 0, beta = 0, r = 5;

#define POINT_COUNT 5
// Points that make up the loop for catmull-rom interpolation
float p[POINT_COUNT][3] = {{-10,0,-10},{-10,0,10},{10,0,10},{0,0,0},{10,0,-10}};

void buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}


float length(float *v) {

	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;

}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

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
				 case 'h':
		          if (curva == 0){
							curva = 1;
							}
							else if(curva == 1) {
							curva = 2;
							}
							else{
							curva = 0;
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


void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
		float	m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
										{ 1.0f, -2.5f,  2.0f, -0.5f},
										{-0.5f,  0.0f,  0.5f,  0.0f},
										{ 0.0f,  1.0f,  0.0f,  0.0f}};

	// hermite cubic curve
	 	float h[4][4] = {	{2.0f,  -2.0f, 1.0f,  1.0f},
										{-3.0f, 3.0f,  -2.0f, -1.0f},
										{0.0f,  0.0f,  1.0f,  0.0f},
										{1.0f,  0.0f,  0.0f,  0.0f}};

	// bezier cubic curves
		float b[4][4] = {	{-1.0f,  3.0f, -3.0f,  1.0f},
									 	{ 3.0f, -6.0f,  3.0f, 0.0f},
										{-3.0f,  3.0f,  0.0f,  0.0f},
									 	{ 1.0f,  0.0f,  0.0f,  0.0f} };


	// Compute A = M * P
	float a[4][4] = {0};


if (curva==0){
	float pX[4] = {p0[0], p1[0], p2[0], p3[0]};
	float pY[4] = {p0[1], p1[1], p2[1], p3[1]};
	float pZ[4] = {p0[2], p1[2], p2[2], p3[2]};
	multMatrixVector(*m, pX, a[0]);
	multMatrixVector(*m, pY, a[1]);
	multMatrixVector(*m, pZ, a[2]);
}
else if(curva == 1){
	float pX[4] = {p0[0], p1[0], p2[0], p3[0]};
	float pY[4] = {p0[1], p1[1], p2[1], p3[1]};
	float pZ[4] = {p0[2], p1[2], p2[2], p3[2]};
	multMatrixVector(*h, pX, a[0]);
	multMatrixVector(*h, pY, a[1]);
	multMatrixVector(*h, pZ, a[2]);
}
else if(curva == 2){
	float pX[4] = {p0[0], p1[0], p2[0], p3[0]};
	float pY[4] = {p0[1], p1[1], p2[1], p3[1]};
	float pZ[4] = {p0[2], p1[2], p2[2], p3[2]};
	multMatrixVector(*b, pX, a[0]);
	multMatrixVector(*b, pY, a[1]);
	multMatrixVector(*b, pZ, a[2]);
}

	// Compute pos = T * A
	// multiplicar vetor dos t's por A
	//slide 2
	float tt[4] = {powf(t,3), powf(t,2), t, 1};
	multMatrixVector(*a, tt, pos);



	// compute deriv = T' * A
	// td é a devivada de tt
	float td[4] = {3 * powf(t,2), 2*t, 1, 0};
	multMatrixVector(*a, td, deriv);

	// ...
}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT;
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
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


void renderCatmullRomCurve() {
    glBegin(GL_LINE_LOOP);
// draw curve using line segments with GL_LINE_LOOP
    float pos[4], deriv[4];
    int i;
    for(i=0; i<100; i++){
        //temos que ir buscar os pontos
        //'gt' tem que estar entre 0 e 1 -> i/100
        getGlobalCatmullRomPoint(i/100.0, pos, deriv);
        glVertex3f(pos[0], pos[1], pos[2]);
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

	static float t = 0;
    float pos[4], deriv[4], z[4], y[4] = {0,1,0}, m[16];
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(px, py, pz,
						px + dx, py + dy, pz + dz,
						0.0f,1.0f,0.0f);
		glColor3f(1,0,0);
	renderCatmullRomCurve();

	// apply transformations here
	// ...
    getGlobalCatmullRomPoint(t,pos, deriv);

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


    normalize(deriv);

    cross(deriv, y, z );
    normalize(z);
    cross(z, deriv, y);
    normalize(y);

    buildRotMatrix(deriv, y, z, m);
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glMultMatrixf(m);
		glColor3f(0.5f,1.0f,0.5f);
		glPushMatrix();
		glRotatef(90.0,0,1,0);
	glutWireCone(1,2,10,10);
    glPopMatrix();
		glColor3f(1,1,1);
		glutWireTeapot(1);
		glPopMatrix();

	glutSwapBuffers();
	t+=0.001;
}


void processMouseButtons(int button, int state, int xx, int yy)
{
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy)
{
	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {

		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux *							     sin(betaAux * 3.14 / 180.0);
}


int main(int argc, char **argv) {

// inicialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

// callback registration
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// mouse callbacks
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}


#include "headers/catmullRom.h"



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

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}


void getCatmullRomPoint(float t, std::vector<Ponto*> pontos, float *pos, float *deriv, int *indices){
	// [t^3, t^2, t, 1]
	float tt[4] = {powf(t,3), powf(t,2), t, 1};
	// [3*t^2, 2*t, 1, 0] -> derivada
	float td[4] = {3 * powf(t,2), 2*t, 1, 0};



	// catmull-rom matrix
		float	m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
										{ 1.0f, -2.5f,  2.0f, -0.5f},
										{-0.5f,  0.0f,  0.5f,  0.0f},
										{ 0.0f,  1.0f,  0.0f,  0.0f}};


//precisamos de 4 pontos
 Ponto* p0 = pontos[indices[0]];
 Ponto* p1 = pontos[indices[1]];
 Ponto* p2 = pontos[indices[2]];
 Ponto* p3 = pontos[indices[3]];



	// Compute A = M * P
	float a[4] = {0};
	multMatrixVector(*m, tt, a);

	//derivada
	float d[4] = {0};
	multMatrixVector(*m, td, d);



	// Compute pos[i] = T * A
	pos[0] = a[0]*p0->x +a[1]*p1->x + a[2]*p2->x + a[3]*p3->x;
	pos[1] = a[0]*p0->y +a[1]*p1->y + a[2]*p2->y + a[3]*p3->y;
	pos[2] = a[0]*p0->z +a[1]*p1->z + a[2]*p2->z + a[3]*p3->z;


	// compute deriv[i] = T' * A

	pos[0] = d[0]*p0->x +d[1]*p1->x + d[2]*p2->x + d[3]*p3->x;
	pos[1] = d[0]*p0->y +d[1]*p1->y + d[2]*p2->y + d[3]*p3->y;
	pos[2] = d[0]*p0->z +d[1]*p1->z + d[2]*p2->z + d[3]*p3->z;

}



//To get the points for the full curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, std::vector<Ponto*> pontos){

	int n = pontos.size();
	float t = gt * n; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];

	indices[0] = (index + n-1) % n;
	indices[1] = (indices[0]+1) % n;
	indices[2] = (indices[1]+1) % n;
	indices[3] = (indices[2]+1) % n;

	getCatmullRomPoint(t, pontos, pos, deriv, indices);

}



void renderCatmullRomCurve(std::vector<Ponto*> pontos){

	glBegin(GL_LINE_LOOP);
// draw curve using line segments with GL_LINE_LOOP
	float pos[3], deriv[3];
	float t;

	std::vector<Ponto*> pts;
	for(t = 0; t < 1; t+=0.01){
		getGlobalCatmullRomPoint(t,pos,deriv,pontos);
    Ponto *ponto = new Ponto();
    (*ponto).x = pos[0];
    (*ponto).y = pos[1];
    (*ponto).z = pos[2];
		pts.push_back(ponto);
	}

	int n = pts.size();
	float p[3];
	int i;
	for(i=0; i<n; i++){
			//temos que ir buscar os pontos
			p[0] = pts[i]->x;
			p[1] = pts[i]->y;
			p[2] = pts[i]->z;
			glVertex3f(p[0],p[1],p[2]);
	}

	glEnd();


}

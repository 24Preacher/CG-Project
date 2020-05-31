#include "headers/utils.h"
using namespace std;

void printPoint (Ponto*p){
	printf("(%f,%f,%f)\n",p->x,p->y,p->z);
}


bool pertenceP(Ponto*p,vector<Ponto*>*pontos){
	int i;
	bool flag = false;
	for(i=0;i<pontos->size() && !flag;i++){
		 if(equalsP(p,(pontos->at(i)))){
			 flag=true;
		 }
	}
	return flag;
}

void meanP(vector<Ponto*>* pontos, Ponto* res){
	float x=0,y=0,z=0;
	int i=0;
	for(i=0;i<pontos->size();i++){
		x+= pontos->at(i)->x;
		y+= pontos->at(i)->y;
		z+= pontos->at(i)->z;

	}
	res->x = x/(i+1);
	res->y = y/(i+1);
	res->z = z/(i+1);

}

void normalizeP(Ponto* res){
float aux[3];
aux[0]=res->x;
aux[1]=res->y;
aux[2]=res->z;
normalize(aux);
res->x=aux[0];
res->y=aux[1];
res->z=aux[2];
}
void copyP(Ponto*fts,Ponto*snd){
	snd->x=fts->x;
	snd->y=fts->y;
	snd->z=fts->z;
}


bool equalsP(Ponto*fts,Ponto*snd){
	return ((fts->x == snd->x) && (fts->y == snd->y) && (fts->z == snd->z));
}

void crossP(Ponto* frst,Ponto* sncd,Ponto* res){
	float a[3];
	float b[3];
	float aux[3];
	aux[0]=0;
	aux[1]=0;
	aux[2]=0;
	a[0]=frst->x;
	a[1]=frst->y;
	a[2]=frst->z;
	b[0]=sncd->x;
	b[1]=sncd->y;
	b[2]=sncd->z;
	cross(a,b,aux);
	res->x = aux[0];
	res->y = aux[1];
	res->z = aux[2];
}

void diffP(Ponto* frts,Ponto* sncd,Ponto* res){
	res->x = (frts->x) - (sncd ->x);
	res->y = (frts->y) - (sncd ->y);
	res->z = (frts->z) - (sncd ->z);
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
void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

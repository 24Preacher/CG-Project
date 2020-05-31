#ifndef utils_h
#define utils_h


#include <vector>
#include <math.h>
#include <stdio.h>

typedef struct {
  float x;
  float y;
  float z;
} Ponto;

void printPoint (Ponto*);
bool pertenceP(Ponto*,std::vector<Ponto*>*);
void meanP(std::vector<Ponto*>*,Ponto*);
void copyP(Ponto*,Ponto*);
bool equalsP(Ponto*,Ponto*);
void diffP(Ponto*, Ponto*,Ponto*);
void crossP (Ponto*,Ponto*,Ponto*);
void normalizeP(Ponto*);
void cross(float*, float*, float*);
void normalize(float*);
void multMatrixVector(float *, float *, float *);
#endif

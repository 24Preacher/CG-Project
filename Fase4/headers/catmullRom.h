#ifndef catmullrom_h
#define catmullrom_h
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "instruction.h"
#include "utils.h"
#include <vector>
#include <math.h>





void getCatmullRomPoint(float, std::vector<Ponto*> , float*, float*, int*);
void getGlobalCatmullRomPoint(float, float*, float*, std::vector<Ponto*>);
void renderCatmullRomCurve(std::vector<Ponto*>);

#endif

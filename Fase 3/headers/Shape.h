#include <stdio.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifndef SHAPE
#define SHAPE


#include <vector>
#include "parser.h"

class Shape {

private:
    std::vector<Ponto*> Pontos;
    GLuint buffer;

public:
    void inserePonto(Ponto*);
    Ponto* getPoint(int);
    int getSize();
    void vbo();
    void draw();

};

#endif

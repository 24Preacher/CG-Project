#ifndef shape_h
#define shape_h

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "instruction.h"

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
    void print(const char*);
};

typedef std::vector<Shape*> shapeStruct;
typedef std::vector<shapeStruct> shapeMatrix;
typedef std::vector<Instruction> instructions;
typedef std::vector<instructions> instructionsMatrix;


#endif //shape_h

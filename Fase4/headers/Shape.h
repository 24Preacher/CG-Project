#ifndef shape_h
#define shape_h

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#include "/usr/local/include/IL/il.h"
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#endif

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "utils.h"
#include "instruction.h"
#include "material.h"

using namespace std;

class Shape {

private:
    std::vector<Material*> materials;
    GLuint buffer[3];
    int n_vertices;
    unsigned int textura;
    bool has_texture;


public:
    void addMaterial(Material*);
    Shape (vector<Ponto*>*,vector<Ponto*>*,vector<Ponto*>*,const char*);
    int getNVertices();
    void loadImage(const char*);
    void draw();
    void cleanVector(vector<Ponto*> * );
    void print();
};

typedef std::vector<Shape*> shapeStruct;
typedef std::vector<shapeStruct> shapeMatrix;
typedef std::vector<Instruction> instructions;
typedef std::vector<instructions> instructionsMatrix;


#endif //shape_h

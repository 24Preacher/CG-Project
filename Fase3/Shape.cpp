#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <cstdlib>

#include "headers/Shape.h"

using namespace std;


void Shape::inserePonto(Ponto* p){
    this->Pontos.push_back(p);
}


Ponto* Shape::getPoint(int i) {
    return this->Pontos.at(i);
}

int Shape::getSize(){
    return this->Pontos.size();
}

void Shape::vbo() {
    float *vertex = (float *) malloc(sizeof(float) * 3 * this->Pontos.size());
    int index = 0;
    for (int i = 0; i < this->Pontos.size(); i++) {
        vertex[index] = this->Pontos[i]->x;
        vertex[index + 1] = this->Pontos[i]->y;
        vertex[index + 2] = this->Pontos[i]->z;
        index += 3;
    }

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * index, vertex, GL_STATIC_DRAW);

    free(vertex);
}


void Shape::draw(){
        glBindBuffer(GL_ARRAY_BUFFER,buffer);
        glVertexPointer(3,GL_FLOAT,0, 0);
        glDrawArrays(GL_TRIANGLES,0,getSize()*3);
}

void Shape::print(const char* file){
  int i;

  ofstream f (file,ios::out| ios::trunc );
  if( f.is_open() ) {
    for(i=0;i<this->Pontos.size();i++){
     f << this->Pontos.at(i)->x << ' '
       << this->Pontos.at(i)->y << ' '
       << this->Pontos.at(i)->z << '\n';

    }
  }
    f.close();
}

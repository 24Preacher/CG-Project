#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/light.h"


int Light::getType() {
  return type;
}

float* Light::getPosicao(){
    return posicao;
}


Light::Light(int type, float *pos, float * dir ,float *adds, float* ambient, float* diffuse, float* specular) {

    this->type = type;

    this->posicao[0] = pos[0];
    this->posicao[1] = pos[1];
    this->posicao[2] = pos[2];
    this->posicao[3] = pos[3];

    this->direcao[0] = dir[0];
    this->direcao[1] = dir[1];
    this->direcao[2] = dir[2];

    this->adds[0] = adds[0];
    this->adds[1] = adds[1];
    this->adds[2] = adds[2];

    this->ambient[0] = ambient[0];
    this->ambient[1] = ambient[1];
    this->ambient[2] = ambient[2];

    this->diffuse[0] = diffuse[0];
    this->diffuse[1] = diffuse[1];
    this->diffuse[2] = diffuse[2];

    this->specular[0] = specular[0];
    this->specular[1] = specular[1];
    this->specular[2] = specular[2];

}


void Light::draw(){

  GLfloat ambient[4] = {0.2, 0.05, 0.05, 1.0};
  GLfloat diffuse[4] = {0.8, 0.2, 0.2, 1.0};
  GLfloat specular[4] = {1.0, 1.0, 1.0, 1.0};
  GLfloat emission[4] = {0.0, 0.0, 0.0, 1.0};
	GLfloat pos[4] = {posicao[0], posicao[1] , posicao[2], posicao[3]};


  if (type == 3 ) {

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcao);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, adds[0]); // [0,90] ou 180
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, adds[1]); // [0,128]
    glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION, adds[2]); //de 0 a 1

  }

  else{
    glLightfv(GL_LIGHT0, GL_POSITION, pos );
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular );
  }
}

void Light::print(){

     std::cout << this->type << " "
               << this->posicao << " "
               << this->direcao <<  " "
               << this->adds <<  " "
               << this->ambient <<  " "
               << this->diffuse <<  " "
               << this->specular << std::endl;

}

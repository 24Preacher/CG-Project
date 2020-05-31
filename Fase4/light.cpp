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

void Light::addPos(float* posicao ){

  for( int i = 0; i < 4; i++ )
    this->posicao[i] = posicao[i];

}

void Light::addAmb(float* ambient ){

  for( int i = 0; i < 3; i++ )
    this->ambient[i] = ambient[i];
}

void Light::addSpec (float* specular ){

  for( int i = 0; i < 3; i++ )
    this->specular[i] = specular[i];

}

void Light::addDiff(float* diffuse ){

  for( int i = 0; i < 3; i++ )
    this->diffuse[i] = diffuse[i];

}

void Light::addAdds(float* adds ){

  for( int i = 0; i < 3; i++ )
    this->adds[i] = adds[i];

}

void Light::addDir(float* direcao ){

  for( int i = 0; i < 3; i++ )
    this->direcao[i] = direcao[i];

}


Light::Light( int type ) {

    this->type = type;

    if( type == 1 ){

      this->posicao[0] = 1.0;
      this->posicao[1] = 1.0;
      this->posicao[2] = 1.0;
      this->posicao[3] = 1.0;

    }else if (type == 2 ){

      this->posicao[0] = 1.0;
      this->posicao[1] = 1.0;
      this->posicao[2] = 1.0;
      this->posicao[3] = 0.0;

    }else if( type == 3 ){

      this->posicao[0] = 1.0;
      this->posicao[1] = 1.0;
      this->posicao[2] = 1.0;
      this->posicao[3] = 1.0;

      this->direcao[0] = 0;
      this->direcao[1] = 0;
      this->direcao[2] = -1;
    }

    this->ambient[0] = 0.2;
    this->ambient[1] = 0.2;
    this->ambient[2] = 0.2;

    this->diffuse[0] = 1;
    this->diffuse[1] = 1;
    this->diffuse[2] = 1;

    this->specular[0] = 1;
    this->specular[1] = 1;
    this->specular[2] = 1;

    this->adds[0] = 180; //cutoff
    this->adds[1] = 0; //exponent
    this->adds[2] = 1; //attenuation

}


void Light::draw(){


	GLfloat pos[4] = {posicao[0], posicao[1] , posicao[2], posicao[3]};


  if (type == 3 ) {

    glLightfv(GL_LIGHT0, GL_POSITION, pos );
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

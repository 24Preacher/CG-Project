
#include "headers/material.h"


Material::Material(int type, float shiness, float* color){
    this -> type = type;
    this -> shininess = shininess;
    this -> color[0] = color[0];
    this -> color[1] = color[1];
    this -> color[2] = color[2];
    this -> color[3] = 1.0f;
}

void Material::draw(){
  if(type == 0){
    glMaterialfv(GL_FRONT,GL_SPECULAR,color);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);
  }else if (type == 1){
    glMaterialfv(GL_FRONT,GL_EMISSION,color);
  }else if (type == 2){
    glMaterialfv(GL_FRONT,GL_DIFFUSE,color);
  }else if (type == 3){
    glMaterialfv(GL_FRONT,GL_AMBIENT,color);
  }
}

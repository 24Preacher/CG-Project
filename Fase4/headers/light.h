#ifndef light_h
#define light_h


#include <cmath>
#include <cstring>
#include <iostream>



class Light{

  private:

    int type; // 1 Point, 2 Directional, 3 Spot
    float posicao[4]; // Sendo um point descreve a posição da luz, sendo directional descrever a diração posicao[3] == 0.0 -> direcional || posicao[3] == 1.0 -> pontual
    float direcao[3]; // 0 0 -1 default value
    float adds[3]; // [0] -> spot cutoff [0,90] [1] -> spot exponent[0,128] [2] -> GL_QUADRATIC_ATTENUATION {0,1}
    float ambient[3];
    float diffuse[3];
    float specular[3];

  public:

    float* getPosicao();
    int getType();
    Light( int type, float* posicao , float* dir, float* adds, float* ambient, float* diffuse, float* specular);
    void draw();
    void print();

};

#endif

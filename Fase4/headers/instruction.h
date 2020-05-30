#ifndef instruction_h
#define instruction_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include "utils.h"

typedef struct {
  float x;
  float y;
  float z;
} Ponto;

class Instruction {

private:
    char instruction;
    float time;
    float angle;
    float x, y, z;
    std::vector<Ponto*> pontos;


public:
    Instruction (char, float ,float, float, float, float);

    char getInstruction ();

    int getTime();

    float getAngle ();

    float getX ();

    float getY ();

    float getZ ();

    void print();

    std::vector<Ponto*> getPontos();

    void addPonto(Ponto*);

    void setInstruction (char);

    void setAngle (float);

    void setX (float);

    void setY (float);

    void setZ (float);


};


#endif

#ifndef instruction_h
#define instruction_h

#include <stdio.h>
#include <iostream>

class Instruction {
    char instruction;
    float angle;
    float x, y, z;
public:
    Instruction (char,float, float, float, float);

    char getInstruction ();

    float getAngle ();

    float getX ();

    float getY ();

    float getZ ();

    void print();

    void setInstruction (char);

    void setAngle (float);

    void setX (float);

    void setY (float);

    void setZ (float);

};

#endif

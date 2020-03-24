#include "instruction.h"

char Instruction::getInstruction () {
        return this->instruction;
    }

float Instruction::getAngle () {
        return this->angle;
    }

    float Instruction::getX () {
        return this->x;
    }

    float Instruction::getY () {
        return this->y;
    }
    float Instruction::getZ () {
        return this->z;
    }

    void Instruction::setInstruction (char instruction) {
        this->instruction = instruction;
    }

    void Instruction::setAngle (float angle) {
        this->angle = angle;
    }

    void Instruction::setX (float x) {
        this->x = x;
    }

    void Instruction::setY (float y) {
        this->y = y;
    }

    void Instruction::setZ (float z) {
        this->z = z;
    }

    void Instruction::print(){
         std::cout << this->instruction << " "
                   << this->angle <<  " "
                   << this->x <<  " "
                   << this->y <<  " "
                   << this->z << std::endl;
    }

Instruction::Instruction(char instruction, float angle, float x, float y, float z) {
    this->instruction = instruction;
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
}

#include "headers/instruction.h"

char Instruction::getInstruction () {
        return this->instruction;
    }

  int Instruction::getTime(){
    return this->time;
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

    std::vector<Ponto*> Instruction::getPontos(){
      return this->pontos;
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

    void Instruction::addPonto(Ponto* p){
      this->pontos.push_back(p);
    }

    void Instruction::print(){
         std::cout << this->instruction << " "
                   << this->time << " "
                   << this->angle <<  " "
                   << this->x <<  " "
                   << this->y <<  " "
                   << this->z << std::endl;
            int i ;
            for(i=0;i<this->pontos.size();i++){
              std::cout << "(" << this->pontos.at(i)->x << ","
                        << this->pontos.at(i)->y << ","
                        << this->pontos.at(i)->z <<  ")" << std::endl;
            }

    }

Instruction::Instruction(char instruction, float time, float angle, float x, float y, float z) {
    this->instruction = instruction;
    this->time = time;
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
}

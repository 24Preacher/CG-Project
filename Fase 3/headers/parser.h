#ifndef parser_h
#define parser_h

#include "tinyxml2.h"
#include "instruction.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sstream>
#include <vector>
using namespace std;
using namespace tinyxml2;


typedef struct {
  float x;
  float y;
  float z;
} Ponto;

typedef std::vector<Ponto> pointsStruct;
typedef std::vector<pointsStruct> pointsMatrix;
typedef std::vector<Instruction> instructions;
typedef std::vector<instructions> instructionsMatrix;


void parseGroup(XMLNode* group, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i);
void parseModels (XMLNode* pNode, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i);
vector<string> split(const string& s, char delimiter);
int loadDoc(char* path,  pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix );

#endif

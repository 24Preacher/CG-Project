#ifndef parser_h
#define parser_h
#include <GL/gl.h>

#include "tinyxml2.h"
#include "instruction.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sstream>
#include <vector>
#include "instruction.h"

using namespace std;
using namespace tinyxml2;




void parseGroup(XMLNode* group, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i);
void parseModels (XMLNode* pNode, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i);
void parseTranslation (XMLNode* pNode, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i);
vector<string> split(const string& s, char delimiter);
int loadDoc(char* path,  pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix );




#endif

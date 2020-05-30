#ifndef parser_h
#define parser_h

#include "tinyxml2.h"
#include "instruction.h"
#include "Shape.h"
#include "utils.h"
#include "light.h"

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sstream>
#include <vector>

using namespace std;
using namespace tinyxml2;




void parseGroup(XMLNode* , shapeMatrix* , instructionsMatrix* , int* );
void parseModels (XMLNode* , shapeMatrix* , instructionsMatrix* , int* );
void parseTranslation (XMLNode* , shapeMatrix* , instructionsMatrix* , int* );
vector<string> split(const string& , char );
int loadDoc(char* ,  shapeMatrix* , instructionsMatrix* , vector<Light*> * );
void parseLight(XMLNode* , vector<Light*>* , instructionsMatrix* , int* );




#endif

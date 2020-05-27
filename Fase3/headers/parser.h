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




void parseGroup(XMLNode* , pointsMatrix* , instructionsMatrix* , int* );
void parseModels (XMLNode* , pointsMatrix* , instructionsMatrix* , int* );
void parseTranslation (XMLNode* , pointsMatrix* , instructionsMatrix* , int* );
vector<string> split(const string& , char );
int loadDoc(char* ,  pointsMatrix* , instructionsMatrix*  );




#endif

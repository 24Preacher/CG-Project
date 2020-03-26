#include "headers/parser.h"
#include "headers/tinyxml2.h"

using namespace std;
using namespace tinyxml2;



vector<string> split(const string& s, char delimiter)
{
    std::vector<string> tokens;
    std::string token;
    std::istringstream ss(s);
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}


void parseGroup(XMLNode* group, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i){
  XMLNode* pParm;
  pParm = group -> FirstChildElement();
  float angle, scale, x, y, z;
  int j;
  while(pParm)
  {
        if ((strcmp (pParm -> Value(), "translate")) == 0){
          if (pParm -> ToElement() -> Attribute("X")){
            x = stof(pParm -> ToElement() -> Attribute("X"));
          }
          else{
            x=0;
          }

          if (pParm -> ToElement() -> Attribute("Y")){
            y = stof(pParm -> ToElement() -> Attribute("Y"));
          }
          else{
            y=0;
          }

          if (pParm -> ToElement() -> Attribute("Z")){
            z = stof(pParm -> ToElement() -> Attribute("Z"));
          }
          else{
            z=0;
          }

          Instruction in ('t',0,x,y,z);
          (*instructionsMatrix)[*i].push_back(in);
        }

        else if ((strcmp (pParm -> Value(), "rotate")) == 0){
          if (pParm -> ToElement() -> Attribute("angle")){
            angle = stof(pParm -> ToElement() -> Attribute("angle"));
          }
          else{
            angle=0;
          }
          if (pParm -> ToElement() -> Attribute("axisX")){
            x = stof(pParm -> ToElement() -> Attribute("axisX"));
          }
          else{
            x=0;
          }
          if (pParm -> ToElement() -> Attribute("axisY")){
            y = stof(pParm -> ToElement() -> Attribute("axisY"));
          }
          else{
            y=0;
          }
          if (pParm -> ToElement() -> Attribute("axisZ")){
            z = stof(pParm -> ToElement() -> Attribute("axisZ"));
          }
          else{
            z=0;
          }
          Instruction in ('r',angle,x,y,z);
          (*instructionsMatrix)[*i].push_back(in);
        }
        else if ((strcmp (pParm -> Value(), "scale")) == 0){
          if (pParm -> ToElement() -> Attribute("X")){
            x = stof(pParm -> ToElement() -> Attribute("X"));
          }
          else{
            x=0;
          }
          if (pParm -> ToElement() -> Attribute("Y")){
            y = stof(pParm -> ToElement() -> Attribute("Y"));
          }
          else{
            y=0;
          }
          if (pParm -> ToElement() -> Attribute("Z")){
            z = stof(pParm -> ToElement() -> Attribute("Z"));
          }
          else{
            z=0;
          }
          Instruction in ('s',0,x,y,z);
          (*instructionsMatrix)[*i].push_back(in);
        }
        else if ((strcmp (pParm -> Value(), "color")) == 0){
          if (pParm -> ToElement() -> Attribute("Red")){
            x = stof(pParm -> ToElement() -> Attribute("Red"));
          }
          else{
            x=0;
          }
          if (pParm -> ToElement() -> Attribute("Green")){
            y = stof(pParm -> ToElement() -> Attribute("Green"));
          }
          else{
            y=0;
          }
          if (pParm -> ToElement() -> Attribute("Blue")){
            z = stof(pParm -> ToElement() -> Attribute("Blue"));
          }
          else{
            z=0;
          }
          Instruction in ('c',0,x/255,y/255,z/255);
          (*instructionsMatrix)[*i].push_back(in);
        }
        else if ((strcmp (pParm -> Value(), "group")) == 0){
          instructions insts; // vector de instrucoes vazio
          pointsStruct pontos; // vector de pontos vazio
          (*instructionsMatrix).push_back(insts);
          (*pointsMatrix).push_back(pontos);
          for (j=0;j<instructionsMatrix[*i].size();j++){
            instructionsMatrix[*i+1] = instructionsMatrix[*i];
            }
        *i++;

          parseGroup(pParm, pointsMatrix, instructionsMatrix, i);
        }
        else if ((strcmp (pParm -> Value(), "models")) == 0){
          parseModels(pParm, pointsMatrix, instructionsMatrix, i);
        }
      pParm = pParm->NextSiblingElement();
  }
}

void parseModels (XMLNode* pNode, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i){
  XMLNode* pParm;
  pParm = pNode -> FirstChildElement();
  int a=0, n;
  std::string file;
  std::vector<std::string> files;
  while(pParm)
  {
      file = pParm-> ToElement() -> Attribute("file");
      files.push_back(file);
      pParm = pParm->NextSiblingElement();
      a++;
  }
  for(n=0;n<files.size();n++){
    ifstream infile;
    infile.open(files[n]);
    if(infile.is_open()){
      std::string line;

    while(std::getline(infile,line)){

      std::vector<string> tokens;
      tokens = split(line, ' ');

      Ponto *p = new Ponto();
      (*p).x = stof(tokens[0],nullptr);
      (*p).y = stof(tokens[1],nullptr);
      (*p).z = stof(tokens[2],nullptr);
      (*pointsMatrix)[*i].push_back(*p);
    }
  }
    infile.close();
 }
}


int loadDoc(char* path,  pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix ) {
    XMLDocument doc;
    tinyxml2::XMLError flag = doc.LoadFile(path);

    if(!flag){
      XMLNode *scene = doc.FirstChild();
      if(scene == nullptr){
      return XML_ERROR_FILE_READ_ERROR;
    }

    XMLNode *group = scene -> FirstChildElement("group");
    int i = 0;
    if(group == nullptr) return XML_ERROR_PARSING_ELEMENT;
    while(group){
    instructions insts; // vector de instrucoes vazio
    pointsStruct pontos; // vector de pontos vazio
    (*instructionsMatrix).push_back(insts);
    (*pointsMatrix).push_back(pontos);
    parseGroup(group,pointsMatrix,instructionsMatrix,&i);
    i++;
    group = group -> NextSiblingElement("group");
  }
  return 1;
}
return 0;
}

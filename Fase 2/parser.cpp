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


void parseGroup(XMLNode* group, pointsStruct* pointsStruct, instructionsMatrix* instructionsMatrix, int* i){
  XMLNode* pParm;
  pParm = group -> FirstChildElement();
  float angle, scale, x, y, z;
  int a = *i;
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
          instructionsMatrix[a].push_back(in);
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
          instructionsMatrix[a].push_back(in);
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
          instructionsMatrix[a].push_back(in);
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
          Instruction in ('c',0,x,y,z);
          instructionsMatrix[a].push_back(in);
        }
        else if ((strcmp (pParm -> Value(), "group")) == 0){
          a++;
          parseGroup(pParm, pointsStruct, instructionsMatrix, &a);
        }
        else if ((strcmp (pParm -> Value(), "models")) == 0){
          parseModels(pParm, pointsStruct, instructionsMatrix, &a);
        }
      pParm = pParm->NextSiblingElement();
  }
}

void parseModels (XMLNode* pNode, pointsStruct* pointsStruct, instructionsMatrix* instructionsMatrix, int* i){
  XMLElement *pParm;
  pParm = pNode -> FirstChildElement();
  int a=0;
  std::string file;
  std::vector<std::string> files;
  while(pParm)
  {
      file = pParm->Attribute("file");
      files.push_back(file);
      pParm = pParm->NextSiblingElement();
      a++;
  }


}

vector<string> getfiles (char* path){

    std::vector<string> files;
    XMLDocument doc;
    tinyxml2::XMLError flag = doc.LoadFile(path);
if(!flag){
    XMLElement *pRoot, *pParm;
    pRoot = doc.FirstChildElement();
    if(pRoot)
    {
        pParm = pRoot->FirstChildElement();
        int i = 0; // for sorting the entries
        std::string file;
        while(pParm)
        {
            file = pParm->Attribute("file");
            files.push_back(file);
            pParm = pParm->NextSiblingElement();
            i++;
        }
        int it;

    }


    }
    return files;
}


std::vector<Ponto> getpontos(char* path){
  int i;
  vector<string> files = getfiles(path);
  std::vector<Ponto> pontos;
  for(i=0;i<files.size();i++){
    ifstream infile;
    infile.open(files[i]);
    if(infile.is_open()){
      std::string line;

    while(std::getline(infile,line)){

      std::vector<string> tokens;
      tokens = split(line, ' ');

      Ponto *p = new Ponto();
      (*p).x = stof(tokens[0],nullptr);
      (*p).y = stof(tokens[1],nullptr);
      (*p).z = stof(tokens[2],nullptr);
      pontos.push_back(*p);
    }
  }
    infile.close();
    }
    return pontos;

}

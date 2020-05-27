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
  float angle, scale, x, y, z,time;
  int num = *i;
  printf("5\n" );


  while(pParm)
  {
        if ((strcmp (pParm -> Value(), "translate")) == 0){
          parseTranslation(pParm,pointsMatrix,instructionsMatrix,i);
        }

        else if ((strcmp (pParm -> Value(), "rotate")) == 0){
          if (pParm -> ToElement() -> Attribute("angle")){
            angle = stof(pParm -> ToElement() -> Attribute("angle"));
          }
          else{
            angle=0;
          }
          if (pParm -> ToElement() -> Attribute("time")){
            time = stof(pParm -> ToElement() -> Attribute("time"));
          }
          else{
            time=0;
          }
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
          Instruction in ('r',time,angle,x,y,z);
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
          Instruction in ('s',0,0,x,y,z);
          (*instructionsMatrix)[*i].push_back(in);
        }
        else if ((strcmp (pParm -> Value(), "colour")) == 0){
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
          Instruction in ('c',0,0,x/255,y/255,z/255);
          (*instructionsMatrix)[*i].push_back(in);
        }
        else if ((strcmp (pParm -> Value(), "group")) == 0){
          instructions insts; // vector de instrucoes vazio
            unsigned int j;
            for (j=0;j<(*instructionsMatrix)[num].size();j++){
              insts.push_back((*instructionsMatrix)[num][j]);
            }

          (*instructionsMatrix).push_back(insts);
          pointsStruct pontos; // vector de pontos vazio
          (*pointsMatrix).push_back(pontos);
          (*i)++;
          parseGroup(pParm, pointsMatrix, instructionsMatrix, i);
        }
        else if ((strcmp (pParm -> Value(), "models")) == 0){
          parseModels(pParm, pointsMatrix, instructionsMatrix, i);
        }
      pParm = pParm->NextSiblingElement();
  }
}


void parseTranslation (XMLNode* pNode, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i){
  XMLNode* pParm;
  float x,y,z,time;

  if (pNode -> ToElement() -> Attribute("time")){
    time = stof(pNode -> ToElement() -> Attribute("time"));
    pParm = pNode -> FirstChildElement();
    Instruction in ('t',time,0,0,0,0);
    while(pParm)
    {
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

      Ponto *p = new Ponto();
      (*p).x = x;
      (*p).y = y;
      (*p).z = z;

        in.addPonto(p);

        pParm = pParm->NextSiblingElement();
    }
      (*instructionsMatrix)[*i].push_back(in);

  }
  else{
    time=0;
    if (pNode -> ToElement() -> Attribute("X")){
      x = stof(pNode -> ToElement() -> Attribute("X"));
    }
    else{
      x=0;
    }

    if (pNode -> ToElement() -> Attribute("Y")){
      y = stof(pNode -> ToElement() -> Attribute("Y"));
    }
    else{
      y=0;
    }

    if (pNode -> ToElement() -> Attribute("Z")){
      z = stof(pNode -> ToElement() -> Attribute("Z"));
    }
    else{
      z=0;
    }

    Instruction in ('t',time,0,x,y,z);
    (*instructionsMatrix)[*i].push_back(in);
  }

}

void parseModels (XMLNode* pNode, pointsMatrix* pointsMatrix, instructionsMatrix* instructionsMatrix, int* i){
  XMLNode* pParm;
  pParm = pNode -> FirstChildElement();
  int n;
  std::string file;
  std::vector<std::string> files;
  printf("9\n" );

  while(pParm)
  {
      file = pParm-> ToElement() -> Attribute("file");
      files.push_back(file);
      pParm = pParm->NextSiblingElement();
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
      (*pointsMatrix)[*i].push_back(p);
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

  int linhas =0, colunas =0;

  for(linhas=0;linhas<(*instructionsMatrix).size();linhas++)
    for(colunas=0;colunas<(*instructionsMatrix)[linhas].size();colunas++)
          (*instructionsMatrix)[linhas][colunas].print();


  return 1;
}
return 0;
}

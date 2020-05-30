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


void parseGroup(XMLNode* group, shapeMatrix* shape, instructionsMatrix* instructionsMatrix, int* i){
  XMLNode* pParm;
  pParm = group -> FirstChildElement();
  float angle, scale, x, y, z,time;
  int num = *i;
  while(pParm)
  {

        if ((strcmp (pParm -> Value(), "translate")) == 0){
          parseTranslation(pParm,shape,instructionsMatrix,i);
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
          shapeStruct pontos; // vector de pontos vazio
          (*shape).push_back(pontos);
          (*i)++;
          parseGroup(pParm, shape, instructionsMatrix, i);
        }
        else if ((strcmp (pParm -> Value(), "models")) == 0){
          parseModels(pParm, shape, instructionsMatrix, i);
        }
      pParm = pParm->NextSiblingElement();
  }
}


void parseTranslation (XMLNode* pNode, shapeMatrix* shape, instructionsMatrix* instructionsMatrix, int* i){
  XMLNode* pParm;
  float x,y,z,time;

  if (pNode -> ToElement() -> Attribute("time")){
    time = stof(pNode -> ToElement() -> Attribute("time"));
    pParm = pNode -> FirstChildElement();
    Instruction in ('T',time,0,0,0,0);
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

void parseModels (XMLNode* pNode, shapeMatrix* shape, instructionsMatrix* instructionsMatrix, int* i){
  XMLNode* pParm;
  pParm = pNode -> FirstChildElement();
  int n;
  std::string file;
  std::string texturefile;
  float colorR = 0.0,colorG = 0.0,colorB = 0.0;
  float cores[4];
  float shininess;
  Shape* figura;

  while(pParm)
  {
      std::vector<Ponto*> pontos;
      std::vector<Ponto*> normals;
      std::vector<Ponto*> textcoords;
      if (pParm-> ToElement() -> Attribute("file")){
      file = pParm-> ToElement() -> Attribute("file");

      ifstream infile;
      infile.open(file);
      if(infile.is_open()){
        std::string line;
        int a=0;
      while(std::getline(infile,line)){

        std::vector<string> tokens;
        tokens = split(line, ' ');

        // printf("%d %f %f %f %f %f %f %f %f\n", a,
        // stof(tokens[0]),
        // stof(tokens[1]),
        // stof(tokens[2]),
        // stof(tokens[3]),
        // stof(tokens[4]),
        // stof(tokens[5]),
        // stof(tokens[6]),
        // stof(tokens[7]) );
        Ponto *p = new Ponto();
        (*p).x = stof(tokens[0],nullptr);
        (*p).y = stof(tokens[1],nullptr);
        (*p).z = stof(tokens[2],nullptr);
        pontos.push_back(p);
        Ponto *p1 = new Ponto();
        (*p1).x = stof(tokens[3],nullptr);
        (*p1).y = stof(tokens[4],nullptr);
        (*p1).z = stof(tokens[5],nullptr);
        normals.push_back(p1);
        Ponto *p2 = new Ponto();
        (*p2).x = stof(tokens[6],nullptr);
        (*p2).y = stof(tokens[7],nullptr);
        (*p2).z = 0.0;
        textcoords.push_back(p2);
        a++;
      }
      infile.close();
        const char* textura = pParm-> ToElement() -> Attribute("texture");
        cout << textura << endl;
        cout.flush();

       figura = new Shape(&pontos,&normals,&textcoords,textura);
       printf("numero de vertices da figura: %d\n",figura->getNVertices());
       cout << figura->getNVertices() << endl;
       cout.flush();
       figura -> print();
      if (pParm-> ToElement() -> Attribute("diffR")){

      if (pParm-> ToElement() -> Attribute("diffR")){
        colorR = stof(pNode -> ToElement() -> Attribute("diffR"));
      }
      if (pParm-> ToElement() -> Attribute("diffG")){
        colorG = stof(pNode -> ToElement() -> Attribute("diffG"));
      }
      if (pParm-> ToElement() -> Attribute("diffB")){
        colorB = stof(pNode -> ToElement() -> Attribute("diffB"));
      }
      cores[0]=colorR;
      cores[1]=colorG;
      cores[2]=colorB;
      Material* material = new Material(2,0,cores);
      figura->addMaterial(material);

    }

    if (pParm-> ToElement() -> Attribute("emiR")){
      if (pParm-> ToElement() -> Attribute("emiR")){
        colorR = stof(pNode -> ToElement() -> Attribute("emiR"));
      }
      if (pParm-> ToElement() -> Attribute("emiG")){
        colorG = stof(pNode -> ToElement() -> Attribute("emiG"));
      }
      if (pParm-> ToElement() -> Attribute("emiB")){
        colorB = stof(pNode -> ToElement() -> Attribute("emiB"));
      }
      cores[0]=colorR;
      cores[1]=colorG;
      cores[2]=colorB;
      Material* material = new Material(1,0,cores);
      figura->addMaterial(material);

    }

    if (pParm-> ToElement() -> Attribute("specR")){
      if (pParm-> ToElement() -> Attribute("specR")){
        colorR = stof(pNode -> ToElement() -> Attribute("specR"));
      }
      if (pParm-> ToElement() -> Attribute("specG")){
        colorG = stof(pNode -> ToElement() -> Attribute("specG"));
      }
      if (pParm-> ToElement() -> Attribute("specB")){
        colorB = stof(pNode -> ToElement() -> Attribute("specB"));
      }
      if (pParm-> ToElement() -> Attribute("shininess")){
        shininess = stof(pNode -> ToElement() -> Attribute("shininess"));
      }
      cores[0]=colorR;
      cores[1]=colorG;
      cores[2]=colorB;
      Material* material = new Material(0,shininess,cores);
      figura->addMaterial(material);

    }

    if (pParm-> ToElement() -> Attribute("ambR")){
      if (pParm-> ToElement() -> Attribute("ambR")){
        colorR = stof(pNode -> ToElement() -> Attribute("ambR"));
      }
      if (pParm-> ToElement() -> Attribute("ambG")){
        colorG = stof(pNode -> ToElement() -> Attribute("ambG"));
      }
      if (pParm-> ToElement() -> Attribute("ambB")){
        colorB = stof(pNode -> ToElement() -> Attribute("ambB"));
      }
      cores[0]=colorR;
      cores[1]=colorG;
      cores[2]=colorB;
      Material* material = new Material(3,0,cores);
      figura->addMaterial(material);

    }
      figura->print();
    (*shape)[*i].push_back(figura);
    }
  }
      pParm = pParm->NextSiblingElement();
}
}



int loadDoc(char* path,  shapeMatrix* shape, instructionsMatrix* instructionsMatrix ) {
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
    shapeStruct pontos; // vector de pontos vazio
    (*instructionsMatrix).push_back(insts);
    (*shape).push_back(pontos);
    parseGroup(group,shape,instructionsMatrix,&i);
    i++;
    group = group -> NextSiblingElement("group");
  }



  return 1;
}
return 0;
}

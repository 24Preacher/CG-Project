#include "../headers/parser.h"
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
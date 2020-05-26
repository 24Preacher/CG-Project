
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>

#include <vector>
#include <sstream>
#include "headers/parser.h"
#include "headers/Shape.h"


using namespace std;
//32*16 = 512
int indices[32][16];
const int nPatch = 16;



void make_Plane (float comprimento, float largura, const char* file){
  ofstream f (file, ios::out| ios::trunc );
  float cx = comprimento/2;
	float cz = largura/2;

  if(f.is_open()){
    f << cx << ' ' << 0.0 << ' ' << cz << '\n'
    	<< cx << ' ' << 0.0 << ' ' << -cz << '\n'
    	<< -cx << ' ' << 0.0 << ' ' << -cz << '\n'
      << cx << ' ' << 0.0 << ' ' << cz << '\n'
      << -cx << ' ' << 0.0 << ' ' << -cz << '\n'
      << -cx << ' ' << 0.0 << ' ' << cz << '\n';
  }
  f.close();

}

void make_Box (float comprimento, float largura, float altura, int divisoes, const char* file){
  int i,j;
  float cx = comprimento/2;
 	float cz = largura/2;
	float cy = altura /2;
  float rx = comprimento/divisoes;
	float rz = largura/divisoes;
	float ry = altura/divisoes;
  ofstream f (file,ios::out| ios::trunc );
  if(f.is_open()){
    for (i = 0; i < divisoes; i++) {
    for (j = 0; j < divisoes; j++) {
      //face da frente
      f << -cx + j*rx << ' ' << -cy + i*ry << ' ' << cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry << ' ' << cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry + ry << ' ' <<  cz << '\n'

        << -cx + j*rx << ' ' << -cy + i*ry << ' ' << cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry + ry << ' ' << cz << '\n'
        << -cx + j*rx << ' ' << -cy + i*ry << ' ' << cz << '\n';

        // face de cima
      f << -cx + j*rx << ' ' << cy << ' ' << cz - i*rz << '\n'
        << -cx + j*rx + rx << ' ' << cy << ' ' << cz - i*rz << '\n'
        << -cx + j*rx + rx << ' ' << cy << ' ' << cz - i*rz - rz << '\n'

        << -cx + j*rx << ' ' << cy << ' ' <<  cz - i*rz << '\n'
        << -cx + j*rx + rx << ' ' << cy << ' ' <<  cz - i*rz - rz << '\n'
        << -cx + j*rx << ' ' <<  cy << ' ' << cz - i*rz - rz << '\n';

      // face de trás
      f << -cx + j*rx << ' ' << -cy + i*ry << ' ' << -cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry + ry << ' ' << -cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry << ' ' << -cz << '\n'

        << -cx + j*rx << ' ' << -cy + i*ry << ' ' << -cz << '\n'
        << -cx + j*rx << ' ' << -cy + i*ry + ry << ' ' << -cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry + ry << ' ' << -cz << '\n';
      // face de baixo
      f << -cx + j*rx << ' ' << -cy << ' ' << cz - i*rz << '\n'
        << -cx + j*rx + rx << ' ' << -cy << ' ' << cz - i*rz - rz << '\n'
        << -cx + j*rx + rx << ' ' << -cy << ' ' << cz - i*rz << '\n'

        << -cx + j*rx << ' ' << -cy << ' ' << cz - i*rz << '\n'
        << -cx + j*rx << ' ' << -cy << ' ' << cz - i*rz - rz << '\n'
        << -cx + j*rx + rx << ' ' << -cy << ' ' << cz - i*rz - rz << '\n';
      // face da esquerda
      f << -cx << ' ' << -cy + i*ry << ' ' << cz - j*rz << '\n'
        << -cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz - rz << '\n'
        << -cx << ' ' << -cy + i*ry << ' ' << cz - j*rz - rz << '\n'

        << -cx << ' ' << -cy + i*ry << ' ' << cz - j*rz << '\n'
        << -cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz << '\n'
        << -cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz - rz  << '\n';
      // face da direita
      f << cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz - rz << '\n'
        << cx << ' ' << -cy + i*ry << ' ' << cz - j*rz << '\n'
        << cx << ' ' << -cy + i*ry << ' ' << cz - j*rz - rz << '\n'

        << cx << ' ' << -cy + i*ry << ' ' << cz - j*rz << '\n'
        << cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz - rz << '\n'
        << cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz << '\n';
      }

    }

  }
  f.close();

}


void make_Sphere (float radius, int slices, int stacks, const char* file){

    float h_stack = (M_PI/stacks); //altura de cada stack
    float a_slices = 2*M_PI / slices;
    int i, j;
    float alfa, beta = 0;

    ofstream f (file,ios::out| ios::trunc );
    if(f.is_open()){


    for(j=1; j<=stacks; j++){

        alfa = 0;
        for(i=1; i<=slices; i++){
          f << (radius * sin(beta) * sin(alfa)) << ' ' <<
                     (radius * cos(beta)) << ' ' <<
                     (radius * sin(beta) * cos(alfa)) << '\n'
            << (radius * sin(beta + h_stack) * sin(alfa)) << ' ' <<
                     (radius * cos(beta + h_stack)) << ' ' <<
                     (radius * sin(beta + h_stack) * cos(alfa)) << '\n'
            << (radius * sin(beta + h_stack) * sin(alfa + a_slices)) << ' ' <<
                     (radius * cos(beta + h_stack)) << ' ' <<
                     (radius * sin(beta + h_stack) * cos(alfa + a_slices)) << '\n'
             << (radius * sin(beta) * sin(alfa)) << ' ' <<
                 (radius * cos(beta)) << ' ' <<
                (radius * sin(beta) * cos(alfa)) << '\n'
            << (radius * sin(beta + h_stack) * sin(alfa + a_slices)) << ' ' <<
                (radius * cos(beta + h_stack)) << ' ' <<
                (radius * sin(beta + h_stack) * cos(alfa + a_slices)) << '\n'
             << (radius * sin(beta) * sin(alfa + a_slices)) << ' ' <<
                (radius * cos(beta)) << ' ' <<
                (radius * sin(beta) * cos(alfa + a_slices)) << '\n';
        alfa = i*a_slices;
        }
        beta = j * h_stack;
      }
    }
    f.close();

}




void make_Cone(float radius, float height, int slices, int stacks, const char* file){
    int i, j;
    float alt_stacks = height/stacks;
    float ang_slices = 2 * M_PI / slices;
		float tempangulo;
		float tempradius;
    ofstream f (file,ios::out| ios::trunc );
    if(f.is_open()){

  	//base
        for(i=0; i<slices; i++){
          tempangulo = i*ang_slices;
          f << radius * sin(tempangulo) << ' ' << 0 << ' '<< radius * cos(tempangulo) << '\n'
            << 0 << ' ' << 0 << ' ' << 0 << '\n'
            << radius * sin(tempangulo + ang_slices) << ' ' << 0 << ' ' << radius * cos(tempangulo + ang_slices) << '\n';

					}

		//lados
		tempradius = radius/stacks;
			for(j=0; j<stacks; j++){
				for(i=0; i<slices; i++){
					tempangulo = i*ang_slices;
          f << (radius - j*tempradius)*sin(tempangulo) << ' ' << alt_stacks*j << ' ' << (radius - j*tempradius)*cos(tempangulo) << '\n'

           << (radius - j*tempradius)*sin(tempangulo + ang_slices) << ' ' <<  alt_stacks*j << ' ' << (radius - j*tempradius)*cos(tempangulo + ang_slices) << '\n'

           << (radius - j*tempradius - tempradius)*sin(tempangulo + ang_slices) << ' ' << alt_stacks*j + alt_stacks << ' ' << (radius - j*tempradius - tempradius)*cos(tempangulo + ang_slices) << '\n'

           << (radius - j*tempradius)*sin(tempangulo) << ' ' << alt_stacks*j << ' ' << (radius - j*tempradius)*cos(tempangulo) << '\n'

           << (radius - j*tempradius - tempradius)*sin(tempangulo + ang_slices) << ' ' << alt_stacks*j + alt_stacks << ' ' << (radius - j*tempradius - tempradius)*cos(tempangulo + ang_slices) << '\n'

           << (radius - j*tempradius - tempradius)*sin(tempangulo) << ' ' << alt_stacks*j + alt_stacks << ' ' << (radius - j*tempradius - tempradius)*cos(tempangulo) << '\n';


				}
			}
    }
    f.close();

}




void make_Cylinder(float radius, float height, int slices, const char* file) {

float n_angle = 2 * M_PI / slices; //angulo de casa slice
float angle;
ofstream f (file,ios::out| ios::trunc );
if(f.is_open()){
for(int i = 0; i < slices; i++){
    angle = n_angle * i;
    //base de cima
    f << radius * cos(angle) << ' ' << height/2 << ' ' << radius * sin(angle) << '\n'
      << 0 << ' ' << height/2 << ' ' << 0 << '\n'
      << radius*cos(angle + n_angle) << ' ' << height/2 << ' ' << radius * sin(angle + n_angle) << '\n'
      //lateral (triangulos virados para baixo)
      << radius * cos(angle) << ' ' << height/2 << ' ' << radius * sin(angle) << '\n'
      << radius*cos(angle + n_angle) << ' ' << height/2 << ' ' << radius * sin(angle + n_angle) << '\n'
      << radius * cos(angle) << ' ' << -height/2 << ' ' << radius * sin(angle) << '\n'
      //lateral (triangulos virados para cima)
      << radius*cos(angle + n_angle) << ' ' << height/2 << ' ' << radius * sin(angle + n_angle) << '\n'
      << radius*cos(angle + n_angle) << ' ' << -height/2 << ' ' << radius * sin(angle + n_angle) << '\n'
      << radius * cos(angle) << ' ' << -height/2 << ' ' << radius * sin(angle) << '\n'
      //base de baixo
      << 0 << ' ' << -height/2 << ' ' << 0 << '\n'
      << radius * cos(angle) << ' ' << -height/2 << ' ' << radius * sin(angle) << '\n'
      << radius*cos(angle + n_angle) << ' ' << -height/2 << ' ' << radius * sin(angle + n_angle) << '\n';

  }
}
  f.close();
}

void make_Torus(float inside_radius, float outside_radius, int slices, int stacks, const char* file){
  float alfa, c, beta;
  float a = 2*M_PI/slices;
  float b = 2*M_PI/stacks;

  ofstream f (file,ios::out| ios::trunc );
  if(f.is_open()){
    for(int i = 0; i<slices; i++){
      alfa = i * a;

      for(int j = 0; j <= stacks; j++){
        beta = j * b;
        f
          << (outside_radius + inside_radius * cos(beta + b)) * cos(alfa) << ' ' << inside_radius * sin(beta + b) << ' ' << (outside_radius + inside_radius *cos(beta + b)) * sin(alfa) << '\n'
          << (outside_radius + inside_radius * cos(beta + b)) * cos(alfa + a) << ' ' << inside_radius * sin(beta + b) << ' ' << (outside_radius + inside_radius * cos(beta + b)) * sin(alfa + a) << '\n'
          << (outside_radius + inside_radius * cos(beta)) * cos(alfa + a) << ' ' << inside_radius * sin(beta) << ' ' << (outside_radius + inside_radius * cos(beta)) * sin(alfa + a) << '\n'

          << (outside_radius + inside_radius * cos(beta)) * cos(alfa) << ' ' << inside_radius * sin(beta) << ' ' << (outside_radius + inside_radius * cos(beta)) * sin(alfa) << '\n'
          << (outside_radius + inside_radius * cos(beta + b)) * cos(alfa) << ' ' << inside_radius * sin(beta + b) << ' ' << (outside_radius + inside_radius * cos(beta + b)) * sin(alfa) << '\n'
          << (outside_radius + inside_radius * cos(beta)) * cos(alfa + a) << ' ' << inside_radius * sin(beta) << ' ' << (outside_radius + inside_radius * cos(beta)) * sin(alfa + a) << '\n';


      }
    }
  }
      f.close();
}


//-------------resolução da addams


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



Ponto* pontosBezier(float *p1, float *p2, float *p3, float *p4, float t){
    float x = (1 - t);
    float ponto[3];

    //ver slides das curvas - bezier curves degree 3
    float x0,x1,x2,x3;
    x0 = pow(x, 3);
    x1 = 3 * x * pow(x,2) * t;
    x2 = 3 * x * pow(t,2);
    x3 = pow(t,3);

    ponto[0] = x0*p1[0] + x1*p2[0] + x2*p3[0] + x3*p4[0];
    ponto[1] = x0*p1[1] + x1*p2[1] + x2*p3[1] + x3*p4[1];
    ponto[2] = x0*p1[2] + x1*p2[2] + x2*p3[2] + x3*p4[2];


    Ponto *p = new Ponto();
    (*p).x = ponto[0];
    (*p).y = ponto[1];
    (*p).z = ponto[2];

    return p;


}







//ver slides das curvas - bezier patches (pontos verdes- control points e ponto vermelho- ponto no patch)
//nos patches usa-se o u em vez do t
//temos que obter 4 pontos (control points) para o calculo de bezier
Ponto* calcBezierPatch(std::vector<Ponto> controlPoints, int np, float u, float v){
    int n = 16;
    float aux[n][3], res[n][3];
    Ponto *p, *ponto;

    int j=0, w=0;
    for(int i=0; i<n; i++){
      aux[j][0] = controlPoints[indices[np][i]].x;
      aux[j][1] = controlPoints[indices[np][i]].y;
      aux[j][2] = controlPoints[indices[np][i]].z;
      j++;
      //j é multiplo de 4 pq são precisos 4 pontos para cada calculo de Bezier
      if(j % 4 == 0){
        p = pontosBezier(aux[0], aux[1], aux[2], aux[3], u);
        res[w][0] = p->x;
        res[w][1] = p->y;
        res[w][2] = p->z;

        w++;
        j=0;

      }

    }
    ponto = pontosBezier(res[0], res[1], res[2], res[3], v);
    return ponto;
}


// No ficheiro irão estar descritos os pontos de controlo e o valor da tesselation
// função para fazer parse do ficheiro
Shape* bezier_patches(int tesselation, const string& file) {
  std::ifstream f;
  f.open(file);

  int nBezier = 0;
  int ncontrolPoints = 0;
  int bezier = 0;
  int i,j;
  Shape* shape = new Shape();
  string aux,aux2;
  std::vector<Ponto> pontos;

  if ( f.is_open() ) {

      getline(f, aux);
      printf("%s\n", aux.c_str() );
      nBezier = stoi(aux);
      printf("Numero de Bezier Patches %d\n", nBezier );




      std::vector<string> tokens;


      //de 0 a 31 -> indices dos pontos controlo, 16 cada
        for( i = 0; i < nBezier ;i++ ) {
          std::string line;
          getline(f,line);
          tokens = split(line, ' ');
          for( j = 0; j < nPatch ; j++ ) {
            indices[i][j] = stoi(tokens[j],nullptr);

          }
          //int aux2 = stoi(line);
          for( int u = 0; u < tokens.size(); u++){
            indices[i][u] = stoi(tokens[u]);
            printf("%d\n", indices[i][u] );
          }
        }

    printf("Bezier chegou ao final com o valor -> %d que tem de ser 32\n", nBezier );
    getline(f,aux2);
    ncontrolPoints = stoi(aux2); //nmr de control points
    printf("Numero de control points %d\n", ncontrolPoints);
    for( int z = 0; z < ncontrolPoints; z++ ){
      std::string line1;
      getline(f,line1);
      tokens = split(line1, ',');
      pontos.reserve(ncontrolPoints);
      Ponto *p = new Ponto();
      (*p).x = stof(tokens[0],nullptr);
      (*p).y = stof(tokens[1],nullptr);
      (*p).z = stof(tokens[2],nullptr);
      pontos.push_back(*p);
      printf("control z=%d : %f,%f,%f\n",z,(*p).x,(*p).y,(*p).z );
    }
  }

  f.close();


  float u1, v1, u2, v2, inc = 1.0/tesselation;
  Ponto* res[nBezier][4];

  for(int i=0; i<nBezier; i++){
    for(int j=0; j<tesselation; j++){
      for(int w=0; w<tesselation; w++){
          u1 = j*inc;
          v1 = w*inc;
          u2 = (j+1)*inc;
          v2 = (w+1)*inc;

          res[i][0] = calcBezierPatch(pontos, i, u1, v1);
          res[i][1] = calcBezierPatch(pontos, i, u2, v1);
          res[i][2] = calcBezierPatch(pontos, i, u1, v2);
          res[i][3] = calcBezierPatch(pontos, i, u2,v2);



          Ponto *p0 = new Ponto();
          (*p0).x = (res[i][0])->x;
          (*p0).y = (res[i][0])->y;
          (*p0).z = (res[i][0])->z;

          Ponto *p1 = new Ponto();
          (*p1).x = (res[i][1])->x;
          (*p1).y = (res[i][1])->y;
          (*p1).z = (res[i][1])->z;

          Ponto *p3 = new Ponto();
          (*p3).x = (res[i][3])->x;
          (*p3).y = (res[i][3])->y;
          (*p3).z = (res[i][3])->z;


          Ponto *p2 = new Ponto();
          (*p2).x = (res[i][2])->x;
          (*p2).y = (res[i][2])->y;
          (*p2).z = (res[i][2])->z;


          //0,1,3
          shape->inserePonto(p0);
          shape->inserePonto(p1);
          shape->inserePonto(p3);
          //0,3,2
          shape->inserePonto(p0);
          shape->inserePonto(p3);
          shape->inserePonto(p2);


      }
    }
  }

  shape->print();

 return shape;

}


void help(){
printf ( " ┌------------------------------------------- PRIMITIVES -------------------------------------------┐\n");
printf ( " |                                                                                                  |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ PLANE                                                                                        |\n");
printf ( " |       $ ./generator plane <COMPRIMENTO> <LARGURA> <OUTPUT_FILE>                                  |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ BOX                                                                                          |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator box <COMPRIMENTO> <LARGURA> <ALTURA> [<DIVISOES>] <OUTPUT_FILE>              |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ SPHERE                                                                                       |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator sphere <RAIO> <SLICES> <STACKS> <OUTPUT_FILE>                                |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ CONE                                                                                         |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator cone <RAIO_BASE> <ALTURA> <SLICES> <STACKS> <OUTPUT_FILE>                    |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ Cylinder                                                                                     |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator cylinder <raio> <altura> <Slices>  <OUTPUT_FILE>                             |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ Torus                                                                                        |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator torus <raio interior> <raio exterior> <Slices> <Stacks> <OUTPUT_FILE>        |\n");
printf ( " |                                                                                                  |\n");
printf ( " |                                                                                                  |\n");
printf ( " └--------------------------------------------------------------------------------------------------┘\n");
}



int main(int argc, char **argv) {
std::string str = argv[1];
std::string folder = "models/";
  if (!str.compare("plane")){
    if (argc != 5)
      printf("Invalid input. Try -help for help.\n");
    else {
      folder.append(argv[4]);
      const char* file = folder.c_str();

      make_Plane(stof(argv[2]),stof(argv[2]),file);

    }
  }
  else if (!str.compare("box")){
    if (argc != 7)
      printf("Invalid input. Try -help for help.\n");
    else {
      folder.append(argv[6]);
      const char* file = folder.c_str();
      make_Box(stof(argv[2]),stof(argv[3]),stof(argv[4]),stof(argv[5]),file);
    }
  }
  else if (!str.compare("sphere")){
    if (argc != 6)
      printf("Invalid input. Try -help for help.\n");
    else {
      folder.append(argv[5]);
      const char* file = folder.c_str();
      make_Sphere(stof(argv[2]),stof(argv[3]),stof(argv[4]),file);
    }
  }
  else if (!str.compare("cone")){
    if (argc != 7)
      printf("Invalid input. Try -help for help.\n");
    else {
      folder.append(argv[6]);
      const char* file = folder.c_str();
      make_Cone(stof(argv[2]),stof(argv[3]),stof(argv[4]),stof(argv[5]),file);
    }
  }
  else if (!str.compare("cylinder")){
    if (argc != 6)
      printf("Invalid input. Try -help for help.\n");
    else {
      folder.append(argv[5]);
      const char* file = folder.c_str();
      make_Cylinder(stof(argv[2]),stof(argv[3]),stof(argv[4]),file);
    }
  }
  else if (!str.compare("torus")){
    if (argc != 7)
      printf("Invalid input. Try -help for help.\n");
    else {
      folder.append(argv[6]);
      const char* file = folder.c_str();
      make_Torus(stof(argv[2]),stof(argv[3]),stof(argv[4]),stof(argv[5]),file);
    }
  }
  else if(!str.compare("bezier")){

    bezier_patches(10, "teapot.patch");
  }
  else if (!str.compare("-help"))
     help();
  else printf("Command not found. Try -help for help.\n");

  return 1;

}

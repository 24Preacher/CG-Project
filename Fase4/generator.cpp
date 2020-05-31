
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
#include <stdio.h>

#include <vector>
#include <sstream>
#include "headers/instruction.h"
#include "headers/Shape.h"
#include "headers/utils.h"


using namespace std;
//32*16 = 512
int indices[32][16];
const int nPatch = 16;


void calcNormals(vector<Ponto*>* pontos,vector<Ponto*>* normals){
  int i,j,a;
  vector<Ponto*>pontosIguais;
  for(i=0;i<pontos->size();i++){
    Ponto * p = pontos -> at(i);
    if(!(pertenceP(p,(&pontosIguais)))){
    vector<Ponto*> npontosIguais;
    vector<int> indices;
    for(j=0;j<pontos->size();j++){
      if(equalsP(p,(pontos -> at(j)))){
        pontosIguais.push_back((pontos -> at(j)));
        indices.push_back(j);
      }
    }
    for(a=0;a<indices.size();a++){
      npontosIguais.push_back(normals->at((indices.at(a))));
    }
      Ponto* norm = new Ponto();
      meanP(&npontosIguais,norm);
      normalizeP(norm);
      for(a=0;a<indices.size();a++){
        copyP(norm,normals->at(a));
      }
    }
  }

}


void prinTofile(vector<Ponto*>* pontos,vector<Ponto*>* normals,vector<Ponto*>* textcoords,const char* filename){
  int i;
  ofstream f (filename,ios::out| ios::trunc );
  if(f.is_open()){
    if(pontos->size()==normals->size() && normals->size()==textcoords->size()){

    for (i=0;i<pontos->size();i++){
      f << pontos -> at(i) -> x << ' '
        << pontos -> at(i) -> y << ' '
        << pontos -> at(i) -> z << ' '
        << normals -> at(i) -> x << ' '
        << normals -> at(i) -> y << ' '
        << normals -> at(i) -> z << ' '
        << textcoords -> at(i) -> x << ' '
        << textcoords -> at(i) -> y << '\n';
      }
    }
    f.close();
  }
  else{
    printf("wrong vectors\n" );
  }

}


void make_Plane (float comprimento, float largura, const char* file){
  float cx = comprimento/2;
	float cz = largura/2;



    vector<Ponto*> pontos;
    vector<Ponto*> normals;
    vector<Ponto*> textcoords;


    Ponto* p1 = new Ponto();
    p1->x = cx;
    p1->y = 0.0;
    p1->z = cz;

    Ponto* p2 = new Ponto();
    p2->x = cx;
    p2->y = 0.0;
    p2->z = -cz;

    Ponto* p3 = new Ponto();
    p3->x = -cx;
    p3->y = 0.0;
    p3->z = -cz;

    pontos.push_back(p1);
    pontos.push_back(p2);
    pontos.push_back(p3);

    Ponto* temp = new Ponto();
    Ponto* temp2 = new Ponto();
    diffP(p2,p1,temp);
    diffP(p3,p1,temp2);
    Ponto* np = new Ponto();
    crossP(temp,temp2,np);
    delete(temp);
    delete(temp2);
    normalizeP(np);
    Ponto* np1 = new Ponto();
    Ponto* np2 = new Ponto();
    copyP(np,np1);
    copyP(np,np2);
    normals.push_back(np);
    normals.push_back(np1);
    normals.push_back(np2);
    Ponto*tp1 = new Ponto();
    Ponto*tp2 = new Ponto();
    Ponto*tp3 = new Ponto();
    tp1->x =0;
    tp1->y =0;
    tp1->z =0;
    tp2->x =0;
    tp2->y =0;
    tp2->z =0;
    tp3->x =0;
    tp3->y =0;
    tp3->z =0;
    textcoords.push_back(tp1);
    textcoords.push_back(tp2);
    textcoords.push_back(tp3);

    p1 = new Ponto();
    p1->x = cx;
    p1->y = 0.0;
    p1->z = cz;

    p2 = new Ponto();
    p2->x = -cx;
    p2->y = 0.0;
    p2->z = -cz;

    p3 = new Ponto();
    p3->x = -cx;
    p3->y = 0.0;
    p3->z = cz;


    pontos.push_back(p1);
    pontos.push_back(p2);
    pontos.push_back(p3);

    temp = new Ponto();
    temp2 = new Ponto();
    diffP(p2,p1,temp);
    diffP(p3,p1,temp2);
    np = new Ponto();
    crossP(temp,temp2,np);
    delete(temp);
    delete(temp2);
    normalizeP(np);
     np1 = new Ponto();
     np2 = new Ponto();
    copyP(np,np1);
    copyP(np,np2);
    normals.push_back(np);
    normals.push_back(np1);
    normals.push_back(np2);
    tp1 = new Ponto();
    tp2 = new Ponto();
    tp3 = new Ponto();
    tp1->x =0;
    tp1->y =0;
    tp1->z =0;
    tp2->x =0;
    tp2->y =0;
    tp2->z =0;
    tp3->x =0;
    tp3->y =0;
    tp3->z =0;
    textcoords.push_back(tp1);
    textcoords.push_back(tp2);
    textcoords.push_back(tp3);

    calcNormals(&pontos,&normals);
    prinTofile(&pontos,&normals,&textcoords,file);


}

void make_Box (float comprimento, float largura, float altura, int divisoes, const char* file){
  int i,j;
  float cx = comprimento/2;
 	float cz = largura/2;
	float cy = altura /2;
  float rx = comprimento/divisoes;
	float rz = largura/divisoes;
	float ry = altura/divisoes;
    vector<Ponto*> pontos;
    vector<Ponto*> normals;
    vector<Ponto*> textcoords;
    for (i = 0; i < divisoes; i++) {
    for (j = 0; j < divisoes; j++) {

      Ponto* p1 = new Ponto();
      p1->x = -cx + j*rx;
      p1->y = -cy + i*ry;
      p1->z = cz;

      Ponto* p2 = new Ponto();
      p2->x = -cx + j*rx + rx;
      p2->y = -cy + i*ry;
      p2->z = cz;

      Ponto* p3 = new Ponto();
      p3->x = -cx + j*rx;
      p3->y = -cy + i*ry + ry;
      p3->z = cz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

      Ponto* temp = new Ponto();
      Ponto* temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
      Ponto* np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
      Ponto* np1 = new Ponto();
      Ponto* np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      Ponto*tp1 = new Ponto();
      Ponto*tp2 = new Ponto();
      Ponto*tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);


      p1 = new Ponto();
      p1->x =  -cx + j*rx;
      p1->y = -cy + i*ry;
      p1->z = cz;

      p2 = new Ponto();
      p2->x = -cx + j*rx + rx;
      p2->y = -cy + i*ry + ry;
      p2->z = cz;

      p3 = new Ponto();
      p3->x = -cx + j*rx;
      p3->y = -cy + i*ry;
      p3->z = cz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

      temp = new Ponto();
      temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = -cx + j*rx;
      p1->y = cy;
      p1->z = cz - i*rz;

      p2 = new Ponto();
      p2->x = -cx + j*rx + rx;
      p2->y = cy;
      p2->z = cz - i*rz;

      p3 = new Ponto();
      p3->x = -cx + j*rx + rx;
      p3->y = cy;
      p3->z = cz - i*rz - rz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);


      p1 = new Ponto();
      p1->x = -cx + j*rx;
      p1->y = cy;
      p1->z = cz - i*rz;

      p2 = new Ponto();
      p2->x = -cx + j*rx + rx;
      p2->y = cy;
      p2->z = cz - i*rz - rz;

      p3 = new Ponto();
      p3->x = -cx + j*rx;
      p3->y = cy;
      p3->z = cz - i*rz - rz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = -cx + j*rx;
      p1->y = -cy + i*ry;
      p1->z = -cz;

      p2 = new Ponto();
      p2->x = -cx + j*rx + rx;
      p2->y = -cy + i*ry + ry;
      p2->z = -cz;

      p3 = new Ponto();
      p3->x = -cx + j*rx + rx;
      p3->y = -cy + i*ry;
      p3->z = -cz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);


      p1 = new Ponto();
      p1->x = -cx + j*rx;
      p1->y = -cy + i*ry;
      p1->z = -cz;

      p2 = new Ponto();
      p2->x = -cx + j*rx;
      p2->y = -cy + i*ry + ry;
      p2->z = -cz;

      p3 = new Ponto();
      p3->x = -cx + j*rx + rx;
      p3->y = -cy + i*ry + ry;
      p3->z = -cz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = -cx + j*rx;
      p1->y = -cy;
      p1->z = cz - i*rz;

      p2 = new Ponto();
      p2->x = -cx + j*rx + rx;
      p2->y = -cy;
      p2->z = cz - i*rz - rz;

      p3 = new Ponto();
      p3->x = -cx + j*rx + rx;
      p3->y = -cy;
      p3->z = cz - i*rz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);


      p1 = new Ponto();
      p1->x = -cx + j*rx;
      p1->y = -cy;
      p1->z = cz - i*rz;

      p2 = new Ponto();
      p2->x = -cx + j*rx;
      p2->y = -cy;
      p2->z = cz - i*rz - rz;

      p3 = new Ponto();
      p3->x = -cx + j*rx + rx;
      p3->y = -cy;
      p3->z = cz - i*rz - rz;


      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = -cx;
      p1->y = -cy + i*ry;
      p1->z = cz - j*rz;

      p2 = new Ponto();
      p2->x = -cx;
      p2->y = -cy + i*ry +ry;
      p2->z = cz - j*rz - rz;

      p3 = new Ponto();
      p3->x = -cx;
      p3->y = -cy + i*ry;
      p3->z = cz - j*rz - rz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = -cx;
      p1->y = -cy + i*ry;
      p1->z = cz - j*rz;

      p2 = new Ponto();
      p2->x = -cx;
      p2->y = -cy + i*ry +ry;
      p2->z = cz - j*rz;

      p3 = new Ponto();
      p3->x = -cx;
      p3->y = -cy + i*ry +ry;
      p3->z = cz - j*rz - rz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = cx;
      p1->y = -cy + i*ry +ry;
      p1->z = cz - j*rz - rz;

      p2 = new Ponto();
      p2->x = cx;
      p2->y = -cy + i*ry;
      p2->z = cz - j*rz;

      p3 = new Ponto();
      p3->x = cx;
      p3->y = -cy + i*ry;
      p3->z = cz - j*rz - rz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = cx;
      p1->y = -cy + i*ry;
      p1->z = cz - j*rz;

      p2 = new Ponto();
      p2->x = cx;
      p2->y = -cy + i*ry +ry;
      p2->z = cz - j*rz - rz;

      p3 = new Ponto();
      p3->x = cx;
      p3->y = -cy + i*ry +ry;
      p3->z = cz - j*rz;

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

       temp = new Ponto();
       temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
       np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
       np1 = new Ponto();
       np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      }

    }
    calcNormals(&pontos,&normals);
    prinTofile(&pontos,&normals,&textcoords,file);

}

void sphere_text(float alpha, float beta, float* resx, float* resy) {
    float dx = (1.0 / (2.0*M_PI)) * (-alpha) + 1.0;
    float dy = (1.0 / (M_PI)) * (beta + (M_PI / 2.0));

    if (dx<0)
      dx=0.0;
    if (dx>1)
      dx=1.0;
    if (dy<0)
      dy=0.0;
    if (dy>1)
      dy=1.0;

    *resx = dx;
    *resy = dy;
}


void make_Sphere (float radius, int slices, int stacks, const char* file){

  float d_beta  = (M_PI / stacks);
  float d_alfa = (2*M_PI / slices);
  int i, j;
  float alfa, beta;

    ofstream f (file,ios::out| ios::trunc );
    if(f.is_open()){
      float normals [3];
      float textX = 0,textY = 0;

    for(j=0; j<stacks; j++){

        for(i=0; i<slices; i++){

          alfa = i*(2*M_PI / slices);
          beta = j*(M_PI / stacks) - (M_PI / 2);

          normals[0]= (radius * cos(alfa) * cos(beta));
          normals[1]= (radius * sin(beta));
          normals[2]= (radius * sin(alfa) * cos(beta));

          f << (radius * cos(alfa) * cos(beta)) << ' ' <<
                     (radius * sin(beta)) << ' ' <<
                     (radius * sin(alfa) * cos(beta)) << ' ';
          normalize(normals);
          f << normals[0] << ' ' << normals[1] << ' ' << normals[2] <<  ' ';

          sphere_text(alfa,beta,&textX,&textY);

          f << textX << ' ' << textY << '\n';

          normals[0]= (radius * cos(alfa) * cos(beta + d_beta));
          normals[1]= (radius * sin(beta + d_beta));
          normals[2]= (radius * sin(alfa) * cos(beta + d_beta));

          f << (radius * cos(alfa) * cos(beta + d_beta)) << ' ' <<
                   (radius * sin(beta + d_beta)) << ' ' <<
                   (radius * sin(alfa) * cos(beta + d_beta)) <<  ' ';

          normalize(normals);

          f << normals[0] << ' ' << normals[1] << ' ' << normals[2] <<  ' ';

          sphere_text(alfa,beta + d_beta,&textX,&textY);

          f << textX << ' ' << textY << '\n';

          normals[0]= (radius * cos(alfa + d_alfa) * cos(beta));
          normals[1]= (radius * sin(beta));
          normals[2]= (radius * sin(alfa + d_alfa) * cos(beta));


          f << (radius * cos(alfa + d_alfa) * cos(beta)) << ' ' <<
               (radius * sin(beta)) << ' ' <<
               (radius * sin(alfa + d_alfa) * cos(beta)) << ' ';

          normalize(normals);

          f << normals[0] << ' ' << normals[1] << ' ' << normals[2] <<  ' ';

          sphere_text(alfa + d_alfa,beta,&textX,&textY);

          f << textX << ' ' << textY << '\n';

          normals[0]= (radius * cos(alfa) * cos(beta + d_beta));
          normals[1]= (radius * sin(beta + d_beta));
          normals[2]= (radius * sin(alfa) * cos(beta + d_beta));

          f << (radius * cos(alfa) * cos(beta + d_beta)) << ' ' <<
               (radius * sin(beta + d_beta)) << ' ' <<
               (radius * sin(alfa) * cos(beta + d_beta)) << ' ';

          normalize(normals);

          f << normals[0] << ' ' << normals[1] << ' ' << normals[2] <<  ' ';

          sphere_text(alfa,beta + d_beta,&textX,&textY);

          f << textX << ' ' << textY << '\n';

          normals[0]= (radius * cos(alfa + d_alfa) * cos(beta + d_beta));
          normals[1]= (radius * sin(beta + d_beta));
          normals[2]= (radius * sin(alfa + d_alfa) * cos(beta + d_beta));

          f << (radius * cos(alfa + d_alfa) * cos(beta + d_beta)) << ' ' <<
               (radius * sin(beta + d_beta)) << ' ' <<
               (radius * sin(alfa + d_alfa) * cos(beta + d_beta)) << ' ';

          normalize(normals);

          f << normals[0] << ' ' << normals[1] << ' ' << normals[2] <<  ' ';

          sphere_text(alfa + d_alfa,beta + d_beta,&textX,&textY);

          f << textX << ' ' << textY << '\n';

          normals[0]= (radius * cos(alfa + d_alfa) * cos(beta));
          normals[1]= (radius * sin(beta));
          normals[2]= (radius * sin(alfa + d_alfa) * cos(beta));

          f << (radius * cos(alfa + d_alfa) * cos(beta)) << ' ' <<
               (radius * sin(beta)) << ' ' <<
               (radius * sin(alfa + d_alfa) * cos(beta)) << ' ';

          normalize(normals);

          f << normals[0] << ' ' << normals[1] << ' ' << normals[2] <<  ' ';

          sphere_text(alfa + d_alfa,beta,&textX,&textY);

          f << textX << ' ' << textY << '\n';

        }
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
    vector<Ponto*> pontos;
    vector<Ponto*> normals;
    vector<Ponto*> textcoords;

        for(i=0; i<slices; i++){
          tempangulo = i*ang_slices;

          Ponto* p1 = new Ponto();
          p1->x = radius * sin(tempangulo);
          p1->y = 0;
          p1->z = radius * cos(tempangulo);

          Ponto* p2 = new Ponto();
          p2->x = 0;
          p2->y = 0;
          p2->z = 0;

          Ponto* p3 = new Ponto();
          p3->x = radius * sin(tempangulo + ang_slices);
          p3->y = 0;
          p3->z = radius * cos(tempangulo + ang_slices);

          pontos.push_back(p1);
          pontos.push_back(p2);
          pontos.push_back(p3);

          Ponto* temp = new Ponto();
          Ponto* temp2 = new Ponto();
          diffP(p2,p1,temp);
          diffP(p3,p1,temp2);
          Ponto* np = new Ponto();
          crossP(temp,temp2,np);
          delete(temp);
          delete(temp2);
          normalizeP(np);
          Ponto* np1 = new Ponto();
          Ponto* np2 = new Ponto();
          copyP(np,np1);
          copyP(np,np2);
          normals.push_back(np);
          normals.push_back(np1);
          normals.push_back(np2);
          Ponto*tp1 = new Ponto();
          Ponto*tp2 = new Ponto();
          Ponto*tp3 = new Ponto();
          tp1->x =0;
          tp1->y =0;
          tp1->z =0;
          tp2->x =0;
          tp2->y =0;
          tp2->z =0;
          tp3->x =0;
          tp3->y =0;
          tp3->z =0;
          textcoords.push_back(tp1);
          textcoords.push_back(tp2);
          textcoords.push_back(tp3);

					}

		tempradius = radius/stacks;
			for(j=0; j<stacks; j++){
				for(i=0; i<slices; i++){
					tempangulo = i*ang_slices;

          Ponto* p1 = new Ponto();
          p1->x = (radius - j*tempradius)*sin(tempangulo);
          p1->y= alt_stacks*j;
          p1->z = (radius - j*tempradius)*cos(tempangulo);


          Ponto* p2 = new Ponto();
          p2->x = (radius - j*tempradius)*sin(tempangulo + ang_slices);
          p2->y = alt_stacks*j;
          p2->z = (radius - j*tempradius)*cos(tempangulo + ang_slices);


          Ponto* p3= new Ponto();
          p3->x = (radius - j*tempradius - tempradius)*sin(tempangulo + ang_slices);
          p3->y = alt_stacks*j + alt_stacks;
          p3->z= (radius - j*tempradius - tempradius)*cos(tempangulo + ang_slices);


          pontos.push_back(p1);
          pontos.push_back(p2);
          pontos.push_back(p3);

          Ponto* temp = new Ponto();
          Ponto* temp2 = new Ponto();
          diffP(p2,p1,temp);
          diffP(p3,p1,temp2);
          Ponto* np = new Ponto();
          crossP(temp,temp2,np);
          delete(temp);
          delete(temp2);
          normalizeP(np);
          Ponto* np1 = new Ponto();
          Ponto* np2 = new Ponto();
          copyP(np,np1);
          copyP(np,np2);
          normals.push_back(np);
          normals.push_back(np1);
          normals.push_back(np2);
          Ponto*tp1 = new Ponto();
          Ponto*tp2 = new Ponto();
          Ponto*tp3 = new Ponto();
          tp1->x =0;
          tp1->y =0;
          tp1->z =0;
          tp2->x =0;
          tp2->y =0;
          tp2->z =0;
          tp3->x =0;
          tp3->y =0;
          tp3->z =0;
          textcoords.push_back(tp1);
          textcoords.push_back(tp2);
          textcoords.push_back(tp3);


          p1 = new Ponto();
          p1->x = (radius - j*tempradius)*sin(tempangulo);
          p1->y = alt_stacks*j;
          p1->z = (radius - j*tempradius)*cos(tempangulo);

          p2 = new Ponto();
          p2->x = (radius - j*tempradius - tempradius)*sin(tempangulo + ang_slices);
          p2->y = alt_stacks*j + alt_stacks;
          p2->z = (radius - j*tempradius - tempradius)*cos(tempangulo + ang_slices);

          p3 = new Ponto();
          p3->x = (radius - j*tempradius - tempradius)*sin(tempangulo);
          p3->y = alt_stacks*j + alt_stacks;
          p3->z = (radius - j*tempradius - tempradius)*cos(tempangulo);

          pontos.push_back(p1);
          pontos.push_back(p2);
          pontos.push_back(p3);

          temp = new Ponto();
          temp2 = new Ponto();
          diffP(p2,p1,temp);
          diffP(p3,p1,temp2);
          np = new Ponto();
          crossP(temp,temp2,np);
          delete(temp);
          delete(temp2);
          normalizeP(np);
          np1 = new Ponto();
          np2 = new Ponto();
          copyP(np,np1);
          copyP(np,np2);
          normals.push_back(np);
          normals.push_back(np1);
          normals.push_back(np2);
          tp1 = new Ponto();
          tp2 = new Ponto();
          tp3 = new Ponto();
          tp1->x =0;
          tp1->y =0;
          tp1->z =0;
          tp2->x =0;
          tp2->y =0;
          tp2->z =0;
          tp3->x =0;
          tp3->y =0;
          tp3->z =0;
          textcoords.push_back(tp1);
          textcoords.push_back(tp2);
          textcoords.push_back(tp3);

				}
			}
        calcNormals(&pontos,&normals);
        prinTofile(&pontos,&normals,&textcoords,file);
}




void make_Cylinder(float radius, float height, int slices, const char* file) {

float n_angle = 2 * M_PI / slices;
float angle;
ofstream f (file,ios::out| ios::trunc );
vector<Ponto*> pontos;
vector<Ponto*> normals;
vector<Ponto*> textcoords;

for(int i = 0; i < slices; i++){
    angle = n_angle * i;

      Ponto* p1 = new Ponto();
      p1->x = radius * cos(angle);
      p1->y = height/2;
      p1->z = radius * sin(angle);

      Ponto* p2 = new Ponto();
      p2->x = 0;
      p2->y = height/2;
      p2->z = 0;

      Ponto* p3 = new Ponto();
      p3->x = radius*cos(angle + n_angle);
      p3->y = height/2;
      p3->z = radius * sin(angle + n_angle);

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

      Ponto* temp = new Ponto();
      Ponto* temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
      Ponto* np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
      Ponto* np1 = new Ponto();
      Ponto* np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      Ponto*tp1 = new Ponto();
      Ponto*tp2 = new Ponto();
      Ponto*tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = radius * cos(angle);
      p1->y = height/2;
      p1->z = radius * sin(angle);

      p2 = new Ponto();
      p2->x = radius*cos(angle + n_angle);
      p2->y = height/2;
      p2->z = radius * sin(angle + n_angle);

      p3 = new Ponto();
      p3->x = radius * cos(angle);
      p3->y = -height/2;
      p3->z = radius * sin(angle);

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

      temp = new Ponto();
      temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
      np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
      np1 = new Ponto();
      np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = radius*cos(angle + n_angle);
      p1->y = height/2;
      p1->z = radius * sin(angle + n_angle);

      p2 = new Ponto();
      p2->x = radius*cos(angle + n_angle);
      p2->y = -height/2;
      p2->z = radius * sin(angle + n_angle);

      p3 = new Ponto();
      p3->x = radius * cos(angle);
      p3->y = -height/2;
      p3->z = radius * sin(angle);

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

      temp = new Ponto();
      temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
      np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
      np1 = new Ponto();
      np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);

      p1 = new Ponto();
      p1->x = 0;
      p1->y = -height/2;
      p1->z = 0;

      p2 = new Ponto();
      p2->x = radius * cos(angle);
      p2->y = -height/2;
      p2->z = radius * sin(angle);

      p3 = new Ponto();
      p3->x = radius*cos(angle + n_angle);
      p3->y = -height/2;
      p3->z = radius * sin(angle + n_angle);

      pontos.push_back(p1);
      pontos.push_back(p2);
      pontos.push_back(p3);

      temp = new Ponto();
      temp2 = new Ponto();
      diffP(p2,p1,temp);
      diffP(p3,p1,temp2);
      np = new Ponto();
      crossP(temp,temp2,np);
      delete(temp);
      delete(temp2);
      normalizeP(np);
      np1 = new Ponto();
      np2 = new Ponto();
      copyP(np,np1);
      copyP(np,np2);
      normals.push_back(np);
      normals.push_back(np1);
      normals.push_back(np2);
      tp1 = new Ponto();
      tp2 = new Ponto();
      tp3 = new Ponto();
      tp1->x =0;
      tp1->y =0;
      tp1->z =0;
      tp2->x =0;
      tp2->y =0;
      tp2->z =0;
      tp3->x =0;
      tp3->y =0;
      tp3->z =0;
      textcoords.push_back(tp1);
      textcoords.push_back(tp2);
      textcoords.push_back(tp3);
  }

calcNormals(&pontos,&normals);
prinTofile(&pontos,&normals,&textcoords,file);
}

void make_Torus(float inside_radius, float outside_radius, int slices, int stacks, const char* file){
  float alfa, c, beta;
  float a = 2*M_PI/slices;
  float b = 2*M_PI/stacks;

  vector<Ponto*> pontos;
  vector<Ponto*> normals;
  vector<Ponto*> textcoords;

    for(int i = 0; i<slices; i++){
      alfa = i * a;

      for(int j = 0; j <= stacks; j++){
        beta = j * b;

        Ponto* p1 = new Ponto();
        p1->x = (outside_radius + inside_radius * cos(beta + b)) * cos(alfa);
        p1->y = inside_radius * sin(beta + b);
        p1->z = (outside_radius + inside_radius *cos(beta + b)) * sin(alfa);

        Ponto* p2 = new Ponto();
        p2->x = (outside_radius + inside_radius * cos(beta + b)) * cos(alfa + a);
        p2->y = inside_radius * sin(beta + b);
        p2->z = (outside_radius + inside_radius * cos(beta + b)) * sin(alfa + a);

        Ponto* p3 = new Ponto();
        p3->x = (outside_radius + inside_radius * cos(beta)) * cos(alfa + a);
        p3->y = inside_radius * sin(beta);
        p3->z = (outside_radius + inside_radius * cos(beta)) * sin(alfa + a);

        pontos.push_back(p1);
        pontos.push_back(p2);
        pontos.push_back(p3);

        Ponto* temp = new Ponto();
        Ponto* temp2 = new Ponto();
        diffP(p2,p1,temp);
        diffP(p3,p1,temp2);
        Ponto* np = new Ponto();
        crossP(temp,temp2,np);
        delete(temp);
        delete(temp2);
        normalizeP(np);
        Ponto* np1 = new Ponto();
        Ponto* np2 = new Ponto();
        copyP(np,np1);
        copyP(np,np2);
        normals.push_back(np);
        normals.push_back(np1);
        normals.push_back(np2);
        Ponto*tp1 = new Ponto();
        Ponto*tp2 = new Ponto();
        Ponto*tp3 = new Ponto();
        tp1->x =0;
        tp1->y =0;
        tp1->z =0;
        tp2->x =0;
        tp2->y =0;
        tp2->z =0;
        tp3->x =0;
        tp3->y =0;
        tp3->z =0;
        textcoords.push_back(tp1);
        textcoords.push_back(tp2);
        textcoords.push_back(tp3);

        p1 = new Ponto();
        p1->x = (outside_radius + inside_radius * cos(beta)) * cos(alfa);
        p1->y = inside_radius * sin(beta);
        p1->z = (outside_radius + inside_radius * cos(beta)) * sin(alfa);

        p2 = new Ponto();
        p2->x = (outside_radius + inside_radius * cos(beta + b)) * cos(alfa);
        p2->y = inside_radius * sin(beta + b);
        p2->z = (outside_radius + inside_radius * cos(beta + b)) * sin(alfa);

        p3 = new Ponto();
        p3->x = (outside_radius + inside_radius * cos(beta)) * cos(alfa + a);
        p3->y = inside_radius * sin(beta);
        p3->z = (outside_radius + inside_radius * cos(beta)) * sin(alfa + a);

        pontos.push_back(p1);
        pontos.push_back(p2);
        pontos.push_back(p3);

        temp = new Ponto();
        temp2 = new Ponto();
        diffP(p2,p1,temp);
        diffP(p3,p1,temp2);
        np = new Ponto();
        crossP(temp,temp2,np);
        delete(temp);
        delete(temp2);
        normalizeP(np);
        np1 = new Ponto();
        np2 = new Ponto();
        copyP(np,np1);
        copyP(np,np2);
        normals.push_back(np);
        normals.push_back(np1);
        normals.push_back(np2);
        tp1 = new Ponto();
        tp2 = new Ponto();
        tp3 = new Ponto();
        tp1->x =0;
        tp1->y =0;
        tp1->z =0;
        tp2->x =0;
        tp2->y =0;
        tp2->z =0;
        tp3->x =0;
        tp3->y =0;
        tp3->z =0;
        textcoords.push_back(tp1);
        textcoords.push_back(tp2);
        textcoords.push_back(tp3);

            }
    }

    calcNormals(&pontos,&normals);
    prinTofile(&pontos,&normals,&textcoords,file);
}


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


Ponto* calcBezierPatch(vector<Ponto> controlPoints, int np, float u, float v){
    int n = 16;
    float aux[n][3], res[n][3];
    Ponto *p, *ponto;

    int j=0, w=0;
    for(int i=0; i<n; i++){
      aux[j][0] = controlPoints[indices[np][i]].x;
      aux[j][1] = controlPoints[indices[np][i]].y;
      aux[j][2] = controlPoints[indices[np][i]].z;
      j++;
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

void bezier_patches(int tesselation, const char* file, const char* file2) {
  std::ifstream f;
  f.open(file);

  int nBezier = 0;
  int ncontrolPoints = 0;
  int bezier = 0;
  int i,j;
  string aux,aux2;
  vector<Ponto> pontos1;


  if ( f.is_open()) {

      getline(f, aux);
      nBezier = stoi(aux);

      std::vector<string> tokens;

        for( i = 0; i < nBezier ;i++ ) {
          std::string line;
          getline(f,line);
          tokens = split(line, ' ');
          for( j = 0; j < nPatch ; j++ ) {
            indices[i][j] = stoi(tokens[j],nullptr);

          }
          for( int u = 0; u < tokens.size(); u++){
            indices[i][u] = stoi(tokens[u]);
          }

        }


    getline(f,aux2);
    ncontrolPoints = stoi(aux2);
    for( int z = 0; z < ncontrolPoints; z++ ){
      std::string line1;
      getline(f,line1);
      tokens = split(line1, ',');
      pontos1.reserve(ncontrolPoints);
      Ponto *p = new Ponto();
      (*p).x = stof(tokens[0],nullptr);
      (*p).y = stof(tokens[1],nullptr);
      (*p).z = stof(tokens[2],nullptr);
      pontos1.push_back(*p);
    }

  }

  f.close();


  vector<Ponto*> pontos;
  vector<Ponto*> normals;
  vector<Ponto*> textcoords;
  float u1, v1, u2, v2, inc = 1.0/tesselation;
  Ponto* res[nBezier][4];

  for(int i=0; i<nBezier; i++){
    for(int j=0; j<tesselation; j++){
      for(int w=0; w<tesselation; w++){
          u1 = j*inc;
          v1 = w*inc;
          u2 = (j+1)*inc;
          v2 = (w+1)*inc;

          res[i][0] = calcBezierPatch(pontos1, i, u1, v1);
          res[i][1] = calcBezierPatch(pontos1, i, u2, v1);
          res[i][2] = calcBezierPatch(pontos1, i, u1, v2);
          res[i][3] = calcBezierPatch(pontos1, i, u2,v2);


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

          pontos.push_back(p0);
          pontos.push_back(p1);
          pontos.push_back(p3);

          Ponto* temp = new Ponto();
          Ponto* temp2 = new Ponto();
          diffP(p1,p0,temp);
          diffP(p3,p0,temp2);
          Ponto* np = new Ponto();
          crossP(temp,temp2,np);
          delete(temp);
          delete(temp2);
          normalizeP(np);
          Ponto* np1 = new Ponto();
          Ponto* np2 = new Ponto();
          copyP(np,np1);
          copyP(np,np2);
          normals.push_back(np);
          normals.push_back(np1);
          normals.push_back(np2);
          Ponto*tp1 = new Ponto();
          Ponto*tp2 = new Ponto();
          Ponto*tp3 = new Ponto();
          tp1->x =0;
          tp1->y =0;
          tp1->z =0;
          tp2->x =0;
          tp2->y =0;
          tp2->z =0;
          tp3->x =0;
          tp3->y =0;
          tp3->z =0;
          textcoords.push_back(tp1);
          textcoords.push_back(tp2);
          textcoords.push_back(tp3);

          pontos.push_back(p0);
          pontos.push_back(p3);
          pontos.push_back(p2);

           temp = new Ponto();
           temp2 = new Ponto();
          diffP(p3,p0,temp);
          diffP(p2,p0,temp2);
           np = new Ponto();
          crossP(temp,temp2,np);
          delete(temp);
          delete(temp2);
          normalizeP(np);
           np1 = new Ponto();
           np2 = new Ponto();
          copyP(np,np1);
          copyP(np,np2);
          normals.push_back(np);
          normals.push_back(np1);
          normals.push_back(np2);
          tp1 = new Ponto();
          tp2 = new Ponto();
          tp3 = new Ponto();
          tp1->x =0;
          tp1->y =0;
          tp1->z =0;
          tp2->x =0;
          tp2->y =0;
          tp2->z =0;
          tp3->x =0;
          tp3->y =0;
          tp3->z =0;
          textcoords.push_back(tp1);
          textcoords.push_back(tp2);
          textcoords.push_back(tp3);
      }
    }
  }

  calcNormals(&pontos,&normals);
  prinTofile(&pontos,&normals,&textcoords,file2);


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
printf ( " |   ‣ Bezier                                                                                       |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator bezier <tesselation> <INPUT_FILE> <OUTPUT_FILE>                              |\n");
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
    if (argc != 5)
      printf("Invalid input. Try -help for help.\n");
    else {
      folder.append(argv[4]);
      const char* file = folder.c_str();
      bezier_patches(stoi(argv[2]), argv[3], file );
      printf("9\n");
    }
  }
  else if (!str.compare("-help"))
     help();
  else printf("Command not found. Try -help for help.\n");

  return 1;

}

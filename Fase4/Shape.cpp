#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <cstdlib>

#include "headers/Shape.h"





int Shape::getNVertices(){
    return this->n_vertices;
}


Shape::Shape(vector<Ponto*>* pontos, vector<Ponto*>* normals, vector<Ponto*>* textcoords, const char* texturefile){
  this->n_vertices = pontos->size();


  int asa;
float m,n,c;

	float * array_vertexs = (float *) malloc(sizeof(float) * 3 * n_vertices);
	float * array_normal = (float *) malloc(sizeof(float) * 3 * n_vertices);
	vector<float> textures;

  vector<Ponto*>::iterator point_it;
    int vertex = 0;
    vertex=0;
    for(point_it = pontos->begin(); point_it != pontos->end(); point_it++){
        Ponto * p = (*point_it);
        array_vertexs[vertex*3 + 0] = p->x;
        array_vertexs[vertex*3 + 1] = p->y;
        array_vertexs[vertex*3 + 2] = p->z;

        vertex++;
    }
    vertex = 0;
    for(point_it = normals->begin(); point_it != normals->end(); point_it++){
        Ponto * p = (*point_it);
        array_normal[vertex*3 + 0] = p->x;
        array_normal[vertex*3 + 1] = p->y;
        array_normal[vertex*3 + 2] = p->z;

        vertex++;
    }
    vertex=0;
    for(point_it = textcoords->begin(); point_it != textcoords->end(); point_it++){
      Ponto * p = (*point_it);
      textures.push_back(p->x);
      textures.push_back(p->y);

      vertex++;
    }


   // for (asa=0;asa<n_vertices*3;asa+=3){
   //   printf("array_vertexs %d : %f,%f,%f\n",asa/3,array_vertexs[asa],array_vertexs[asa+1],array_vertexs[asa+2] );
   // }
   // for (asa=0;asa<n_vertices*3;asa+=3){
   //   printf("array_normal %d : %f,%f,%f\n",asa/3,array_normal[asa],array_normal[asa+1],array_normal[asa+2] );
   // }


   cleanVector(pontos);
   cleanVector(normals);

   glGenBuffers(3,buffer);

    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex * 3,array_vertexs,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex * 3,array_normal,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(float), &(textures[0]), GL_STATIC_DRAW);

    free(array_vertexs);
    free(array_normal);

    if (texturefile != NULL && texturefile[0] != '\0') {
            loadImage(texturefile);
            has_texture = true;
        }
        else{
            has_texture = false;
        }
}

void Shape::loadImage(const char* filename){
  if (!filename)
        return;

        unsigned int t, tw, th;
        unsigned char *texData = NULL;

        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

        ilGenImages(1, &t);
        ilBindImage(t);
        ILboolean a = ilLoadImage((ILstring)filename);
        tw = ilGetInteger(IL_IMAGE_WIDTH);
        th = ilGetInteger(IL_IMAGE_HEIGHT);
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        texData = ilGetData();

        glGenTextures(1, &textura);

        glBindTexture(GL_TEXTURE_2D, textura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

}


void Shape::addMaterial(Material* m){
  this->materials.push_back(m);
}

void Shape::draw(){


vector<Material*>::iterator it2;
for(it2 = materials.begin(); it2 != materials.end(); it2++){
  (*it2)->draw();
}

glBindTexture(GL_TEXTURE_2D, textura);

glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
glVertexPointer(3,GL_FLOAT,0,0);

glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
glNormalPointer(GL_FLOAT,0,0);

if (has_texture) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
  glTexCoordPointer(2, GL_FLOAT, 0, 0);
}

glDrawArrays(GL_TRIANGLES, 0, n_vertices * 3);

if (!has_texture) {
  glBindTexture(GL_TEXTURE_2D, 0);
}

}
void Shape::print(){
  cout << "num_materiais " << materials.size()
    << "textura " << textura
    << "has texture " << has_texture
    << "num vertices  " << n_vertices << endl;
    cout.flush();
    int i;
    for (i=0;i<3;i++){
      cout << "buffer pointer " << i << buffer[i] << endl;
      cout.flush();
    }
}

void Shape::cleanVector(vector<Ponto*> * limpar){
    vector<Ponto*>::iterator it;
    for(it = limpar->begin(); it != limpar->end(); it++){
        delete((*it));
    }
    delete(limpar);
}

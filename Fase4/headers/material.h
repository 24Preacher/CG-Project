#ifndef material_h
#define material_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <stdlib.h>
#include <GL/glut.h>
#endif


class Material {

 private:

    int type; // 0 specular, 1 emissive ,2 difusse, 3 ambient
    float color[4];
    float shininess;

  public:

    Material(int, float, float*);
    void draw();


};


#endif

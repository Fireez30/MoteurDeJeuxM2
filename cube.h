#ifndef CUBE_H
#define CUBE_H
#include "baseobject.h"

 class Cube : public BaseObject, protected QOpenGLFunctions
 {

public :
     Cube();
     void CreateGeometry();
     void Render(QOpenGLShaderProgram *program);
 };

#endif // CUBE_H

#ifndef CUBE_H
#define CUBE_H
#include "baseobject.h"

 class Cube : BaseObject
 {

public :
     void CreateGeometry();
     void Render(QOpenGLShaderProgram *program);
 };

#endif // CUBE_H

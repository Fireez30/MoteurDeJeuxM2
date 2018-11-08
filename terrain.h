#ifndef TERRAIN_H
#define TERRAIN_H
#include "baseobject.h"

 class Terrain : BaseObject, protected QOpenGLFunctions
 {

public :
     void CreateGeometry();
     void Render(QOpenGLShaderProgram *program);
 };

#endif // TERRAIN_H

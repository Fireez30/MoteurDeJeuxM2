#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>
#include "geometryengine.h"

using namespace std;

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

class BaseObject
{
protected:
    QQuaternion rotation;
    QVector3D position;
    GeometryEngine geometry;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    vector<BaseObject> childs;
    BaseObject* parent;

public :
    BaseObject();
    BaseObject(QQuaternion rot,QVector3D geo);
    ~BaseObject();
    void SetRotation(QQuaternion r);
    QQuaternion GetRotation();
    void SetPosition(QVector3D p);
    QVector3D GetPosition();
    void Rotate(QQuaternion r);
    void Translate(QVector3D v);
    void SetChilds(vector<BaseObject> v);
    vector<BaseObject> GetChilds();
    BaseObject GetChildAtIndex(int i);
    BaseObject* GetParent();
    void SetParent(BaseObject* b);
    void SetChildAtIndex(BaseObject c, int i);
    void CreateGeometry();
    void Render(QOpenGLShaderProgram *program);
    void UpdatePositionInSpace();
};

#endif // BASEOBJECT_H
#include <QVector2D>
#include <QVector3D>
#include <GL/gl.h>
#include <QQuaternion>
#include "geometryengine.h"
#include "baseobject.h"
#include <QImage>


BaseObject::BaseObject() : indexBuf(QOpenGLBuffer::IndexBuffer){
    initializeOpenGLFunctions();
    rotation = QQuaternion(0,0,0,0);
    position = QVector3D(0,0,0);
    id = 0;
    arrayBuf.create();
    indexBuf.create();
}

BaseObject::BaseObject(QQuaternion rot,QVector3D geo) : indexBuf(QOpenGLBuffer::IndexBuffer){
    initializeOpenGLFunctions();
    rotation = rot;
    position = geo;
    arrayBuf.create();
    indexBuf.create();
}

BaseObject::~BaseObject(){
    arrayBuf.destroy();
    indexBuf.destroy();
}

void BaseObject::SetRotation(QQuaternion r){
    rotation = r;
}

QQuaternion BaseObject::GetRotation(){
    return rotation;
}

void BaseObject::SetPosition(QVector3D p){
    position = p;
}

QVector3D BaseObject::GetPosition(){
    return position;
}

void BaseObject::Rotate(QQuaternion r){
    rotation *= r;
}

void BaseObject::Translate(QVector3D v){
    position += v;
}

void BaseObject::SetChilds(vector<BaseObject> v){
    childs = v;
}

vector<BaseObject> BaseObject::GetChilds(){
    return childs;
}

BaseObject BaseObject::GetChildAtIndex(int i){
    if (i < childs.size())
        return childs[i];
}

void BaseObject::SetChildAtIndex(BaseObject c, int i){
    if (i < childs.size()){
        childs[i] = c;
    }
}

BaseObject* BaseObject::GetParent(){
    return parent;
}
void BaseObject::SetParent(BaseObject* b){
    parent = b;
}

void BaseObject::UpdatePositionInSpace(){
    rotation *= parent->GetRotation();
    position += parent->GetPosition();
    for (int i = 0; i < childs.size(); i++){
        childs[i].UpdatePositionInSpace();
    }
}

void BaseObject::Render(QOpenGLShaderProgram *program)
{
    //Render stuff here (render the loaded mesh)
    for (int i = 0; i < childs.size(); i++){
        childs[i].Render(program);
    }
}

void BaseObject::CreateGeometry(){
    //Create geometry stuff here (load the object mesh)
    for (int i = 0; i < childs.size(); i++){
        childs[i].CreateGeometry();
    }
}

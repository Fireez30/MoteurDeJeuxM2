#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>
#include "geometryengine.h"
#include "baseobject.h"
#include <QImage>


BaseObject::BaseObject(){
    rotation = QQuaternion(0,0,0,0);
    position = QVector3D(0,0,0);
    arrayBuf.create();
    indexBuf.create();
}

BaseObject::BaseObject(QQuaternion rot,QVector3D geo){
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

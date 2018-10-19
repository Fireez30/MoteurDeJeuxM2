#include "quadtree.h"
#include <QVector3D>

using namespace std;

void QuadTree::computerCenter(){
    float sumx,sumy,sumz = 0;
    for (int i = 0; i < corners.size(); i++){
        sumx += corners[i].x();
        sumy += corners[i].z();
        sumz += corners[i].z();
    }

    center = QVector3D(sumx/corners.size(),sumy/corners.size(),sumz/corners.size());
}


void QuadTree::setLeftTopCorner(QVector3D q)
{
    corners[0] = q;
    corners[1] = QVector3D(q.x()+h,q.y(),q.z());
    corners[2] = QVector3D(q.x(),q.y()+w,q.z());
    corners[3] = QVector3D(q.x()+h,q.y()+w,q.z());
    computerCenter();
}


QuadTree::QuadTree(int i,float he,float we,QVector3D q) :
    id(i),
    h(he),
    w(we)
{
   setLeftTopCorner(q);
}

QuadTree::~QuadTree()
{
    corners.clear();
    childs.clear();
}

QVector3D QuadTree::getCornerAtIndex(int i)
{
    return corners[i];
}

vector<QVector3D> QuadTree::getCorners()
{
    return corners;
}


float QuadTree::getHeight()
{
    return h;
}

float QuadTree::getWidth()
{
    return w;
}

void QuadTree::setHeight(float he)
{
    h = he;
}

void QuadTree::setWidth(float we)
{
    w = we;
}


QVector3D QuadTree::getCenter(){
    return center;
}

void QuadTree::setChilds(std::vector<QuadTree> c)
{
    childs.clear();
    for (int i = 0;i < c.size(); i++){
        childs.push_back(c[i]);
    }
}

void QuadTree::setChildAtIndex(QuadTree q, int i)
{
    childs[i] = q;
}

std::vector<QuadTree> QuadTree::getChilds()
{
    return childs;
}

QuadTree QuadTree::getChildsAtIndex(int i)
{
    return childs[i];
}

int QuadTree::getId()
{
    return id;
}

void QuadTree::ComputeDivision(){
    childs.clear();
    childs.push_back(QuadTree(0,h/2,w/2,getCornerAtIndex(0)));
    childs.push_back(QuadTree(1,h/2,w/2,QVector3D(corners[1].x()+h/2,corners[1].y(),corners[1].z())));
    childs.push_back(QuadTree(2,h/2,w/2,QVector3D(corners[1].x(),corners[1].y()+w/2,corners[1].z())));
    childs.push_back(QuadTree(3,h/2,w/2,getCenter()));
}

void QuadTree::DiviseAtLevel(int depth)
{

}

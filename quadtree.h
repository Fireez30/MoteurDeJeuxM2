#ifndef QUADTREE_H
#define QUADTREE_H

#include <QVector2D>
#include <QVector3D>

class QuadTree
{
    std::vector<QVector3D> corners;
    QVector3D center;
    float h;
    float w;
    std::vector<QuadTree> childs;
    int id;

public :
    QuadTree(int id,float he,float we,QVector3D q);
    ~QuadTree();
    QVector3D getCornerAtIndex(int i);
    std::vector<QVector3D> getCorners();
    void setLeftTopCorner(QVector3D q);
    void setCorners(std::vector<QVector3D> v);
    float getHeight();
    float getWidth();
    void setHeight(float h);
    void setWidth(float w);
    void computerCenter();
    QVector3D getCenter();
    void setChilds(std::vector<QuadTree> c);
    void setChildAtIndex(QuadTree q, int id);
    std::vector<QuadTree> getChilds();
    QuadTree getChildsAtIndex(int id);
    int getId();
    void ComputeDivision();
    void DiviseAtLevel(int depth);
};

#endif // QUADTREE_H

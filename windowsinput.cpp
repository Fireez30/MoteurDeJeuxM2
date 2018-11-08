#include "windowsinput.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QtWidgets>
#include <QGridLayout>
#include <math.h>
#include <iostream>
#include <QTime>

windowsinput::windowsinput(QWidget *p) : widget(0,1,0), widget2(0,10,1), widget3(0,100,2), widget4(0,1000,3), w(0),QOpenGLWidget(p){

}

void windowsinput::showF(){
    QGridLayout *lay = new QGridLayout();
    lay->addWidget(&widget);
    connect(this,SIGNAL(timerSeason(int)),&widget,SLOT(changeSeason(int)));
    setMinimumSize(QSize(800,800));
    setLayout(lay);
    show();
    saison.start(3000,this);
}

windowsinput::~windowsinput(){
}

void windowsinput::timerEvent(QTimerEvent *)
{
    emit(timerSeason(0));
}

void windowsinput::keyPressEvent (QKeyEvent * event)
{
    if(event->key() == Qt::Key_Q){
           widget.x++;
           widget2.x++;
           widget3.x++;
           widget4.x++;
    }

    if(event->key() == Qt::Key_D){
        widget.x--;
        widget2.x--;
        widget3.x--;
        widget4.x--;
 }
    if(event->key() == Qt::Key_Z){
        widget.y--;
        widget2.y--;
        widget3.y--;
        widget4.y--;
 }
    if(event->key() == Qt::Key_S){
        widget.y++;
        widget2.y++;
        widget3.y++;
        widget4.y++;
 }


    if(event->key() == Qt::Key_W){
        widget.z++;
        widget2.z++;
        widget3.z++;
        widget4.z++;
 }

    if(event->key() == Qt::Key_X){
        widget.z--;
        widget2.z--;
        widget3.z--;
        widget4.z--;
 }

    if(event->key() == Qt::Key_U){
        widget.angularSpeed = 0;
        widget2.angularSpeed = 0;
        widget3.angularSpeed = 0;
        widget4.angularSpeed = 0;
 }

    if (event->key() == Qt::Key_Up){
        widget.angularSpeed += 0.1;
        widget2.angularSpeed += 0.1;
        widget3.angularSpeed += 0.1;
        widget4.angularSpeed += 0.1;
    }

    if (event->key() == Qt::Key_Down){
        widget.angularSpeed -= 0.1;
        widget2.angularSpeed -= 0.1;
        widget3.angularSpeed -= 0.1;
        widget4.angularSpeed -= 0.1;
    }
    if(event->key() == Qt::Key_Right){
        widget.rotationAxis = QVector3D(0,1,0);
        widget.angularSpeed = 0.5;
        widget2.rotationAxis = QVector3D(0,1,0);
        widget2.angularSpeed = 0.5;
        widget3.rotationAxis = QVector3D(0,1,0);
        widget3.angularSpeed = 0.5;
        widget4.rotationAxis = QVector3D(0,1,0);
        widget4.angularSpeed = 0.5;
    }

    if(event->key() == Qt::Key_Left){
        widget.rotationAxis = QVector3D(0,-1,0);
        widget.angularSpeed = 0.5;
        widget2.rotationAxis = QVector3D(0,-1,0);
        widget2.angularSpeed = 0.5;
        widget3.rotationAxis = QVector3D(0,-1,0);
        widget3.angularSpeed = 0.5;
        widget4.rotationAxis = QVector3D(0,-1,0);
        widget4.angularSpeed = 0.5;
    }
}

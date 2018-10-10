#ifndef WINDOWSINPUT_H
#define WINDOWSINPUT_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTime>
#include "mainwidget.h"

class windowsinput : public QOpenGLWidget, protected QOpenGLFunctions
{

public :
    MainWidget widget;
    MainWidget widget2;
    MainWidget widget3;
    MainWidget widget4;

    QWidget w;
    void keyPressEvent ( QKeyEvent * event ) override;

    void showF();
    windowsinput(QWidget *p);
    ~windowsinput();
};

#endif // WINDOWSINPUT_H

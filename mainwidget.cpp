/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"

#include <QMouseEvent>
#include <GL/gl.h>
#include <QKeyEvent>
#include <QPainter>
#include <QElapsedTimer>
#include <math.h>
#include <iostream>
#include <QVector3D>
#include <QTime>
#include "cube.h"

bool start = true;
int initial_time = time (NULL);
int final_time,frame_count;
int last_fps = 0;

MainWidget::MainWidget(QWidget *parent,int maxfps,int saison) :
    QOpenGLWidget(parent),
    texture(0),
    angularSpeed(0),
    actualSeason(saison)
{
    std::cout << "debut constructeur main widget" << std::endl;
    if (maxfps == 0)
        max_fps = 1;
    else
        max_fps = maxfps;
    et.start();
    v = std::vector<QVector3D>();
    v.push_back(QVector3D(0,200,0));
    v.push_back(QVector3D(200,0,0));
    v.push_back(QVector3D(0,0,200));
    v.push_back(QVector3D(200,200,0));
    //initializeGL();
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    doneCurrent();
}

//! [0]



void MainWidget::keyPressEvent (QKeyEvent * event)
{
    if(event->key() == Qt::Key_Q)
           x++;

    if(event->key() == Qt::Key_D)
           x--;

    if(event->key() == Qt::Key_Z)
          y--;

    if(event->key() == Qt::Key_S)
          y++;

    if(event->key() == Qt::Key_W)
          z++;

    if(event->key() == Qt::Key_X)
          z--;

    if(event->key() == Qt::Key_U)
          angularSpeed = 0;

    if(event->key() == Qt::Key_Right){
        rotationAxis = QVector3D(0,1,0);
        angularSpeed = 0.5;
    }

    if(event->key() == Qt::Key_Left){
        rotationAxis = QVector3D(0,-1,0);
        angularSpeed = 0.5;
    }
}

void MainWidget::changeSeason(int a)
{
    actualSeason++;
    actualSeason = actualSeason %4;//cycle through 4 saisons
    update();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;


        frame_count++;
        final_time = time(NULL);
        if (final_time - initial_time > 0)
        {
            //display
            last_fps = frame_count/ (final_time - initial_time);
            frame_count = 0;
            initial_time = final_time;
            std::cout << "Fps : " << last_fps << std::endl;
        }

        // Render text
        //timer.start(1000/max_fps,this);
        // Request an update
        et.restart();


    }
            update();
}
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0, 1);

   // glOrtho(-17.0,17.0,-17.0,17.0,3.0,7.0);
    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]
    geometries = new GeometryEngine;
    //scene = Cube();
    //scene.CreateGeometry();//start with the basic level of details
    rotation = QQuaternion::fromAxisAndAngle(1,0,0,135);
    // Use QBasicTimer because its faster than QTimer

    timer.start(1000/max_fps, this);
}
//! [3]
void MainWidget::initShaders()
{


    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
    {
        std::cout << "Erreur lors de la compilation du vertex shader" << std::endl;
        close();
    }

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
    {
        std::cout << "Erreur lors de la compilation du fragment shader" << std::endl;
        close();
    }

    // Link shader pipeline
    if (!program.link())
    {
        std::cout << "Erreur lors du link" << std::endl;
        close();
    }

    // Bind shader pipeline for use
    if (!program.bind())
    {
        std::cout << "Erreur lors du bind" << std::endl;
        close();
    }
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage("hmap3.png"));

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 100.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]


void MainWidget::paintGL()
{

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();
//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(x, y, z);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]
    program.setUniformValue("basecolor",QVector4D(v[actualSeason][0]/255, v[actualSeason][1]/255, v[actualSeason][2]/255, 1));
    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    geometries->drawMeshGeometry(&program);
    //scene.Render(&program);//old version of this is drawTerrainGeometry();
}

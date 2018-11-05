QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    windowsinput.cpp \
    quadtree.cpp \
    scenegraphnode.cpp \
    baseobject.cpp \
    terrain.cpp \
    cube.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    windowsinput.h \
    quadtree.h \
    scenegraphnode.h \
    baseobject.h \
    terrain.h \
    cube.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=

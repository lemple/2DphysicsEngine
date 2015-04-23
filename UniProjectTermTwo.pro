#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T11:25:45
#
#-------------------------------------------------
QT       += core
QT       -= gui
TARGET = 2DphysicsEngine
CONFIG   += console
CONFIG   -= app_bundle
#CONFIG += c++11
#CONFIG += -std=gnu++0x

TEMPLATE = app
INCLUDEPATH += /usr/local/include \
               /src/

QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)
QMAKE_CXXFLAGS += -std=c++0x

LIBS += -lGLEW
LIBS += $$system(sdl2-config --libs)
LIBS += -lSDL2


HEADERS += src/Randini/GLSLProgram.h \
src/Randini/Camera2D.h \
src/Randini/Errors.h \
src/Randini/GLTexture.h \
src/Randini/ImageLoader.h \
src/Randini/InputControl.h \
src/Randini/IOManager.h \
src/Randini/picoPNG.h \
src/Randini/Randini.h \
src/Randini/ResourceManager.h \
src/Randini/Sprite.h \
src/Randini/SpriteLoader.h \
src/Randini/TextureCache.h \
src/Randini/Timer.h \
src/Randini/Vertex.h \
src/Randini/Window.h \
src/Uni/Ball.h \
src/Uni/BallControl.h \
src/Uni/BallRenderer.h \
src/Uni/BallGrid.h \
src/Uni/MainGame.h
SOURCES += src/Uni/main.cpp \
src/Uni/Ball.cpp \
src/Uni/BallControl.cpp \
src/Uni/BallRenderer.cpp \
src/Uni/BallGrid.cpp \
src/Uni/MainGame.cpp \
src/Randini/GLSLProgram.cpp \
src/Randini/Camera2D.cpp \
src/Randini/Errors.cpp \
src/Randini/ImageLoader.cpp \
src/Randini/InputControl.cpp \
src/Randini/IOManager.cpp \
src/Randini/picoPNG.cpp \
src/Randini/Randini.cpp \
src/Randini/ResourceManager.cpp \
src/Randini/Sprite.cpp \
src/Randini/SpriteLoader.cpp \
src/Randini/TextureCache.cpp \
src/Randini/Timer.cpp \
src/Randini/Window.cpp

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
               src/ \
               Include/ \
               Include/BallGame \
               Include/Randini

QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)
QMAKE_CXXFLAGS += -std=c++0x

LIBS += -lGLEW
LIBS += $$system(sdl2-config --libs)
LIBS += -lSDL2


HEADERS += Include/Randini/GLSLProgram.h \
Include/Randini/Camera2D.h \
Include/Randini/Errors.h \
Include/Randini/GLTexture.h \
Include/Randini/ImageLoader.h \
Include/Randini/InputControl.h \
Include/Randini/IOManager.h \
Include/Randini/picoPNG.h \
Include/Randini/Randini.h \
Include/Randini/ResourceManager.h \
Include/Randini/SpriteLoader.h \
Include/Randini/TextureCache.h \
Include/Randini/Timer.h \
Include/Randini/Vertex.h \
Include/Randini/Window.h \
Include/BallGame/Ball.h \
Include/BallGame/BallControl.h \
Include/BallGame/BallRenderer.h \
Include/BallGame/BallGrid.h \
Include/BallGame/MainGame.h
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
src/Randini/SpriteLoader.cpp \
src/Randini/TextureCache.cpp \
src/Randini/Timer.cpp \
src/Randini/Window.cpp

#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T16:05:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChimpOut-Editor
TEMPLATE = app

INCLUDEPATH += $$PWD/include

SOURCES += src/main-editor.cpp\
        src/EditorMainWindow.cpp

HEADERS  += include/EditorMainWindow.h

FORMS    += src/EditorMainWindow.ui

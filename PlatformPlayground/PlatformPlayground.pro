TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf
#LIBS += -lSDL2 -ldl -lpthread

DESTDIR = $$PWD/bin
TARGET = DSMaze

SOURCES += main.cpp \
    SDLUtils.cpp

HEADERS += \
    cleanup.h \
    SDLUtils.h

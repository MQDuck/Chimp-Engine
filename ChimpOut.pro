TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf
#LIBS += -lSDL2 -ldl -lpthread

DESTDIR = $$PWD
TARGET = ChimpOut

SOURCES += main.cpp \
    SDLUtils.cpp \
    ChimpObject.cpp \
    ChimpMobile.cpp \
    ChimpCharacter.cpp \
    ChimpGame.cpp

HEADERS += \
    cleanup.h \
    SDLUtils.h \
    ChimpObject.h \
    ChimpConstants.h \
    ChimpMobile.h \
    ChimpCharacter.h \
    ChimpTile.h \
    ChimpGame.h \
    Coordinate.h \
    ChimpDefines.h

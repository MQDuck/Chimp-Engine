TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -ltinyxml2 -llua
#LIBS += -lSDL2 -ldl -lpthread

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

CONFIG += link_pkgconfig
PKGCONFIG += x11

DESTDIR = $$PWD
TARGET = ChimpOut

SOURCES += main.cpp \
    SDLUtils.cpp \
    chimp/ChimpCharacter.cpp \
    chimp/ChimpGame.cpp \
    chimp/ChimpMobile.cpp \
    chimp/ChimpObject.cpp \
    chimp/loadLevel.cpp \
    chimp/ChimpLuaInterface.cpp \
    runlua.cpp

HEADERS += \
    cleanup.h \
    SDLUtils.h \
    ChimpConstants.h \
    chimp/ChimpCharacter.h \
    chimp/ChimpGame.h \
    chimp/ChimpMobile.h \
    chimp/ChimpObject.h \
    chimp/ChimpStructs.h \
    chimp/ChimpTile.h \
    chimp/loadLevel.h \
    chimp/ChimpLuaInterface.h \
    runlua.h

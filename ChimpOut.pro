TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2 -llua
#LIBS += -lSDL2 -ldl -lpthread

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_RELEASE += -O3 -mtune=generic

CONFIG += link_pkgconfig
PKGCONFIG += x11

DESTDIR = $$PWD
TARGET = ChimpOut

SOURCES += main.cpp \
    chimp/ChimpCharacter.cpp \
    chimp/ChimpGame.cpp \
    chimp/ChimpMobile.cpp \
    chimp/ChimpObject.cpp \
    chimp/ChimpLuaInterface.cpp

HEADERS += \
    cleanup.h \
    ChimpConstants.h \
    chimp/ChimpCharacter.h \
    chimp/ChimpGame.h \
    chimp/ChimpMobile.h \
    chimp/ChimpObject.h \
    chimp/ChimpStructs.h \
    chimp/ChimpTile.h \
    chimp/ChimpLuaInterface.h

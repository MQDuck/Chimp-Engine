TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -ltinyxml2
#LIBS += -lSDL2 -ldl -lpthread

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

CONFIG += link_pkgconfig
PKGCONFIG += x11

DESTDIR = $$PWD
TARGET = ChimpOut

SOURCES += main.cpp \
    SDLUtils.cpp \
    ChimpObject.cpp \
    ChimpMobile.cpp \
    ChimpCharacter.cpp \
    ChimpGame.cpp \
    loadLevel.cpp

HEADERS += \
    cleanup.h \
    SDLUtils.h \
    ChimpObject.h \
    ChimpConstants.h \
    ChimpMobile.h \
    ChimpCharacter.h \
    ChimpTile.h \
    ChimpGame.h \
    ChimpStructs.h \
    loadLevel.h

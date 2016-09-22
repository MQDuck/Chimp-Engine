TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_RELEASE += -O3 -mtune=generic

CONFIG += link_pkgconfig

DESTDIR = $$PWD
TARGET = ChimpOut
SOURCES += main.cpp \
    chimp/ChimpCharacter.cpp \
    chimp/ChimpGame.cpp \
    chimp/ChimpMobile.cpp \
    chimp/ChimpObject.cpp \
    chimp/ChimpLuaInterface.cpp \
    tinyxml2.cpp

HEADERS += \
    cleanup.h \
    ChimpConstants.h \
    chimp/ChimpCharacter.h \
    chimp/ChimpGame.h \
    chimp/ChimpMobile.h \
    chimp/ChimpObject.h \
    chimp/ChimpStructs.h \
    chimp/ChimpTile.h \
    chimp/ChimpLuaInterface.h \
    tinyxml2.h

linux: LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2 -llua
linux: PKGCONFIG += x11

win32: LIBS += -LC:/libraries/SDL/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

win32: INCLUDEPATH += C:/libraries/SDL/include
win32: DEPENDPATH += C:/libraries/SDL/include

win32: LIBS += -LC:/libraries/Lua/lib/ -llua53

win32: INCLUDEPATH += C:/libraries/Lua/include
win32: DEPENDPATH += C:/libraries/Lua/include

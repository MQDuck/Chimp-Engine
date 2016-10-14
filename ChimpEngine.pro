TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_RELEASE += -O3 -mtune=generic

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/chimp/include

CONFIG += link_pkgconfig

DESTDIR = $$PWD
TARGET = ChimpEngine
SOURCES += src/main.cpp \
    chimp/src/ChimpCharacter.cpp \
    chimp/src/ChimpGame.cpp \
    chimp/src/ChimpLuaInterface.cpp \
    chimp/src/ChimpMobile.cpp \
    chimp/src/ChimpObject.cpp \
    src/tinyxml2.cpp

HEADERS += \
    chimp/include/ChimpCharacter.h \
    chimp/include/ChimpGame.h \
    chimp/include/ChimpLuaInterface.h \
    chimp/include/ChimpMobile.h \
    chimp/include/ChimpObject.h \
    chimp/include/ChimpStructs.h \
    chimp/include/ChimpTile.h \
    include/ChimpConstants.h \
    include/cleanup.h \
    include/tinyxml2.h

linux: LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2 -llua
linux: PKGCONFIG += x11

win32: LIBS += -LC:/libraries/SDL/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

win32: INCLUDEPATH += C:/libraries/SDL/include
win32: DEPENDPATH += C:/libraries/SDL/include

win32: LIBS += -LC:/libraries/Lua/lib/ -llua53

win32: INCLUDEPATH += C:/libraries/Lua/include
win32: DEPENDPATH += C:/libraries/Lua/include

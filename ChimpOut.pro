TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_RELEASE += -O3 -mtune=generic

INCLUDEPATH += $$PWD/include

CONFIG += link_pkgconfig

DESTDIR = $$PWD
TARGET = ChimpOut
SOURCES += src/main.cpp \
    src/ChimpCharacter.cpp \
    src/ChimpGame.cpp \
    src/ChimpLuaInterface.cpp \
    src/ChimpMobile.cpp \
    src/ChimpObject.cpp \
    src/tinyxml2.cpp

HEADERS += \
    include/chimp/ChimpCharacter.h \
    include/chimp/ChimpGame.h \
    include/chimp/ChimpLuaInterface.h \
    include/chimp/ChimpMobile.h \
    include/chimp/ChimpObject.h \
    include/chimp/ChimpStructs.h \
    include/chimp/ChimpTile.h \
    include/cleanup.h \
    include/tinyxml2.h \
    include/ChimpConstants.h

linux: LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2 -llua
linux: PKGCONFIG += x11

win32: LIBS += -LC:/libraries/SDL/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

win32: INCLUDEPATH += C:/libraries/SDL/include
win32: DEPENDPATH += C:/libraries/SDL/include

win32: LIBS += -LC:/libraries/Lua/lib/ -llua53

win32: INCLUDEPATH += C:/libraries/Lua/include
win32: DEPENDPATH += C:/libraries/Lua/include

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS+= -L/usr/local/lib -lassimp

INCLUDEPATH += /usr/local/include

SOURCES += main.cpp



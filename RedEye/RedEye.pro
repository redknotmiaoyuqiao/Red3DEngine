TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt



win32
{

}

unix:!macx
{
#    LIBS += -lglfw
#    LIBS += -lGLEW
#    LIBS += -lGL
#    LIBS += -lSOIL
#    LIBS += -lassimp
}

unix:macx
{
    LIBS+= -framework opengl
    LIBS+= -framework Cocoa -framework IOKit -framework CoreVideo

    LIBS+= -L/usr/local/lib -lglfw3
    LIBS+= -L/usr/local/lib -lGLEW
    LIBS+= -L/usr/local/lib -lassimp
    LIBS+= -L/usr/local/lib -lfreetype
}

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/freetype2
INCLUDEPATH += glm/

SOURCES += main.cpp \
    RedGL/GLProgram.cpp \
    RedGL/GLShader.cpp \
    Engine/Engine.cpp \
    RedGL/GLVAO.cpp \
    Component/Camera.cpp \
    Engine/Screen.cpp \
    File/IMAGE/stb_image.cpp \
    File/ImageFile.cpp \
    RedGL/GLRenderTarget.cpp

HEADERS += \
    DEBUG/Debug.hpp \
    RedGL/RedGL.hpp \
    SHADER/Shader.hpp \
    SHADER/Header.hpp \
    Engine/Engine.hpp \
    Component/Component.hpp \
    File/File.hpp \
    File/IMAGE/stb_image.h

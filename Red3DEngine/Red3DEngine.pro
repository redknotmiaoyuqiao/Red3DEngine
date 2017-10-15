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
    QMAKE_MAC_SDK = macosx10.13
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
    GL/GLProgram.cpp \
    GL/GLShader.cpp \
    GL/GLTexture.cpp \
    GL/GLVAO.cpp \
    GL/TextFile.cpp \
    Engine/Mesh.cpp \
    Engine/Model.cpp \
    Engine/Light.cpp \
    Engine/Camera.cpp \
    Engine/Material.cpp \
    Engine/PBRLight.cpp \
    Engine/PBRMaterial.cpp \
    GL/ImageFile.cpp \
    Engine/SkyBox.cpp \
    GL/GLCubeMapTexture.cpp \
    UI/UIText.cpp \
    UI/UICharacter.cpp \
    Engine/Screen.cpp \
    IMAGE/stb_image.cpp

HEADERS += \
    GL/File.hpp \
    GL/RedGL.hpp \
    Engine/Engine.hpp \
    DEBUG/Debug.hpp \
    Engine/RedGame.hpp \
    Engine/RedScript.hpp \
    RedGameEngine.hpp \
    SHADER/Shader.hpp \
    UI/UI.hpp \
    IMAGE/stb_image.h

DISTFILES += \

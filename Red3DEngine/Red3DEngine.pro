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
}

INCLUDEPATH += /usr/local/include
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
    SOIL/image_DXT.c \
    SOIL/image_helper.c \
    SOIL/SOIL.c \
    SOIL/stb_image_aug.c \
    Engine/PBRLight.cpp \

HEADERS += \
    GL/File.hpp \
    GL/RedGL.hpp \
    Engine/Engine.hpp \
    DEBUG/Debug.hpp \
    Engine/RedGame.hpp \
    Engine/RedScript.hpp \
    User/MyNano.hpp \
    RedGameEngine.hpp \
    SHADER/Shader.hpp \
    SOIL/image_DXT.h \
    SOIL/image_helper.h \
    SOIL/SOIL.h \
    SOIL/stb_image_aug.h \
    SOIL/stbi_DDS_aug_c.h \
    SOIL/stbi_DDS_aug.h

DISTFILES += \
    GLSL/f_shader.frag \
    GLSL/v_shader.vert

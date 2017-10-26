#include <glm/glm.hpp>

class Camera
{
private:
    float * cameraPos;
    float * cameraFront;
    float * cameraUp;

    float width;
    float height;

    float fovy;
    float near;
    float far;

    glm::mat4 projection;
    glm::mat4 view;
public:
    Camera(float fovy,float width,float height,float near,float far);
    ~Camera();

    void setCamera(float fovy,float width,float height,float near,float far);

    void setCameraWidthHeight(float width,float height);

    void setCameraPos(float x,float y,float z);
    void setCameraFront(float x,float y,float z);
    void setCameraUp(float x,float y,float z);

    glm::mat4 getProjection();
    glm::mat4 getView();
};

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
    // Defines several possible options for camera movement. Used as abstraction
    // to stay away from window-system specific input methods
    enum Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
    };

    // Default camera values
    static constexpr float DEFAULT_YAW = -90.0f;
    static constexpr float DEFAULT_PITCH = 0.0f;
    static constexpr float DEFAULT_SPEED = 2.5f;
    static constexpr float DEFAULT_SENSITIVITY = 0.1f;
    static constexpr float DEFAULT_ZOOM = 45.0f;

    // camera Attributes
    glm::vec3 mMovementDirection;
    glm::vec3 mPos;
    // basic vec
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    // world up
    glm::vec3 mWorldUp;
    // euler Angles
    float mYaw;
    float mPitch;
    // camera options
    float mMovementSpeed;
    float mMouseSensitivity;
    float mZoom;

    // camera state

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = DEFAULT_YAW,
        float pitch = DEFAULT_PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
        float yaw, float pitch);

    glm::mat4 getViewMatrix();

    void update();
    void setMovementDirection();
    void processKeyboard(Camera::Movement direction, float deltaTime);
    void processMouseMovement(
        float xoffset, float yoffset, GLboolean constrainPitch = true);

    void processMouseScroll(float yoffset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

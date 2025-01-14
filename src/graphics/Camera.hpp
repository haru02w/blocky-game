#pragma once
#include "glm/fwd.hpp"
#include <bitset>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For transformations
#include <glm/gtc/type_ptr.hpp> // For accessing data as pointers

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = DEFAULT_YAW,
        float pitch = DEFAULT_PITCH);
    ~Camera();

    void update();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(int scrWidth, int scrHeight) const;

    static constexpr float DEFAULT_YAW = -90.0f;
    static constexpr float DEFAULT_PITCH = 0.0f;
    static constexpr float DEFAULT_SPEED = 1.0f;
    static constexpr float DEFAULT_SENSITIVITY = 62 / 1000.0f;
    static constexpr float DEFAULT_FOV = 70.0f;
    static constexpr float DEFAULT_NEARPLANE = 0.1f;
    static constexpr float DEFAULT_FARPLANE = 10000.0f;

    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        SIZE, // always in the end!
    };

private:
    void updateCameraVector();
    void setupKeyboardInput();
    void setupMouseInput();

    // VIEW
    //
    // camera attrs
    glm::vec3 mPosition;
    std::bitset<Direction::SIZE> mDirections;
    // base vecs
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;

    // euler angles
    float mYaw;
    float mPitch;

    // Mouse
    struct {
        float x, y;
    } mLastMousePos;

    // camera options
    float mMovementSpeed;
    float mMouseSensitivity;

    // PROJECTION
    //
    float mFov;
    float mNearPlane;
    float mFarPlane;
};

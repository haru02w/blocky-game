#include "Camera.hpp"
#include "../Globals.hpp"
#include "../events/KeyEvent.hpp"
#include "../events/MouseEvent.hpp"
#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : mFront(glm::vec3(0.0f, 0.0f, -1.0f))
    , mMovementSpeed(DEFAULT_SPEED)
    , mMouseSensitivity(DEFAULT_SENSITIVITY)
    // arguments
    , mPosition(position)
    , mDirections()
    , mWorldUp(up)
    , mYaw(yaw)
    , mPitch(pitch)
    , mLastMousePos()
    , mFov(DEFAULT_FOV)
    , mNearPlane(DEFAULT_NEARPLANE)
    , mFarPlane(DEFAULT_FARPLANE)
{
    updateCameraVector();
    setupKeyboardInput();
    setupMouseInput();
}

Camera::~Camera() { }

void Camera::updateCameraVector()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(front);
    // also re-calculate the Right and Up vector
    mRight = glm::normalize(glm::cross(
        mFront, mWorldUp)); // normalize the vectors, because their length gets
                            // closer to 0 the more you look up or down which
                            // results in slower movement.
    mUp = glm::normalize(glm::cross(mRight, mFront));
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::mat4 Camera::getProjectionMatrix(int scrWidth, int scrHeight) const
{
    float aspectRatio
        = static_cast<float>(scrWidth) / static_cast<float>(scrHeight);
    return glm::perspective(
        glm::radians(mFov), aspectRatio, mNearPlane, mFarPlane);
}

void Camera::setupKeyboardInput()
{
    globals.eventManager.subscribe<KeyEvent>(
        "KEY_W", [=, this](KeyEvent &&keyEvent) {
            static glm::vec3 direction;
            if (keyEvent.action == KeyEvent::PRESSED)
                mDirections[FORWARD] = true;
            else if (keyEvent.action == KeyEvent::RELEASED)
                mDirections[FORWARD] = false;
        });

    globals.eventManager.subscribe<KeyEvent>(
        "KEY_S", [=, this](KeyEvent &&keyEvent) {
            if (keyEvent.action == KeyEvent::PRESSED)
                mDirections[BACKWARD] = true;
            else if (keyEvent.action == KeyEvent::RELEASED)
                mDirections[BACKWARD] = false;
        });

    globals.eventManager.subscribe<KeyEvent>(
        "KEY_A", [=, this](KeyEvent &&keyEvent) {
            if (keyEvent.action == KeyEvent::PRESSED)
                mDirections[LEFT] = true;
            else if (keyEvent.action == KeyEvent::RELEASED)
                mDirections[LEFT] = false;
        });

    globals.eventManager.subscribe<KeyEvent>(
        "KEY_D", [=, this](KeyEvent &&keyEvent) {
            if (keyEvent.action == KeyEvent::PRESSED)
                mDirections[RIGHT] = true;
            else if (keyEvent.action == KeyEvent::RELEASED)
                mDirections[RIGHT] = false;
        });

    globals.eventManager.subscribe<KeyEvent>(
        "KEY_LEFT_SHIFT", [=, this](KeyEvent &&keyEvent) {
            if (keyEvent.action == KeyEvent::PRESSED)
                mDirections[DOWN] = true;
            else if (keyEvent.action == KeyEvent::RELEASED)
                mDirections[DOWN] = false;
        });

    globals.eventManager.subscribe<KeyEvent>(
        "KEY_SPACE", [=, this](KeyEvent &&keyEvent) {
            if (keyEvent.action == KeyEvent::PRESSED)
                mDirections[UP] = true;
            else if (keyEvent.action == KeyEvent::RELEASED)
                mDirections[UP] = false;
        });
}
void Camera::setupMouseInput()
{
    static bool firstMouse = true;
    globals.eventManager.subscribe<MouseEvent>(
        "MOUSE_MOVEMENT", [=, this](MouseEvent &&mouseEvent) {
            [[unlikely]] if (firstMouse) {
                mLastMousePos.x = mouseEvent.posX;
                mLastMousePos.y = mouseEvent.posY;
                firstMouse = false;
            }

            // save offset
            float xoffset = mouseEvent.posX - mLastMousePos.x;
            float yoffset = mLastMousePos.y - mouseEvent.posY;

            // update last position with normalized positions
            mLastMousePos.x = mouseEvent.posX;
            mLastMousePos.y = mouseEvent.posY;

            // apply mouse sensitivity
            xoffset *= mMouseSensitivity;
            yoffset *= mMouseSensitivity;

            // update yaw and pitch rotation values
            mYaw += xoffset;
            mPitch += yoffset;

            // constrain pitch
            if (mPitch > 89.0f)
                mPitch = 89.0f;
            if (mPitch < -89.0f)
                mPitch = -89.0f;

            updateCameraVector();
        });
}

void Camera::update()
{
    if (mDirections[FORWARD])
        mPosition += mFront * mMovementSpeed;
    if (mDirections[BACKWARD])
        mPosition -= mFront * mMovementSpeed;

    if (mDirections[LEFT])
        mPosition -= mRight * mMovementSpeed;
    if (mDirections[RIGHT])
        mPosition += mRight * mMovementSpeed;

    if (mDirections[UP])
        mPosition += mUp * mMovementSpeed;
    if (mDirections[DOWN])
        mPosition -= mUp * mMovementSpeed;
}

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(10.0f),
      MouseSensitivity(0.1f),
      Zoom(45.0f),
      Radius(glm::length(position)),
      Target(glm::vec3(0.0f))
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Target, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 flatFront = glm::normalize(glm::vec3(Front.x, 0.0f, Front.z));
    if (direction == FORWARD)  Position += flatFront * velocity;
    if (direction == BACKWARD) Position -= flatFront * velocity;
    if (direction == LEFT)     Position -= Right * velocity;
    if (direction == RIGHT)    Position += Right * velocity;
    Target = Position + Front;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    Yaw += xoffset;
    Pitch += yoffset;
    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Radius -= yoffset;
    if (Radius < 1.0f) Radius = 1.0f;
    if (Radius > 100.0f) Radius = 100.0f;
    updateCameraVectors();
}

void Camera::ProcessOrbit(float xoffset, float yoffset) {
    Yaw += xoffset * MouseSensitivity;
    Pitch += yoffset * MouseSensitivity;
    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    float yawRad = glm::radians(Yaw);
    float pitchRad = glm::radians(Pitch);

    glm::vec3 offset;
    offset.x = Radius * cos(pitchRad) * cos(yawRad);
    offset.y = Radius * sin(pitchRad);
    offset.z = Radius * cos(pitchRad) * sin(yawRad);

    Position = Target + offset;
    Front = glm::normalize(Target - Position);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

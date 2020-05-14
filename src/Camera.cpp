/*
 *  Created by michal-swiatek on 14.05.2020, based on Joey de Vries tutorials.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 *  LearnOpenGL tutorial: https://learnopengl.com/Introduction
 */

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

//  Constructors just initialize members
camera::Settings::Settings(float movementSpeed, float zoomSpeed, float sensitivity, float fov) : movementSpeed(movementSpeed), zoomSpeed(zoomSpeed), sensitivity(sensitivity), fov(fov) { }

camera::Transform::Transform(const glm::vec3 &cameraPosition, const glm::vec3 &cameraRotation) : position(cameraPosition), rotation(cameraRotation) { }
camera::Transform::Transform(float x, float y, float z, float yaw, float pitch, float roll) : position(glm::vec3(x, y, z)), rotation(glm::vec3(yaw, pitch, roll)) { }

camera::Orientation::Orientation(const glm::vec3 &worldUp) : worldUp(worldUp) { }

//
//  Camera class
//

//  Constructors initialize members and call updateOrientation()
camera::Camera::Camera(const Transform &transform, const glm::vec3 &worldUp) : transform(transform), orientation(camera::Orientation(worldUp)) { updateOrientation(); }
camera::Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &worldUp) : transform(camera::Transform(position, rotation)), orientation(camera::Orientation(worldUp)) { updateOrientation(); }
camera::Camera::Camera(const Settings &settings, const Transform &transform, const glm::vec3 &worldUp) : settings(settings), transform(transform), orientation(camera::Orientation(worldUp)) { updateOrientation(); }

glm::mat4 camera::Camera::getViewMatrix() const
{
    return glm::lookAt(transform.position, transform.position + orientation.front, orientation.up);
}

void camera::Camera::move(Movement direction, float deltaTime)
{
    float velocity = settings.movementSpeed * deltaTime;

    switch (direction) {
        case camera::Movement::FORWARD:     transform.position += velocity * orientation.front;   break;
        case camera::Movement::BACKWARD:    transform.position -= velocity * orientation.front;   break;
        case camera::Movement::RIGHT:       transform.position += velocity * orientation.right;   break;
        case camera::Movement::LEFT:        transform.position -= velocity * orientation.right;   break;
        case camera::Movement::UP:          transform.position += velocity * orientation.up;      break;
        case camera::Movement::DOWN:        transform.position -= velocity * orientation.up;      break;
    }
}

void camera::Camera::rotate(float yaw, float pitch, float roll)
{
    transform.rotation.x += settings.sensitivity * yaw;
    transform.rotation.y += settings.sensitivity * pitch;
    transform.rotation.z += settings.sensitivity * roll;

    //  Prevent camera flipping
    if (transform.rotation.y < -89.0f)      transform.rotation.y = -89.0f;
    else if (transform.rotation.y > 89.0f)  transform.rotation.y = 89.0f;

    updateOrientation();
}

void camera::Camera::zoom(float value)
{
    settings.fov -= settings.zoomSpeed * value;

    if (settings.fov < 1.0f)        settings.fov = 1.0f;
    else if (settings.fov > 89.0f)  settings.fov = 89.0f;
}

void camera::Camera::updateOrientation()
{
    float yaw = transform.rotation.x;
    float pitch = transform.rotation.y;

    // Calculate the new Front vector
    glm::vec3 front;
    front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

    orientation.front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    orientation.right = glm::normalize(glm::cross(orientation.front, orientation.worldUp));
    orientation.up = glm::normalize(glm::cross(orientation.right, orientation.front));
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
}

//
//  Getters
//

camera::Settings& camera::Camera::getSettings()  { return settings; }

float camera::Camera::getZoom() const { return settings.fov; }

const camera::Transform& camera::Camera::getTransform() const { return transform; }
const camera::Orientation& camera::Camera::getOrientation() const { return orientation; }

//
//  Setters
//

void camera::Camera::setZoom(float zoom) { settings.fov = zoom; }

void camera::Camera::setTransform(const Transform &transform) { this->transform = transform; }
void camera::Camera::setTransform(const glm::vec3 &position, const glm::vec3 &rotation) { this->transform = camera::Transform(position, rotation); }

void camera::Camera::setWorldUp(const glm::vec3 &worldUp) { orientation.worldUp = worldUp; }

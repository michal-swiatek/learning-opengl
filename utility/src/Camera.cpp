/*
 *  Created by michal-swiatek on 14.05.2020, based on Joey de Vries tutorials.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 *  LearnOpenGL tutorial: https://learnopengl.com/Introduction
 */

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

//  Constructors just initialize members
cam::Settings::Settings(float movementSpeed, float zoomSpeed, float sensitivity, float fov, float aspectRatio) : movementSpeed(movementSpeed), zoomSpeed(zoomSpeed), sensitivity(sensitivity), fov(fov), aspectRatio(aspectRatio) { }
cam::Orientation::Orientation(const glm::vec3 &worldUp) : worldUp(worldUp) { }

//
//  Camera class
//

//  Constructors initialize members and call updateOrientation()
cam::Camera::Camera(const Transform &transform, const glm::vec3 &worldUp) : transform(transform), orientation(cam::Orientation(worldUp)) { updateOrientation(); }
cam::Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &worldUp) : transform(Transform(position, rotation)), orientation(cam::Orientation(worldUp)) { updateOrientation(); }
cam::Camera::Camera(const Settings &settings, const Transform &transform, const glm::vec3 &worldUp) : settings(settings), transform(transform), orientation(cam::Orientation(worldUp)) { updateOrientation(); }

glm::mat4 cam::Camera::getViewMatrix() const
{
    return glm::lookAt(transform.position, transform.position + orientation.front, orientation.up);
}

glm::mat4 cam::Camera::getProjectionMatrix() const
{
    return glm::perspective(settings.fov, settings.aspectRatio, 0.1f, 100.0f);
}

glm::mat4 cam::Camera::getViewProjectionMatrix() const
{
    return getProjectionMatrix() * getViewMatrix();
}

void cam::Camera::move(Direction direction, Speed speed, float deltaTime)
{
    float velocity = settings.movementSpeed * deltaTime;

    switch (speed) {
        case cam::Speed::FAST:      velocity *= 2;      break;
        case cam::Speed::SLOW:      velocity *= 0.25;   break;
        case cam::Speed::NORMAL:    velocity *= 1.0;    break;
    }

    switch (direction) {
        case cam::Direction::FORWARD:   transform.position += velocity * orientation.front;     break;
        case cam::Direction::BACKWARD:  transform.position -= velocity * orientation.front;     break;
        case cam::Direction::RIGHT:     transform.position += velocity * orientation.right;     break;
        case cam::Direction::LEFT:      transform.position -= velocity * orientation.right;     break;
        case cam::Direction::UP:        transform.position += velocity * orientation.up;        break;
        case cam::Direction::DOWN:      transform.position -= velocity * orientation.up;        break;
    }
}

void cam::Camera::rotate(float yaw, float pitch, float roll)
{
    transform.rotation.x += settings.sensitivity * yaw;
    transform.rotation.y += settings.sensitivity * pitch;
    transform.rotation.z += settings.sensitivity * roll;

    //  Prevent cam flipping
    if (transform.rotation.y < -89.0f)      transform.rotation.y = -89.0f;
    else if (transform.rotation.y > 89.0f)  transform.rotation.y = 89.0f;

    updateOrientation();
}

void cam::Camera::zoom(float value)
{
    settings.fov -= settings.zoomSpeed * value;

    if (settings.fov < 1.0f)
        settings.fov = 1.0f;
    if (settings.fov > 45.0f)
        settings.fov = 45.0f;
}

void cam::Camera::updateOrientation()
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

cam::Settings& cam::Camera::getSettings()  { return settings; }

float cam::Camera::getZoom() const { return settings.fov; }

const Transform& cam::Camera::getTransform() const { return transform; }
const cam::Orientation& cam::Camera::getOrientation() const { return orientation; }

//
//  Setters
//

void cam::Camera::setZoom(float zoom) { settings.fov = zoom; }

void cam::Camera::setTransform(const Transform &transform) { this->transform = transform; }
void cam::Camera::setTransform(const glm::vec3 &position, const glm::vec3 &rotation) { this->transform = Transform(position, rotation); }

void cam::Camera::setWorldUp(const glm::vec3 &worldUp) { orientation.worldUp = worldUp; }

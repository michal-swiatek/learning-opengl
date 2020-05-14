/*
 *  Created by michal-swiatek on 14.05.2020, based on Joey de Vries tutorials.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 *  LearnOpenGL tutorial: https://learnopengl.com/Introduction
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace cam {

    enum class Movement { FORWARD, BACKWARD, RIGHT, LEFT, UP, DOWN };

    struct Settings
    {
        //  Default cam settings
        static constexpr float MOVEMENT_SPEED = 10.0;
        static constexpr float ZOOM_SPEED = 0.1;
        static constexpr float SENSITIVITY = 0.1;
        static constexpr float FIELD_OF_VIEW = 45.0;

        float movementSpeed;
        float zoomSpeed;
        float sensitivity;
        float fov;

        Settings(float movementSpeed = MOVEMENT_SPEED, float zoomSpeed = ZOOM_SPEED, float sensitivity = SENSITIVITY, float fov = FIELD_OF_VIEW);
    };

    struct Transform
    {
        //  Default Euler angles values
        static constexpr float YAW = 0.0f;
        static constexpr float PITCH = 0.0f;
        static constexpr float ROLL = 0.0f;

        static constexpr glm::vec3 ROTATION = glm::vec3(-90.0f, 0.0f, 0.0f);

        glm::vec3 position;
        glm::vec3 rotation;

        Transform(const glm::vec3& cameraPosition, const glm::vec3& cameraRotation = ROTATION);
        Transform(float x, float y, float z, float yaw = YAW, float pitch = PITCH, float roll = ROLL);
    };

    struct Orientation
    {
        //  Default world dup vector
        static constexpr glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;

        glm::vec3 worldUp;

        explicit Orientation(const glm::vec3& worldUp);
    };

    class Camera
    {
    public:
        Camera(const Transform& transform, const glm::vec3& worldUp = Orientation::WORLD_UP);
        Camera(const glm::vec3& position = glm::vec3(0.0), const glm::vec3& rotation = Transform::ROTATION, const glm::vec3& worldUp = Orientation::WORLD_UP);
        Camera(const Settings& settings, const Transform& transform, const glm::vec3& worldUp = Orientation::WORLD_UP);
        virtual ~Camera() = default;

        glm::mat4 getViewMatrix() const;

        virtual void move(Movement direction, float deltaTime = 1.0);
        virtual void rotate(float yaw, float pitch, float roll = 0.0);
        virtual void zoom(float value);

        //  Get
        Settings& getSettings();  //  Reference for easy manipulation

        float getZoom() const;

        const Transform& getTransform() const;
        const Orientation& getOrientation() const;

        //  Set
        void setZoom(float zoom = Settings::FIELD_OF_VIEW);

        void setTransform(const Transform& transform);
        void setTransform(const glm::vec3& position, const glm::vec3& rotation = Transform::ROTATION);

        void setWorldUp(const glm::vec3& worldUp = Orientation::WORLD_UP);

    private:
        Settings settings;

        Transform transform;
        Orientation orientation;

        // Calculates the front vector from the Camera's (updated) Euler Angles
        void updateOrientation();
    };
}

#endif //CAMERA_H

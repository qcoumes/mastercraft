#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <tool/Camera.hpp>


#ifndef M_PIf32
#define M_PIf32    3.141592653589793238462643383279502884f /* pi */
#endif

#ifndef M_PI_2f32
#define M_PI_2f32  1.570796326794896619231321691639751442f /* pi/2 */
#endif

namespace tool {
    
    Camera::Camera() :
            position(glm::vec3(0, 0, 0)), pitch(0.0), yaw(M_PIf32) {
        computeDirectionVectors();
    }
    
    
    void Camera::computeDirectionVectors() {
        this->frontVector = {
                std::cos(this->pitch) * std::sin(this->yaw),
                std::sin(this->pitch),
                std::cos(this->pitch) * std::cos(this->yaw)
        };
        this->leftVector = { std::sin(this->yaw + M_PI_2f32), 0.f, std::cos(this->yaw + M_PI_2f32) };
        this->upVector = glm::cross(this->frontVector, this->leftVector);
    }
    
    
    void Camera::moveLeft(float delta) {
        this->position += delta * this->leftVector;
    }
    
    
    void Camera::moveForward(float delta) {
        this->position += delta * this->frontVector;
    }
    
    
    void Camera::moveUp(float delta) {
        this->position += this->upVector * delta;
    }
    
    
    void Camera::rotateLeft(float degrees) {
        this->yaw += glm::radians(degrees);
        computeDirectionVectors();
    }
    
    
    void Camera::rotateUp(float degrees) {
        this->pitch += glm::radians(degrees);
        this->pitch = std::max(std::min(this->pitch, M_PI_2f32), -M_PI_2f32);
        computeDirectionVectors();
    }
    
    
    void Camera::setPosition(const glm::vec3 &position) {
        this->position = position;
    }
    
    
    void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z) {
        this->position = { x, y, z };
    }
    
    
    glm::vec3 Camera::getPosition() const {
        return this->position;
    }
    
    
    void Camera::setAngle(GLfloat pitch, GLfloat yaw) {
        this->pitch = pitch;
        this->yaw = yaw;
    }
    
    
    void Camera::setProjMatrix(float fov, int width, int height) {
        this->projMatrix = glm::perspective(
                glm::radians(fov), static_cast<float>(width) / static_cast<float>(height), 0.1f, 256.f
        );
    }
    
    
    glm::mat4 Camera::getViewMatrix() const {
        return glm::lookAt(this->position, this->position + this->frontVector, this->upVector);
    }
    
    
    glm::mat4 Camera::getProjMatrix() const {
        return this->projMatrix;
    }
    
    
    glm::vec3 Camera::getFrontVector() const {
        return this->frontVector;
    }
}

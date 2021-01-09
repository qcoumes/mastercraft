#ifndef OPENGL_CAMERA_HPP
#define OPENGL_CAMERA_HPP

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <misc/INonCopyable.hpp>


namespace tool {
    
    class Camera : public misc::INonCopyable {
        
        private:
            glm::mat4 projMatrix;  /**< Projection matrix of the camera */
            glm::vec3 position;    /**< Position of the camera */
            GLfloat pitch;         /**< Rotation on X axis */
            GLfloat yaw;           /**< Rotation on Y axis */
            glm::vec3 leftVector;  /**< Vector used to move on X axis */
            glm::vec3 upVector;    /**< Vector used to move on Y axis */
            glm::vec3 frontVector; /**< Vector used to move on Z axis */
            
            void computeDirectionVectors();
        
        public:
            
            Camera();
            
            void moveLeft(float delta);
            
            void moveForward(float delta);
            
            void moveUp(float delta);
            
            void rotateLeft(float degrees);
            
            void rotateUp(float degrees);
            
            void setPosition(const glm::vec3 &position);
            
            void setPosition(GLfloat x, GLfloat y, GLfloat z);
            
            [[nodiscard]] glm::vec3 getPosition() const;
            
            void setAngle(GLfloat pitch, GLfloat yaw);
            
            [[nodiscard]] glm::mat4 getViewMatrix() const;
            
            void setProjMatrix(float fov, int width, int height);
            
            [[nodiscard]] glm::mat4 getProjMatrix() const;
            
            [[nodiscard]] glm::vec3 getFrontVector() const;
    };
}

#endif // OPENGL_CAMERA_HPP

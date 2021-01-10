#include <glm/gtc/type_ptr.hpp>

#include <entity/Sun.hpp>
#include <app/Engine.hpp>
#include <iostream>


namespace entity {
    
    Sun::Sun() :
        shader(std::make_unique<shader::Shader>("../shader/sun.vs.glsl", "../shader/sun.fs.glsl")) {
        this->shader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Sun::~Sun() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    GLuint Sun::update() {
        app::Engine *engine = app::Engine::getInstance();
        GLfloat angle = (
            360.f / app::Config::TICK_PER_DAY_CYCLE * static_cast<float>(engine->world->tickCycle)
        );
        glm::mat4 rotationZ = glm::rotate(
            glm::mat4(1.f), glm::radians(angle), glm::vec3(0.f, 0.f, 1.f)
        );
        glm::mat4 rotationY = glm::rotate(
            glm::mat4(1.f), glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f)
        );
        glm::vec3 position, camera = engine->camera->getPosition();
        glm::vec3 vertices[36];
        
        this->position = glm::vec3(rotationY * rotationZ * glm::vec4(1000, 0, 0, 1));
        
        for (GLuint i = 0; i < 36; i++) {
            position = glm::vec3(
                rotationY * rotationZ * glm::vec4(this->vertices[i] + glm::vec3(20, 0, 0), 1)
            );
            position += camera;
            vertices[i] = position;
        }
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Set the VAO
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(
            VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        return 1;
    }
    
    
    GLuint Sun::render() {
        app::Engine *engine = app::Engine::getInstance();
        glm::mat4 MVMatrix = engine->camera->getViewMatrix();
        glm::mat4 MVPMatrix = engine->camera->getProjMatrix() * MVMatrix;
        
        this->shader->use();
        this->shader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        this->shader->stop();
        return 1;
    }
    
    
    glm::vec3 Sun::getPosition() {
        return this->position;
    }
}

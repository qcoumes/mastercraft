#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include <entity/Skybox.hpp>
#include <app/Engine.hpp>


namespace entity {
    
    Skybox::Skybox() {
        std::unique_ptr<misc::Image> texture[6] = {
            std::unique_ptr<misc::Image>(
                misc::Image::loadPNG("../assets/entity/skybox/negative_right.png")
            ),
            std::unique_ptr<misc::Image>(
                misc::Image::loadPNG("../assets/entity/skybox/negative_left.png")
            ),
            std::unique_ptr<misc::Image>(
                misc::Image::loadPNG("../assets/entity/skybox/negative_top.png")
            ),
            std::unique_ptr<misc::Image>(
                misc::Image::loadPNG("../assets/entity/skybox/negative_bottom.png")
            ),
            std::unique_ptr<misc::Image>(
                misc::Image::loadPNG("../assets/entity/skybox/negative_back.png")
            ),
            std::unique_ptr<misc::Image>(
                misc::Image::loadPNG("../assets/entity/skybox/negative_front.png")
            ),
        };
        this->negativeSky = std::make_unique<shader::Cubemap>(texture);
        
        this->shader = std::make_unique<shader::ShaderCubemap>(
            "../shader/skybox.vs.glsl", "../shader/skybox.fs.glsl"
        );
        this->shader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->shader->addUniform("uSkyColor", shader::UNIFORM_3_F);
        
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
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
    }
    
    
    Skybox::~Skybox() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    GLuint Skybox::render() {
        app::Engine *engine = app::Engine::getInstance();
        // Remove translation from the MV
        glm::mat4 MVMatrix = glm::mat4(glm::mat3(engine->camera->getViewMatrix()));
        glm::mat4 MVPMatrix = engine->camera->getProjMatrix() * MVMatrix;
        
        glCullFace(GL_FRONT);
        this->shader->use();
        this->shader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        this->shader->loadUniform(
            "uSkyColor", glm::value_ptr(app::Config::getSkyboxColor(engine->world->tickCycle))
        );
        this->shader->bindCubemap(*this->negativeSky);
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        this->shader->unbindCubemap();
        this->shader->stop();
        glCullFace(GL_BACK);
        
        return 1;
    }
}

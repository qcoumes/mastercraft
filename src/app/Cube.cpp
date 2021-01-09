#include <glm/gtc/type_ptr.hpp>

#include <shader/Texture.hpp>
#include <app/Cube.hpp>
#include <app/Engine.hpp>


namespace app {
    
    TexturedVertex::TexturedVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texture) :
            position(position), normal(normal), texture(texture) {
    }
    
    
    Cube::Cube() :
            shader(shader::ShaderTexture("../shader/cube.vs.glsl", "../shader/cube.fs.glsl")),
            texture(shader::Texture(misc::Image::loadPNG("../assets/white4x4.png"))) {
        
        TexturedVertex vertices[36] = {
                // Face
                TexturedVertex({ 0, 0, 1 }, { 0, 0, 1 }, { 1, 1 }),
                TexturedVertex({ 1, 0, 1 }, { 0, 0, 1 }, { 0, 1 }),
                TexturedVertex({ 1, 1, 1 }, { 0, 0, 1 }, { 0, 0 }),
                TexturedVertex({ 1, 1, 1 }, { 0, 0, 1 }, { 0, 0 }),
                TexturedVertex({ 0, 1, 1 }, { 0, 0, 1 }, { 1, 0 }),
                TexturedVertex({ 0, 0, 1 }, { 0, 0, 1 }, { 1, 1 }),
                
                // Top
                TexturedVertex({ 0, 1, 1 }, { 0, 1, 0 }, { 1, 1 }),
                TexturedVertex({ 1, 1, 1 }, { 0, 1, 0 }, { 0, 1 }),
                TexturedVertex({ 1, 1, 0 }, { 0, 1, 0 }, { 0, 0 }),
                TexturedVertex({ 1, 1, 0 }, { 0, 1, 0 }, { 0, 0 }),
                TexturedVertex({ 0, 1, 0 }, { 0, 1, 0 }, { 1, 0 }),
                TexturedVertex({ 0, 1, 1 }, { 0, 1, 0 }, { 1, 1 }),
                
                // Back
                TexturedVertex({ 1, 0, 0 }, { 0, 0, -1 }, { 1, 1 }),
                TexturedVertex({ 0, 0, 0 }, { 0, 0, -1 }, { 0, 1 }),
                TexturedVertex({ 0, 1, 0 }, { 0, 0, -1 }, { 0, 0 }),
                TexturedVertex({ 0, 1, 0 }, { 0, 0, -1 }, { 0, 0 }),
                TexturedVertex({ 1, 1, 0 }, { 0, 0, -1 }, { 1, 0 }),
                TexturedVertex({ 1, 0, 0 }, { 0, 0, -1 }, { 1, 1 }),
                
                // Bottom
                TexturedVertex({ 0, 0, 0 }, { 0, -1, 0 }, { 1, 1 }),
                TexturedVertex({ 1, 0, 0 }, { 0, -1, 0 }, { 0, 1 }),
                TexturedVertex({ 1, 0, 1 }, { 0, -1, 0 }, { 0, 0 }),
                TexturedVertex({ 1, 0, 1 }, { 0, -1, 0 }, { 0, 0 }),
                TexturedVertex({ 0, 0, 1 }, { 0, -1, 0 }, { 1, 0 }),
                TexturedVertex({ 0, 0, 0 }, { 0, -1, 0 }, { 1, 1 }),
                
                // Left
                TexturedVertex({ 0, 0, 0 }, { -1, 0, 0 }, { 1, 1 }),
                TexturedVertex({ 0, 0, 1 }, { -1, 0, 0 }, { 0, 1 }),
                TexturedVertex({ 0, 1, 1 }, { -1, 0, 0 }, { 0, 0 }),
                TexturedVertex({ 0, 1, 1 }, { -1, 0, 0 }, { 0, 0 }),
                TexturedVertex({ 0, 1, 0 }, { -1, 0, 0 }, { 1, 0 }),
                TexturedVertex({ 0, 0, 0 }, { -1, 0, 0 }, { 1, 1 }),
                
                // Right
                TexturedVertex({ 1, 0, 1 }, { 1, 0, 0 }, { 1, 1 }),
                TexturedVertex({ 1, 0, 0 }, { 1, 0, 0 }, { 0, 1 }),
                TexturedVertex({ 1, 1, 0 }, { 1, 0, 0 }, { 0, 0 }),
                TexturedVertex({ 1, 1, 0 }, { 1, 0, 0 }, { 0, 0 }),
                TexturedVertex({ 1, 1, 1 }, { 1, 0, 0 }, { 1, 0 }),
                TexturedVertex({ 1, 0, 1 }, { 1, 0, 0 }, { 1, 1 }),
        };
        
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Set the VAO
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glVertexAttribPointer(
                VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex),
                reinterpret_cast<const GLvoid *>(offsetof(TexturedVertex, position))
        );
        glVertexAttribPointer(
                VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex),
                reinterpret_cast<const GLvoid *>(offsetof(TexturedVertex, normal))
        );
        glVertexAttribPointer(
                VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex),
                reinterpret_cast<const GLvoid *>(offsetof(TexturedVertex, texture))
        );
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        this->shader.addUniform("uMV", shader::UNIFORM_MATRIX_4F);
        this->shader.addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->shader.addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
        this->shader.addUniform("uLightPosition", shader::UNIFORM_3_F);
        this->shader.addUniform("uLightColor", shader::UNIFORM_3_F);
        this->shader.addUniform("uLightDirIntensity", shader::UNIFORM_1_F);
        this->shader.addUniform("uLightAmbIntensity", shader::UNIFORM_1_F);
        
        GLfloat dirIntensity = 1.f, ambIntensity = 0.4f;
        this->shader.use();
        this->shader.loadUniform("uLightPosition", glm::value_ptr(glm::vec3(100, 100, -100)));
        this->shader.loadUniform("uLightColor", glm::value_ptr(glm::vec3(1, 1, 1)));
        this->shader.loadUniform("uLightDirIntensity", &dirIntensity);
        this->shader.loadUniform("uLightAmbIntensity", &ambIntensity);
        this->shader.stop();
    }
    
    
    Cube::~Cube() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    void Cube::update() {
    }
    
    
    void Cube::render() const {
        Engine *engine = Engine::getInstance();
        glm::mat4 MVMatrix = engine->camera->getViewMatrix();
        glm::mat4 MVPMatrix = engine->camera->getProjMatrix() * MVMatrix;
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(MVMatrix));
        
        this->shader.use();
        this->shader.loadUniform("uMV", glm::value_ptr(MVMatrix));
        this->shader.loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        this->shader.loadUniform("uNormal", glm::value_ptr(normalMatrix));
        this->shader.bindTexture(this->texture);
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(36));
        glBindVertexArray(0);
        this->shader.unbindTexture();
        this->shader.stop();
    }
}

#ifndef OPENGL_CUBE_HPP
#define OPENGL_CUBE_HPP

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <shader/ShaderTexture.hpp>
#include <tool/Rendered.hpp>


namespace app {
    
    struct TexturedVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture;
        
        TexturedVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texture);
    };
    
    
    
    class Cube : public tool::Rendered {
        
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
            static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
            static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;
            
            shader::ShaderTexture shader;
            shader::Texture texture;
            GLuint vbo = 0;
            GLuint vao = 0;
        
        public:
            
            Cube();
            
            ~Cube() override;
            
            void update() override;
            
            void render() const override;
    };
}

#endif // OPENGL_CUBE_HPP

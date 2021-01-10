#ifndef OPENGL_SUN_HPP
#define OPENGL_SUN_HPP

#include <shader/Shader.hpp>
#include <app/Config.hpp>


namespace entity {
    
    class Sun : public misc::INonCopyable {
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
        
        private:
            glm::vec3 vertices[36] = {
                // face
                { -1, -1, 1 },
                { 1,  -1, 1 },
                { 1,  1,  1 },
                { 1,  1,  1 },
                { -1, 1,  1 },
                { -1, -1, 1 },
                // top
                { -1, 1,  1 },
                { 1,  1,  1 },
                { 1,  1,  -1 },
                { 1,  1,  -1 },
                { -1, 1,  -1 },
                { -1, 1,  1 },
                // back
                { 1,  -1, -1 },
                { -1, -1, -1 },
                { -1, 1,  -1 },
                { -1, 1,  -1 },
                { 1,  1,  -1 },
                { 1,  -1, -1 },
                // bottom
                { -1, -1, -1 },
                { 1,  -1, -1 },
                { 1,  -1, 1 },
                { 1,  -1, 1 },
                { -1, -1, 1 },
                { -1, -1, -1 },
                // left
                { -1, -1, -1 },
                { -1, -1, 1 },
                { -1, 1,  1 },
                { -1, 1,  1 },
                { -1, 1,  -1 },
                { -1, -1, -1 },
                // right
                { 1,  -1, 1 },
                { 1,  -1, -1 },
                { 1,  1,  -1 },
                { 1,  1,  -1 },
                { 1,  1,  1 },
                { 1,  -1, 1 },
            };
            std::unique_ptr<shader::Shader> shader;
            glm::vec3 position;
            GLuint vbo;
            GLuint vao;
        
        public:
            
            Sun();
            
            ~Sun();
            
            GLuint update();
            
            GLuint render();
            
            [[nodiscard]] glm::vec3 getPosition();
    };
}

#endif //OPENGL_SUN_HPP

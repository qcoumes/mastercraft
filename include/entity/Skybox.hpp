#ifndef OPENGL_SKYBOX_HPP
#define OPENGL_SKYBOX_HPP

#include <glm/vec3.hpp>

#include <shader/Cubemap.hpp>
#include <shader/ShaderCubemap.hpp>


namespace entity {
    
    class Skybox : public misc::INonCopyable {
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
            std::unique_ptr<shader::ShaderCubemap> shader;
            std::unique_ptr<shader::Cubemap> negativeSky;
            GLuint vbo;
            GLuint vao;
        
        public:
            
            explicit Skybox();
            
            ~Skybox();
            
            GLuint render();
    };
}

#endif // OPENGL_SKYBOX_HPP

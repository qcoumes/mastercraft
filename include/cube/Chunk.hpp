#ifndef OPENGL_CHUNK_H
#define OPENGL_CHUNK_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <misc/INonCopyable.hpp>
#include <cube/CubeData.hpp>


namespace cube {
    
    class Chunk : public misc::INonCopyable {
        public:
            static constexpr GLint X = 16;
            static constexpr GLint Y = 16;
            static constexpr GLint Z = 16;
            static constexpr GLint SIZE = X * Y * Z;
        
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
            static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
            static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;
            static constexpr GLuint VERTEX_ATTR_DATA = 3;
            
            CubeData cubes[X][Y][Z] {};
            glm::ivec3 position = glm::ivec3(0);
            GLboolean modified = true;
            GLuint countAlpha = 0;
            GLuint vboAlpha = 0;
            GLuint vaoAlpha = 0;
            GLuint count = 0;
            GLuint vbo = 0;
            GLuint vao = 0;
            
            [[nodiscard]] static bool onBorder(GLubyte x, GLubyte y, GLubyte z);
            
            [[nodiscard]] bool occluded(CubeData type, GLint x, GLint y, GLint z,
                                        CubeData direction) const;
            
            [[nodiscard]] static GLushort computeData(CubeData type, CubeData direction,
                                               bool opaqueAbove) ;
        
        public:
            
            Chunk();
            
            ~Chunk();
            
            CubeData get(GLubyte x, GLubyte y, GLubyte z);
            
            void set(GLubyte x, GLubyte y, GLubyte z, CubeData type);
            
            void setPosition(GLint x, GLint y, GLint z);
            
            void touch();
            
            GLuint update();
            
            GLuint render(bool alpha) const;
    };
}

#endif // OPENGL_CHUNK_H

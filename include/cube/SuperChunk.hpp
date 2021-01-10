#ifndef OPENGL_SUPERCHUNK_HPP
#define OPENGL_SUPERCHUNK_HPP

#include <glm/glm.hpp>

#include <cube/Chunk.hpp>
#include <shader/Shader.hpp>
#include <misc/INonCopyable.hpp>
#include <app/Config.hpp>


namespace cube {
    
    class SuperChunk : public misc::INonCopyable {
        
        public:
            static constexpr GLint CHUNK_X = 2;
            static constexpr GLint CHUNK_Y = 16;
            static constexpr GLint CHUNK_Z = 2;
            static constexpr GLint CHUNK_SIZE = CHUNK_X * CHUNK_Y * CHUNK_Z;
            static constexpr GLint X = Chunk::X * CHUNK_X;
            static constexpr GLint Y = Chunk::Y * CHUNK_Y;
            static constexpr GLint Z = Chunk::Z * CHUNK_Z;
            static constexpr GLint SIZE = CHUNK_SIZE * Chunk::SIZE;
            
            static_assert(app::Config::GEN_MAX_H <= Y);
        
        private:
            Chunk chunks[CHUNK_X][CHUNK_Y][CHUNK_Z];
            glm::ivec3 position = { 0, 0, 0 };
            GLboolean modified = true;
            GLuint count = 0;
        
        public:
            
            SuperChunk() = default;
            
            explicit SuperChunk(glm::ivec3 position);
            
            SuperChunk(GLuint x, GLuint y, GLuint z);
            
            ~SuperChunk() = default;
            
            CubeData get(GLuint x, GLuint y, GLuint z);
            
            void set(GLuint x, GLuint y, GLuint z, CubeData type);
            
            void touch();
            
            GLuint update();
            
            GLuint render(bool alpha);
    };
}

#endif //OPENGL_SUPERCHUNK_HPP

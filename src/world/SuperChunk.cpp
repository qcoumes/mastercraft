#include <iostream>

#include <glm/ext.hpp>

#include <world/SuperChunk.hpp>
#include <app/Engine.hpp>


namespace world {
    
    SuperChunk::SuperChunk(glm::ivec3 t_position) :
        position(t_position), modified(true), count(0) {
        
        for (GLint x = 0; x < CHUNK_X; x++) {
            for (GLint y = 0; y < CHUNK_Y; y++) {
                for (GLint z = 0; z < CHUNK_Z; z++) {
                    this->chunks[x][y][z].setPosition(
                        t_position.x + (x * Chunk::X), t_position.y + (y * Chunk::Y),
                        t_position.z + (z * Chunk::Z)
                    );
                }
            }
        }
    }
    
    
    SuperChunk::SuperChunk(GLuint x, GLuint y, GLuint z) :
        SuperChunk(glm::ivec3(x, y, z)) {
    }
    
    
    CubeData SuperChunk::get(GLuint x, GLuint y, GLuint z) {
        assert(x < X);
        assert(y < Y);
        assert(z < Z);
        
        return this->chunks[x / Chunk::X][y / Chunk::Y][z / Chunk::Z].get(
            x % Chunk::X, y % Chunk::Y, z % Chunk::Z
        );
    }
    
    
    void SuperChunk::set(GLuint x, GLuint y, GLuint z, CubeData type) {
        assert(x < X);
        assert(y < Y);
        assert(z < Z);
        
        this->chunks[x / Chunk::X][y / Chunk::Y][z / Chunk::Z].set(
            x % Chunk::X, y % Chunk::Y, z % Chunk::Z, type
        );
        this->modified = true;
    }
    
    
    void SuperChunk::touch() {
        for (GLubyte x = 0; x < CHUNK_X; x++) {
            for (GLubyte y = 0; y < CHUNK_Y; y++) {
                for (GLubyte z = 0; z < CHUNK_Z; z++) {
                    this->chunks[x][y][z].touch();
                }
            }
        }
        this->modified = true;
    }
    
    
    GLuint SuperChunk::update() {
        if (!modified) {
            return this->count;
        }
        
        this->count = 0;
        
        for (GLubyte x = 0; x < CHUNK_X; x++) {
            for (GLubyte y = 0; y < CHUNK_Y; y++) {
                for (GLubyte z = 0; z < CHUNK_Z; z++) {
                    this->count += this->chunks[x][y][z].update();
                }
            }
        }
        
        this->modified = false;
        return this->count;
    }
    
    
    GLuint SuperChunk::render(bool alpha) {
        assert(!modified);
        
        if (this->count == 0) {
            return 0;
        }
        
        GLuint rendered = 0;
        glm::vec3 position;
        app::Engine *engine = app::Engine::getInstance();
        for (GLubyte x = 0; x < CHUNK_X; x++) {
            for (GLubyte y = 0; y < CHUNK_Y; y++) {
                for (GLubyte z = 0; z < CHUNK_Z; z++) {
                    position = glm::ivec3(
                        x * Chunk::X + this->position.x,
                        y * Chunk::Y + this->position.y,
                        z * Chunk::Z + this->position.z
                    );
                    engine->chunkManager->cubeShader->loadUniform(
                        "uChunkPosition", glm::value_ptr(position)
                    );
                    rendered += this->chunks[x][y][z].render(alpha);
                }
            }
        }
        
        return rendered;
    }
}

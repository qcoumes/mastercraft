#include <iostream>
#include <exception>

#include <cube/Chunk.hpp>
#include <cube/CubeFace.hpp>
#include <app/Engine.hpp>
#include <app/Config.hpp>


namespace cube {
    
    Chunk::Chunk() {
        glGenBuffers(1, &this->vboAlpha);
        glGenVertexArrays(1, &this->vaoAlpha);
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Chunk::~Chunk() {
        glDeleteBuffers(1, &this->vboAlpha);
        glDeleteVertexArrays(1, &this->vaoAlpha);
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    bool Chunk::onBorder(GLubyte x, GLubyte y, GLubyte z) {
        static constexpr GLubyte MAX_X = X - 1;
        static constexpr GLubyte MAX_Y = Y - 1;
        static constexpr GLubyte MAX_Z = Z - 1;
        
        return x == MAX_X || y == MAX_Y || z == MAX_Z || !x || !y || !z;
    }
    
    
    bool Chunk::occluded(CubeData type, GLint x, GLint y, GLint z, CubeData direction) const {
        app::Engine *engine = app::Engine::getInstance();
        app::Config *config = app::Config::getInstance();
        
        if (!config->getOcclusionCulling()) {
            return false;
        }
        
        if (onBorder(static_cast<GLubyte>(x), static_cast<GLubyte>(y), static_cast<GLubyte>(z))) {
            x += this->position.x;
            y += this->position.y;
            z += this->position.z;
            
            // Face with ALPHA are drawn only when in contact with AIR
            if (type & ALPHA) {
                switch (direction) {
                    case CubeData::FACE:
                        return engine->world->chunkManager->get({ x, y, z + 1 }) != CubeData::AIR;
                    case CubeData::TOP:
                        return engine->world->chunkManager->get({ x, y + 1, z }) != CubeData::AIR;
                    case CubeData::BACK:
                        return engine->world->chunkManager->get({ x, y, z - 1 }) != CubeData::AIR;
                    case CubeData::BOTTOM:
                        return engine->world->chunkManager->get({ x, y - 1, z }) != CubeData::AIR;
                    case CubeData::LEFT:
                        return engine->world->chunkManager->get({ x - 1, y, z }) != CubeData::AIR;
                    case CubeData::RIGHT:
                        return engine->world->chunkManager->get({ x + 1, y, z }) != CubeData::AIR;
                    default:
                        throw std::runtime_error("Received an invalid direction");
                }
            }
            
            switch (direction) {
                case CubeData::FACE:
                    return !(engine->world->chunkManager->get({ x, y, z + 1 }) & ALPHA);
                case CubeData::TOP:
                    return !(engine->world->chunkManager->get({ x, y + 1, z }) & ALPHA);
                case CubeData::BACK:
                    return !(engine->world->chunkManager->get({ x, y, z - 1 }) & ALPHA);
                case CubeData::BOTTOM:
                    return !(engine->world->chunkManager->get({ x, y - 1, z }) & ALPHA);
                case CubeData::LEFT:
                    return !(engine->world->chunkManager->get({ x - 1, y, z }) & ALPHA);
                case CubeData::RIGHT:
                    return !(engine->world->chunkManager->get({ x + 1, y, z }) & ALPHA);
                default:
                    throw std::runtime_error("Received an invalid direction");
            }
        }
        
        // Face with ALPHA are drawn only when in contact with AIR
        if (type & ALPHA) {
            switch (direction) {
                case CubeData::FACE:
                    return this->cubes[x][y][z + 1] != CubeData::AIR;
                case CubeData::TOP:
                    return this->cubes[x][y + 1][z] != CubeData::AIR;
                case CubeData::BACK:
                    return this->cubes[x][y][z - 1] != CubeData::AIR;
                case CubeData::BOTTOM:
                    return this->cubes[x][y - 1][z] != CubeData::AIR;
                case CubeData::LEFT:
                    return this->cubes[x - 1][y][z] != CubeData::AIR;
                case CubeData::RIGHT:
                    return this->cubes[x + 1][y][z] != CubeData::AIR;
                default:
                    throw std::runtime_error("Received an invalid direction");
            }
        }
        
        switch (direction) {
            case CubeData::FACE:
                return !(this->cubes[x][y][z + 1] & ALPHA);
            case CubeData::TOP:
                return !(this->cubes[x][y + 1][z] & ALPHA);
            case CubeData::BACK:
                return !(this->cubes[x][y][z - 1] & ALPHA);
            case CubeData::BOTTOM:
                return !(this->cubes[x][y - 1][z] & ALPHA);
            case CubeData::LEFT:
                return !(this->cubes[x - 1][y][z] & ALPHA);
            case CubeData::RIGHT:
                return !(this->cubes[x + 1][y][z] & ALPHA);
            default:
                throw std::runtime_error("Received an invalid direction");
        }
    }
    
    
    GLushort Chunk::computeData(CubeData type, CubeData direction, bool opaqueAbove) {
        if (type & TOP_OVERLAY && opaqueAbove) {
            return type | CubeData::BOTTOM;
        }
        
        return type | direction;
    }
    
    
    CubeData Chunk::get(GLubyte x, GLubyte y, GLubyte z) {
        assert(x < X);
        assert(y < Y);
        assert(z < Z);
        
        return this->cubes[x][y][z];
    }
    
    
    void Chunk::set(GLubyte x, GLubyte y, GLubyte z, CubeData type) {
        assert(x < X);
        assert(y < Y);
        assert(z < Z);
        
        this->cubes[x][y][z] = type;
        this->modified = true;
    }
    
    
    void Chunk::setPosition(GLint x, GLint y, GLint z) {
        this->position = { x, y, z };
    }
    
    
    void Chunk::touch() {
        this->modified = true;
    }
    
    
    GLuint Chunk::update() {
        static constexpr GLint FACE_COUNT = SIZE * 6;
        
        if (!modified) {
            return this->count;
        }
        
        this->countAlpha = 0;
        this->count = 0;
        
        CubeFace drawnAlpha[FACE_COUNT], drawn[FACE_COUNT];
        bool opaqueAbove = false;
        CubeData data;
        GLubyte y;
        for (GLubyte x = 0; x < X; x++) {
            for (GLubyte z = 0; z < Z; z++) {
                for (GLshort sy = Y - 1; sy >= 0; sy--) {
                    y = static_cast<GLubyte>(sy);
                    data = this->cubes[x][y][z];
                    
                    if (data == CubeData::AIR) {
                        opaqueAbove = false;
                        continue;
                    }
                    
                    if (data & ALPHA) {
                        opaqueAbove = false;
                        if (!occluded(data, x, y, z, CubeData::TOP)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::top(
                                x, y, z, data | CubeData::TOP
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::BOTTOM)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::bottom(
                                x, y, z, data | CubeData::BOTTOM
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::FACE)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::face(
                                x, y, z, data | CubeData::FACE
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::BACK)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::back(
                                x, y, z, data | CubeData::BACK
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::LEFT)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::left
                                (x, y, z, data | CubeData::LEFT
                                );
                        }
                        if (!occluded(data, x, y, z, CubeData::RIGHT)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::right(
                                x, y, z, data | CubeData::RIGHT
                            );
                        }
                    }
                    else {
                        if (!occluded(data, x, y, z, CubeData::TOP)) {
                            drawn[this->count++] = CubeFace::top(
                                x, y, z, data | CubeData::TOP
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::BOTTOM)) {
                            drawn[this->count++] = CubeFace::bottom(
                                x, y, z, data | CubeData::BOTTOM
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::FACE)) {
                            drawn[this->count++] = CubeFace::face(
                                x, y, z, computeData(data, CubeData::FACE, opaqueAbove
                                )
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::BACK)) {
                            drawn[this->count++] = CubeFace::back(
                                x, y, z, computeData(data, CubeData::BACK, opaqueAbove
                                )
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::LEFT)) {
                            drawn[this->count++] = CubeFace::left(
                                x, y, z, computeData(data, CubeData::LEFT, opaqueAbove
                                )
                            );
                        }
                        if (!occluded(data, x, y, z, CubeData::RIGHT)) {
                            drawn[this->count++] = CubeFace::right(
                                x, y, z, computeData(data, CubeData::RIGHT, opaqueAbove)
                            );
                        }
                        opaqueAbove = true;
                    }
                }
            }
        }
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vboAlpha);
        glBufferData(
            GL_ARRAY_BUFFER, sizeof(CubeFace) * this->countAlpha, drawnAlpha, GL_STATIC_DRAW
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeFace) * this->count, drawn, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Set the VAO
        glBindVertexArray(this->vaoAlpha);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboAlpha);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glEnableVertexAttribArray(VERTEX_ATTR_DATA);
        glVertexAttribPointer(
            VERTEX_ATTR_POSITION, 3, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            reinterpret_cast<const GLvoid *>(offsetof(cube::CubeVertex, vertex))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_NORMAL, 3, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            reinterpret_cast<const GLvoid *>(offsetof(cube::CubeVertex, normal))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_TEXTURE, 2, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            reinterpret_cast<const GLvoid *>(offsetof(cube::CubeVertex, texture))
        );
        glVertexAttribIPointer(
            VERTEX_ATTR_DATA, 1, GL_SHORT, sizeof(cube::CubeVertex),
            reinterpret_cast<const GLvoid *>(offsetof(cube::CubeVertex, data))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glEnableVertexAttribArray(VERTEX_ATTR_DATA);
        glVertexAttribPointer(
            VERTEX_ATTR_POSITION, 3, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            reinterpret_cast<const GLvoid *>(offsetof(cube::CubeVertex, vertex))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_NORMAL, 3, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            reinterpret_cast<const GLvoid *>(offsetof(cube::CubeVertex, normal))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_TEXTURE, 2, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            reinterpret_cast<const GLvoid *>(offsetof(cube::CubeVertex, texture))
        );
        glVertexAttribIPointer(
            VERTEX_ATTR_DATA, 1, GL_UNSIGNED_SHORT, sizeof(cube::CubeVertex),
            reinterpret_cast<const GLvoid *>(offsetof(cube::CubeVertex, data))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        this->modified = false;
        return this->count + this->countAlpha;
    }
    
    
    GLuint Chunk::render(bool alpha) const {
        assert(!modified);
    
//        std::cout << this->position.x << " " << this->position.y << " " << this->position.z << std::endl;
        
        if (this->count + this->countAlpha == 0) {
            return 0;
        }
        
        if (!alpha) {
            glBindVertexArray(this->vao);
            glDrawArrays(GL_TRIANGLES, 0,
                         static_cast<GLsizei>(this->count * CubeFace::VERTICE_COUNT));
            glBindVertexArray(0);
            return this->count;
        }
        else {
            glBindVertexArray(this->vaoAlpha);
            glDrawArrays(GL_TRIANGLES, 0,
                         static_cast<GLsizei>(this->countAlpha * CubeFace::VERTICE_COUNT));
            glBindVertexArray(0);
            return this->countAlpha;
        }
    }
}

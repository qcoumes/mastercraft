#include <algorithm>
#include <iostream>

#include <effolkronium/random.hpp>
#include <glm/ext.hpp>

#include <app/Engine.hpp>
#include <cube/ChunkManager.hpp>
#include <cube/ColumnGenerator.hpp>
#include <cube/TreeGenerator.hpp>


using Random = effolkronium::random_static;

namespace cube {
    
    ChunkManager::ChunkManager(const misc::Image *t_cubeTexture) :
        textureVerticalOffset(0),
        temperatureNoise(
            { Random::get<float>(0., 100000.), Random::get<float>(0., 100000.) }, 5, 1.f, 1 / 258.f,
            0.5f, 2.f
        ),
        
        carvingNoise(
            {
                Random::get<float>(0., 100000.), Random::get<float>(0., 100000.),
                Random::get<float>(0., 100000.)
            },
            3, 1.f, 1 / 64.f, 0.5f, 2.f
        ),
        
        cubeTexture(shader::Texture(t_cubeTexture)),
        heightNoise({ Random::get<float>(0., 100000.), Random::get<float>(0., 100000.) }, 3, 1.f,
                    1 / 256.f, 0.5f, 2.f
        ) {
        
        cubeTexture.bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        cubeTexture.unbind();
    }
    
    
    void ChunkManager::generateKeys() {
        app::Engine *engine = app::Engine::getInstance();
        app::Config *config = app::Config::getInstance();
        
        glm::vec3 camera = engine->camera->getPosition();
        glm::ivec3 position = getSuperChunkCoordinates(camera);
        GLint distanceView = config->getDistanceView();
        
        GLint startx = position.x - distanceView * SuperChunk::X;
        GLint startz = position.z - distanceView * SuperChunk::Z;
        GLint endx = position.x + distanceView * SuperChunk::X;
        GLint endz = position.z + distanceView * SuperChunk::Z;
        
        std::vector<glm::ivec3> keys = std::vector<glm::ivec3>();
        for (GLint x = startx; x <= endx; x += SuperChunk::X) {
            for (GLint z = startz; z <= endz; z += SuperChunk::Z) {
                keys.emplace_back(x, 0, z);
            }
        }
        
        this->keys = keys;
    }
    
    
    CubeData ChunkManager::getBiome(GLuint height, GLfloat temperature) {
        assert(height >= app::Config::GEN_MIN_H);
        assert(height <= app::Config::GEN_MAX_H);
        
        static constexpr GLubyte sandLevel = app::Config::GEN_WATER_LEVEL + 3;
        static constexpr GLubyte dirtLevel = sandLevel + 18;
        static constexpr GLubyte stoneLevel = dirtLevel + 4;
        
        if (temperature < -0.30f) { // Snow biome
            if (height <= app::Config::GEN_WATER_LEVEL) {
                return CubeData::ICE;
            }
            if (height <= sandLevel) {
                return CubeData::SNOW;
            }
            if (height <= dirtLevel) {
                return CubeData::DIRT_SNOW;
            }
            if (height <= stoneLevel) {
                return CubeData::STONE_SNOW;
            }
            return CubeData::SNOW;
        }
        else if (temperature < -0.125f || (temperature > 0.125f && temperature < 0.30f)) {
            // Plain biome
            if (height <= app::Config::GEN_WATER_LEVEL) {
                return CubeData::WATER;
            }
            if (height <= sandLevel) {
                return CubeData::SAND_BEACH;
            }
            if (height <= dirtLevel) {
                return CubeData::DIRT_PLAIN;
            }
            if (height <= stoneLevel) {
                return CubeData::STONE;
            }
            return CubeData::STONE_SNOW;
        }
        else if (temperature < 0.125f) { // Jungle biome
            if (height <= app::Config::GEN_WATER_LEVEL) {
                return CubeData::WATER;
            }
            if (height <= sandLevel) {
                return CubeData::DIRT_JUNGLE;
            }
            if (height <= dirtLevel) {
                return CubeData::DIRT_JUNGLE;
            }
            if (height <= stoneLevel) {
                return CubeData::STONE;
            }
            return CubeData::STONE;
        }
        // Desert biome
        if (height <= app::Config::GEN_WATER_LEVEL) {
            return CubeData::WATER;
        }
        if (height <= sandLevel) {
            return CubeData::SAND_BEACH;
        }
        if (height <= dirtLevel) {
            return CubeData::SAND_DESERT;
        }
        if (height <= stoneLevel) {
            return CubeData::SAND_DESERT;
        }
        return CubeData::STONE;
    }
    
    
    glm::ivec3 ChunkManager::getSuperChunkCoordinates(const glm::ivec3 &position) {
        GLfloat x = (
            std::floor(static_cast<GLfloat>(position.x) / SuperChunk::X)
            * SuperChunk::X
        );
        GLfloat y = (
            std::floor(static_cast<GLfloat>(position.y) / SuperChunk::Y)
            * SuperChunk::Y
        );
        GLfloat z = (
            std::floor(static_cast<GLfloat>(position.z) / SuperChunk::Z)
            * SuperChunk::Z
        );
        
        return glm::ivec3(x, y, z);
    }
    
    
    SuperChunk *ChunkManager::createSuperChunk(glm::ivec3 position) {
        auto *chunk = new SuperChunk(position);
        std::array<CubeData, SuperChunk::Y> column {};
        CubeData biome;
        float temperature;
        GLubyte height;
        GLuint x, y, z, y2;
        
        // Set eight of each column
        for (x = 0; x < SuperChunk::X; x++) {
            for (z = 0; z < SuperChunk::Z; z++) {
                height = static_cast<GLubyte>(this->heightNoise(
                    { position.x + GLint(x), position.z + GLint(z) }, -1, 1,
                    app::Config::GEN_MIN_H,
                    app::Config::GEN_MAX_H
                ));
                for (y = 0; y <= height; y++) {
                    chunk->set(x, y, z, CubeData::STONE);
                }
                for (y = height + 1; y < SuperChunk::Y; y++) {
                    chunk->set(x, y, z, CubeData::AIR);
                }
            }
        }
        
        // Create more unusual terrain by subtracting 3D noise
        glm::vec3 point;
        for (x = 0; x < SuperChunk::X; x++) {
            for (y = app::Config::GEN_CARVING_H; y < app::Config::GEN_MAX_H;
                 y++) {
                for (z = 0; z < SuperChunk::Z; z++) {
                    point = { position.x + GLint(x), position.y + GLint(y), position.z + GLint(z) };
                    if (this->carvingNoise(point) > 0.f) {
                        chunk->set(x, y, z, CubeData::AIR);
                    }
                }
            }
        }
        
        // Generate biome over terrain
        for (x = 0; x < SuperChunk::X; x++) {
            for (z = 0; z < SuperChunk::Z; z++) {
                for (y = app::Config::GEN_MAX_H; y >= app::Config::GEN_MIN_H; y--) {
                    if (chunk->get(x, y, z) != CubeData::AIR) {
                        temperature = this->temperatureNoise(
                            { position.x + GLint(x), position.z + GLint(z) }
                        );
                        biome = ChunkManager::getBiome(y, temperature);
                        column = ColumnGenerator::generate(y, biome);
                        for (y2 = app::Config::GEN_MIN_H; y2 <= app::Config::GEN_MAX_H; y2++) {
                            chunk->set(x, y2, z, column[y2]);
                        }
                        break;
                    }
                }
            }
        }
        
        // Generate Tree or slimes on certain position
        for (x = 0; x < SuperChunk::X; x++) {
            for (z = 0; z < SuperChunk::Z; z++) {
                for (y = app::Config::GEN_MAX_H; y >= app::Config::GEN_MIN_H; y--) {
                    if (!(chunk->get(x, y, z) & NOT_FLOOR)) {
                        biome = chunk->get(x, y, z);
                        
                        // Try to generate a tree at position
                        Tree tree = TreeGenerator::generate({ x, y, z }, biome);
                        if (!tree.empty()) { // If a tree was generated
                            std::for_each(
                                tree.begin(), tree.end(),
                                [&chunk](const auto &e) {
                                    chunk->set(
                                        static_cast<GLuint>(e.first.x),
                                        static_cast<GLuint>(e.first.y),
                                        static_cast<GLuint>(e.first.z),
                                        e.second
                                    );
                                }
                            );
                        }
                        break;
                    }
                }
            }
        }
        
        GLint startx = position.x - SuperChunk::X;
        GLint startz = position.z - SuperChunk::Z;
        GLint endx = position.x + SuperChunk::X;
        GLint endz = position.z + SuperChunk::Z;
        for (GLint x = startx; x <= endx; x += SuperChunk::X) {
            for (GLint z = startz; z <= endz; z += SuperChunk::Z) {
                if (this->chunks.count({ x, 0, z })) {
                    this->chunks.at({ x, 0, z })->touch();
                }
            }
        }
        return chunk;
    }
    
    
    void ChunkManager::clearChunks() {
        this->chunks.clear();
    }
    
    
    CubeData ChunkManager::get(const glm::ivec3 &position) const {
        glm::ivec3 superChunk = this->getSuperChunkCoordinates(position);
        
        if (this->chunks.count(superChunk)) {
            return this->chunks.at(superChunk)->get(
                static_cast<GLuint>(position.x - superChunk.x),
                static_cast<GLuint>(position.y - superChunk.y),
                static_cast<GLuint>(position.z - superChunk.z)
            );
        }
        
        return CubeData::STONE;
    }
    
    
    void ChunkManager::init() {
        this->cubeShader = std::make_unique<shader::ShaderTexture>(
            "../shader/cube.vs.glsl", "../shader/cube.fs.glsl"
        );
        this->cubeShader->addUniform("uMV", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uChunkPosition", shader::UNIFORM_3_F);
        this->cubeShader->addUniform("uVerticalOffset", shader::UNIFORM_1_I);
        this->cubeShader->addUniform("uLightPosition", shader::UNIFORM_3_F);
        this->cubeShader->addUniform("uLightColor", shader::UNIFORM_3_F);
        this->cubeShader->addUniform("uLightDirIntensity", shader::UNIFORM_1_F);
        this->cubeShader->addUniform("uLightAmbIntensity", shader::UNIFORM_1_F);
    }
    
    
    void ChunkManager::update() {
        app::Config *config = app::Config::getInstance();
        
        this->textureVerticalOffset = (this->textureVerticalOffset + 1) % 32;
        
        generateKeys();
        
        // Delete superChunk outside distanceView
        std::vector<glm::ivec3> toErase;
        for (const auto &entry : this->chunks) {
            if (!std::count(this->keys.begin(), this->keys.end(), entry.first)) {
                toErase.push_back(entry.first);
            }
        }
        for (const auto &key : toErase) {
            this->chunks.erase(key);
        }
        
        // Add new superChunk that entered distanceView
        std::for_each(
            this->keys.begin(), this->keys.end(),
            [this](const auto &key) {
                if (!this->chunks.count(key)) {
                    this->chunks.emplace(key, this->createSuperChunk(key));
                }
            }
        );
        
        
        // Update superChunks
        std::for_each(
            this->chunks.begin(), this->chunks.end(),
            [](const auto &entry) { entry.second->update(); }
        );
        
        config->l_superchunk = static_cast<GLuint>(this->chunks.size());
        config->l_chunk = config->l_superchunk * SuperChunk::CHUNK_SIZE;
        config->l_cube = config->l_superchunk * SuperChunk::SIZE;
        config->l_face = config->l_cube * 6;
    }
    
    
    void ChunkManager::render() {
        app::Engine *engine = app::Engine::getInstance();
        app::Config *config = app::Config::getInstance();
    
        config->getFaceCulling() ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
        config->r_superchunk = 0;
        config->r_chunk = 0;
        config->r_cube = 0;
        config->r_face = 0;
        
        glm::mat4 MVMatrix = engine->camera->getViewMatrix();
        glm::mat4 MVPMatrix = engine->camera->getProjMatrix() * MVMatrix;
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(MVMatrix));
        
        glm::vec3 lightPos = glm::vec3(MVMatrix * glm::vec4(engine->world->sun->getPosition(), 0));
        glm::vec3 lightColor = app::Config::getLightColor(engine->world->tickCycle);
        if (engine->world->underwater) {
            lightColor *= glm::vec3(0.36, 0.56, 1);
        }
        GLfloat lightDirIntensity = app::Config::getLightDirIntensity(engine->world->tickCycle);
        GLfloat lightAmbIntensity = app::Config::getLightAmbIntensity(engine->world->tickCycle);
        
        this->cubeShader->use();
        this->cubeShader->loadUniform("uMV", glm::value_ptr(MVMatrix));
        this->cubeShader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        this->cubeShader->loadUniform("uNormal", glm::value_ptr(normalMatrix));
        this->cubeShader->loadUniform("uVerticalOffset", &this->textureVerticalOffset);
        this->cubeShader->loadUniform("uLightPosition", glm::value_ptr(lightPos));
        this->cubeShader->loadUniform("uLightColor", glm::value_ptr(lightColor));
        this->cubeShader->loadUniform("uLightDirIntensity", &lightDirIntensity);
        this->cubeShader->loadUniform("uLightAmbIntensity", &lightAmbIntensity);
        this->cubeShader->bindTexture(this->cubeTexture);
        
        std::for_each(
            this->chunks.begin(), this->chunks.end(),
            [&config](const auto &entry) { config->r_face += entry.second->render(false); }
        );
        glDisable(GL_CULL_FACE);
        std::for_each(
            this->chunks.begin(), this->chunks.end(),
            [&config](const auto &entry) { config->r_face += entry.second->render(true); }
        );
        glEnable(GL_CULL_FACE);
        
        this->cubeShader->unbindTexture();
        this->cubeShader->stop();
    }
}

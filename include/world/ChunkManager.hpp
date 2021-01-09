#ifndef MASTERCRAFT_CHUNKMANAGER_HPP
#define MASTERCRAFT_CHUNKMANAGER_HPP

#include <map>
#include <vector>
#include <memory>
#include <unordered_map>

#include <glm/gtc/noise.hpp>

#include <misc/INonCopyable.hpp>
#include <shader/ShaderTexture.hpp>
#include <misc/Noise.hpp>
#include <world/SuperChunk.hpp>


namespace world {
    
    typedef misc::Noise<glm::vec2, float, glm::simplex> Noise2D;
    typedef misc::Noise<glm::vec3, float, glm::simplex> Noise3D;
    
    
    
    struct Ivec3Hash {
        size_t operator()(const glm::ivec3 &k) const {
            return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
        }
        
        
        bool operator()(const glm::ivec3 &a, const glm::ivec3 &b) const {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }
    };
    
    
    
    class ChunkManager : public misc::INonCopyable {
        
        private:
            std::unordered_map<glm::ivec3, std::unique_ptr<world::SuperChunk>, Ivec3Hash> chunks;
            std::vector<glm::ivec3> keys;
            GLuint textureVerticalOffset;
            Noise2D temperatureNoise;
            Noise3D carvingNoise;
        
        public:
            std::unique_ptr<shader::ShaderTexture> cubeShader;
            shader::Texture cubeTexture;
            
            Noise2D heightNoise;
        
        private:
            
            void generateKeys();
            
            [[nodiscard]] static world::CubeData getBiome(GLuint height, GLfloat temperature);
            
            [[nodiscard]] static glm::ivec3 getSuperChunkCoordinates(const glm::ivec3 &position);
            
            [[nodiscard]] world::SuperChunk *createSuperChunk(glm::ivec3 position);
        
        public:
            
            explicit ChunkManager(const misc::Image *t_cubeTexture);
            
            void clearChunks();
            
            [[nodiscard]] world::CubeData get(const glm::ivec3 &position) const;
            
            void init();
            
            void update();
            
            void render();
    };
}

#endif // MASTERCRAFT_CHUNKMANAGER_HPP

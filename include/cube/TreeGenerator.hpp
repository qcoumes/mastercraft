#ifndef OPENGL_TREEGENERATOR_HPP
#define OPENGL_TREEGENERATOR_HPP

#include <vector>
#include <utility>

#include <glm/vec3.hpp>

#include <cube/CubeData.hpp>


namespace cube {
    
    typedef std::vector<std::pair<glm::ivec3, CubeData>> Tree;
    
    
    
    class TreeGenerator {
        
        private:
            
            [[nodiscard]] static Tree plainTree(glm::ivec3 position);
            
            [[nodiscard]] static Tree jungleTree(glm::ivec3 position);
            
            [[nodiscard]] static Tree snowTree(glm::ivec3 position);
            
            [[nodiscard]] static Tree cactus(glm::ivec3 position);
        
        public:
            
            TreeGenerator() = delete;
            
            [[nodiscard]] static Tree generate(glm::ivec3 position, CubeData biome);
    };
}

#endif //OPENGL_TREEGENERATOR_HPP

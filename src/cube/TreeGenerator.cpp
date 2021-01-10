#include <exception>

#include <effolkronium/random.hpp>

#include <cube/TreeGenerator.hpp>
#include <app/Engine.hpp>


using Random = effolkronium::random_static;

namespace cube {
    
    Tree TreeGenerator::plainTree(glm::ivec3 position) {
        if (position.x + 5 >= SuperChunk::X || position.x - 5 < 0
            || position.z + 5 >= SuperChunk::Z || position.z - 5 < 0) {
            return Tree();
        }
        
        int32_t trunk = Random::get(6, 10);
        Tree tree;
        
        for (int32_t i = 0; i < trunk; i++) {
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i, position.z),
                CubeData::WOOD_PLAIN
            );
        }
        
        for (int32_t i = 1; i < 4; i++) {
            tree.emplace_back(
                glm::ivec3(position.x + i, position.y + 1 + 4, position.z),
                CubeData::LEAVES_PLAIN
            );
            if (trunk > 8) {
                tree.emplace_back(
                    glm::ivec3(position.x - i, position.y + 1 + 7, position.z),
                    CubeData::LEAVES_PLAIN
                );
            }
        }
        
        if (trunk > 8) {
            //one floor
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + 7, position.z - 1),
                CubeData::LEAVES_PLAIN
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + 7, position.z + 1),
                CubeData::LEAVES_PLAIN
            );
            tree.emplace_back(
                glm::ivec3(position.x - 2, position.y + 1 + 7, position.z - 1),
                CubeData::LEAVES_PLAIN
            );
            tree.emplace_back(
                glm::ivec3(position.x - 2, position.y + 1 + 7, position.z + 1),
                CubeData::LEAVES_PLAIN
            );
            
            //two floor
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + 8, position.z + 1),
                CubeData::LEAVES_PLAIN
            );
            tree.emplace_back(
                glm::ivec3(position.x - 2, position.y + 1 + 8, position.z - 1),
                CubeData::LEAVES_PLAIN
            );
            tree.emplace_back(
                glm::ivec3(position.x - 2, position.y + 1 + 8, position.z),
                CubeData::LEAVES_PLAIN
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + 8, position.z),
                CubeData::LEAVES_PLAIN
            );
        }
        
        //one floor
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 4, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 4, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + 4, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + 4, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 4, position.z + 2),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 4, position.z - 2),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 4, position.z + 2),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 4, position.z - 2),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 4, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 4, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 4, position.y + 1 + 4, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 4, position.y + 1 + 4, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 4, position.y + 1 + 4, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 5, position.y + 1 + 4, position.z),
            CubeData::LEAVES_PLAIN
        );
        
        
        //two floor
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 5, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 5, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + 5, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 5, position.z - 2),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 5, position.z + 2),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 5, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 5, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 4, position.y + 1 + 5, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 5, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 5, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + 5, position.z),
            CubeData::LEAVES_PLAIN
        );
        
        //three floor
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 6, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 6, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + 6, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + 6, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + 6, position.z),
            CubeData::LEAVES_PLAIN
        );
        
        
        //head one floor
        tree.emplace_back(
            glm::ivec3(position.x + 3, position.y + 1 + trunk, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + trunk, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + trunk, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x, position.y + 1 + trunk, position.z),
            CubeData::LEAVES_PLAIN
        );
        
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + trunk, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + trunk, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + trunk, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + trunk, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x, position.y + 1 + trunk, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x, position.y + 1 + trunk, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        
        //head two floor
        tree.emplace_back(
            glm::ivec3(position.x + 2, position.y + 1 + trunk + 1, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + trunk + 1, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x, position.y + 1 + trunk + 1, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x - 1, position.y + 1 + trunk + 1, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x - 2, position.y + 1 + trunk + 1, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x - 2, position.y + 1 + trunk + 1, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x - 2, position.y + 1 + trunk + 1, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x - 1, position.y + 1 + trunk + 1, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x - 1, position.y + 1 + trunk + 1, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + trunk + 1, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + trunk + 1, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x, position.y + 1 + trunk + 1, position.z + 1),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x, position.y + 1 + trunk + 1, position.z - 1),
            CubeData::LEAVES_PLAIN
        );
        
        //head three floor
        tree.emplace_back(
            glm::ivec3(position.x, position.y + 1 + trunk + 2, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x + 1, position.y + 1 + trunk + 2, position.z),
            CubeData::LEAVES_PLAIN
        );
        tree.emplace_back(
            glm::ivec3(position.x - 1, position.y + 1 + trunk + 2, position.z),
            CubeData::LEAVES_PLAIN
        );
        
        return tree;
    }
    
    
    Tree TreeGenerator::jungleTree(glm::ivec3 position) {
        if (position.x + 6 >= SuperChunk::X || position.x - 2 < 0
            || position.z + 1 >= SuperChunk::Z || position.z - 1 < 0) {
            return Tree();
        }
        
        int32_t trunk = Random::get(4, 5);
        Tree tree;
        for (int32_t i = 0; i < 2; i++) {
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i, position.z),
                CubeData::WOOD_JUNGLE
            );
        }
        if (trunk == 4) {
            for (int32_t i = 0; i < 2; i++) {
                tree.emplace_back(
                    glm::ivec3(position.x + 1 + i, position.y + 1 + i + 2, position.z),
                    CubeData::WOOD_JUNGLE
                );
                tree.emplace_back(
                    glm::ivec3(position.x, position.y + 1 + i + 2, position.z),
                    CubeData::WOOD_JUNGLE
                );
            }
            
            //one floor
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + trunk, position.z),
                CubeData::WOOD_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 1, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 2, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 4, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            
            tree.emplace_back(
                glm::ivec3(position.x + 3, position.y + 1 + trunk, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 2, position.y + 1 + trunk, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3, position.y + 1 + trunk, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 2, position.y + 1 + trunk, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
            
            //two floor
            tree.emplace_back(
                glm::ivec3(position.x + 2, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 1, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x - 2, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            
            tree.emplace_back(
                glm::ivec3(position.x + 1, position.y + 1 + trunk + 1, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + trunk + 1, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + trunk + 1, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 1, position.y + 1 + trunk + 1, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + trunk + 1, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + trunk + 1, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
        }
        else {
            for (int32_t i = 0; i < 3; i++) {
                tree.emplace_back(
                    glm::ivec3(position.x + 1 + i, position.y + 1 + i + 2, position.z),
                    CubeData::WOOD_JUNGLE
                );
            }
            
            //one floor
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 1, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 2, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 3, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            
            tree.emplace_back(
                glm::ivec3(position.x + 3, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 - 1, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 - 2, position.y + 1 + trunk, position.z),
                CubeData::LEAVES_JUNGLE
            );
            
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 2, position.y + 1 + trunk, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 1, position.y + 1 + trunk, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3, position.y + 1 + trunk, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 - 1, position.y + 1 + trunk, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 2, position.y + 1 + trunk, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 1, position.y + 1 + trunk, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3, position.y + 1 + trunk, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
            
            //two floor
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 1, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 2, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 - 1, position.y + 1 + trunk + 1, position.z),
                CubeData::LEAVES_JUNGLE
            );
            
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 1, position.y + 1 + trunk + 1, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3, position.y + 1 + trunk + 1, position.z + 1),
                CubeData::LEAVES_JUNGLE
            );
            tree.emplace_back(
                glm::ivec3(position.x + 3 + 1, position.y + 1 + trunk + 1, position.z - 1),
                CubeData::LEAVES_JUNGLE
            );
        }
        
        return tree;
    }
    
    
    Tree TreeGenerator::snowTree(glm::ivec3 position) {
        if (position.x + 2 >= SuperChunk::X || position.x - 2 < 0
            || position.z + 2 >= SuperChunk::Z || position.z - 2 < 0) {
            return Tree();
        }
        
        int32_t trunk = Random::get(2, 3);
        int32_t leaves = Random::get(0, 3);
        Tree tree;
        
        if (leaves != 0) {
            for (int32_t i = 0; i < trunk; i++) {
                tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i, position.z),
                                  CubeData::WOOD_SNOW
                );
            }
        }
        else {
            tree.emplace_back(glm::ivec3(position.x, position.y + 1, position.z),
                              CubeData::WOOD_SNOW
            );
        }
        
        for (int32_t i = 0; i < leaves; i += 1) {
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + trunk, position.z),
                CubeData::WOOD_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + trunk + 1, position.z),
                CubeData::WOOD_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + trunk + 2, position.z),
                CubeData::WOOD_SNOW
            );
            
            
            
            
            // one floor
            tree.emplace_back(
                glm::ivec3(position.x + 1, position.y + 1 + i * 3 + 1 + trunk, position.z),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + i * 3 + 1 + trunk, position.z),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + 1 + trunk, position.z + 1),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + 1 + trunk, position.z - 1),
                CubeData::LEAVES_SNOW
            );
            
            tree.emplace_back(
                glm::ivec3(position.x + 1, position.y + 1 + i * 3 + 1 + trunk, position.z + 1),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + i * 3 + 1 + trunk, position.z + 1),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + i * 3 + 1 + trunk, position.z + 1),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x + 1, position.y + 1 + i * 3 + 1 + trunk, position.z - 1),
                CubeData::LEAVES_SNOW
            );
            
            tree.emplace_back(
                glm::ivec3(position.x + 2, position.y + 1 + i * 3 + 1 + trunk, position.z),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x - 2, position.y + 1 + i * 3 + 1 + trunk, position.z),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + 1 + trunk, position.z + 2),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + 1 + trunk, position.z - 2),
                CubeData::LEAVES_SNOW
            );
            
            
            // two floor
            tree.emplace_back(
                glm::ivec3(position.x + 1, position.y + 1 + i * 3 + 2 + trunk, position.z),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x - 1, position.y + 1 + i * 3 + 2 + trunk, position.z),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + 2 + trunk, position.z + 1),
                CubeData::LEAVES_SNOW
            );
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i * 3 + 2 + trunk, position.z - 1),
                CubeData::LEAVES_SNOW
            );
        }
        //three floor
        if (leaves != 0) {
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + leaves * 3 + trunk, position.z),
                CubeData::LEAVES_SNOW
            );
        }
        return tree;
    }
    
    
    Tree TreeGenerator::cactus(glm::ivec3 position) {
        int32_t limit = Random::get(2, 5);
        Tree tree;
        
        for (int32_t i = 0; i < limit; i++) {
            tree.emplace_back(
                glm::ivec3(position.x, position.y + 1 + i, position.z),
                CubeData::CACTUS
            );
        }
        
        return tree;
    }
    
    
    Tree TreeGenerator::generate(glm::ivec3 position, CubeData biome) {
        switch (biome) {
            case DIRT_PLAIN:
                if (Random::get<bool>(0.01)) {
                    return plainTree(position);
                }
                break;
            case DIRT_JUNGLE:
                if (Random::get<bool>(0.1)) {
                    return jungleTree(position);
                }
                break;
            case DIRT_SNOW:
                if (Random::get<bool>(0.005)) {
                    return snowTree(position);
                }
                break;
            case SAND_DESERT:
                if (Random::get<bool>(0.005)) {
                    return cactus(position);
                }
                break;
            case AIR:
            case WATER:
            case SAND_BEACH:
            case ICE:
            case SNOW:
            case STONE:
            case STONE_SNOW:
            case FLOWERS:
            case WOOD_PLAIN:
            case WOOD_JUNGLE:
            case WOOD_SNOW:
            case CACTUS:
            case LEAVES_PLAIN:
            case LEAVES_JUNGLE:
            case LEAVES_SNOW:
                break;
            default:
                throw std::runtime_error("Invalid block type.");
        }
        
        return {};
    }
}

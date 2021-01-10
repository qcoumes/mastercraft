#ifndef OPENGL_COLUMNGENERATOR_HPP
#define OPENGL_COLUMNGENERATOR_HPP

#include <array>

#include <GL/glew.h>

#include <cube/CubeData.hpp>
#include <cube/SuperChunk.hpp>


namespace cube {
    
    class ColumnGenerator {
        
        private:
            typedef std::array<CubeData, SuperChunk::Y> Column;
            
            [[nodiscard]] static Column waterColumn(GLuint height);
            
            [[nodiscard]] static Column iceColumn(GLuint height);
            
            [[nodiscard]] static Column sandBeachColumn(GLuint height);
            
            [[nodiscard]] static Column sandDesertColumn(GLuint height);
            
            [[nodiscard]] static Column snowColumn(GLuint height);
            
            [[nodiscard]] static Column stoneColumn(GLuint height);
            
            [[nodiscard]] static Column stoneSnowColumn(GLuint height);
            
            [[nodiscard]] static Column dirtPlainColumn(GLuint height);
            
            [[nodiscard]] static Column dirtJungleColumn(GLuint height);
            
            [[nodiscard]] static Column dirtSnowColumn(GLuint height);
        
        public:
            
            ColumnGenerator() = delete;
            
            [[nodiscard]] static std::array<CubeData, SuperChunk::Y> generate(GLuint height,
                                                                              CubeData type);
    };
}

#endif //OPENGL_COLUMNGENERATOR_HPP

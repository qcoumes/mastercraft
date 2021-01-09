

#include <world/CubeFace.hpp>


namespace world {
    
    CubeFace world::CubeFace::face(GLubyte x, GLubyte y, GLubyte z, GLushort data) {
        CubeFace face{};
        
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, 0, 1 }, { 1, 1 }, data),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, 0, 1 }, { 0, 1 }, data),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 0, 1 }, { 0, 0 }, data),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 0, 1 }, { 0, 0 }, data),
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 0, 1 }, { 1, 0 }, data),
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, 0, 1 }, { 1, 1 }, data),
        };
        
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::top(GLubyte x, GLubyte y, GLubyte z, GLushort data) {
        CubeFace face{};
        
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 1, 0 }, { 1, 1 }, data),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 1, 0 }, { 0, 1 }, data),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 1, 0 }, { 0, 0 }, data),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 1, 0 }, { 0, 0 }, data),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 1, 0 }, { 1, 0 }, data),
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 1, 0 }, { 1, 1 }, data),
        };
        
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::back(GLubyte x, GLubyte y, GLubyte z, GLushort data) {
        CubeFace face{};
        
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, 0, -1 }, { 1, 1 }, data),
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, 0, -1 }, { 0, 1 }, data),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 0, -1 }, { 0, 0 }, data),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 0, -1 }, { 0, 0 }, data),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 0, -1 }, { 1, 0 }, data),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, 0, -1 }, { 1, 1 }, data),
        };
        
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::bottom(GLubyte x, GLubyte y, GLubyte z, GLushort data) {
        CubeFace face{};
        
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, -1, 0 }, { 1, 1 }, data),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, -1, 0 }, { 0, 1 }, data),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, -1, 0 }, { 0, 0 }, data),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, -1, 0 }, { 0, 0 }, data),
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, -1, 0 }, { 1, 0 }, data),
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, -1, 0 }, { 1, 1 }, data),
        };
        
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::left(GLubyte x, GLubyte y, GLubyte z, GLushort data) {
        CubeFace face{};
        
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 0, y + 0, z + 0 }, { -1, 0, 0 }, { 1, 1 }, data),
            CubeVertex({ x + 0, y + 0, z + 1 }, { -1, 0, 0 }, { 0, 1 }, data),
            CubeVertex({ x + 0, y + 1, z + 1 }, { -1, 0, 0 }, { 0, 0 }, data),
            CubeVertex({ x + 0, y + 1, z + 1 }, { -1, 0, 0 }, { 0, 0 }, data),
            CubeVertex({ x + 0, y + 1, z + 0 }, { -1, 0, 0 }, { 1, 0 }, data),
            CubeVertex({ x + 0, y + 0, z + 0 }, { -1, 0, 0 }, { 1, 1 }, data),
        };
        
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::right(GLubyte x, GLubyte y, GLubyte z, GLushort data) {
        CubeFace face{};
        
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 1, y + 0, z + 1 }, { 1, 0, 0 }, { 1, 1 }, data),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 1, 0, 0 }, { 0, 1 }, data),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 1, 0, 0 }, { 0, 0 }, data),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 1, 0, 0 }, { 0, 0 }, data),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 1, 0, 0 }, { 1, 0 }, data),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 1, 0, 0 }, { 1, 1 }, data),
        };
        
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
}

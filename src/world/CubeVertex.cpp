#include <world/CubeVertex.hpp>


namespace world {
    
    CubeVertex::CubeVertex(glm::cvec3 t_vertex, glm::cvec3 t_normal, glm::cvec2 t_texture, GLushort t_data) :
        vertex(t_vertex), normal(t_normal), texture(t_texture), data(t_data) {
    }
}



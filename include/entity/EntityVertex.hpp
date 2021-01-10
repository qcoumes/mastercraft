#ifndef OPENGL_ENTITYVERTEX_HPP
#define OPENGL_ENTITYVERTEX_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


namespace entity {
    
    struct EntityVertex {
        glm::vec3 vertex;
        glm::vec3 normal;
        glm::vec2 texture;
    
        EntityVertex() = default;
    
        EntityVertex(glm::vec3 vertex, glm::vec3 normal, glm::vec2 texture);
        
        EntityVertex operator+(const glm::vec3 &position) const;
    };
}

#endif //OPENGL_ENTITYVERTEX_HPP

#ifndef OPENGL_CUBEVERTEX_HPP
#define OPENGL_CUBEVERTEX_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <cube/CubeData.hpp>


namespace glm {
    typedef glm::tvec3<GLbyte> cvec3;
    typedef glm::tvec2<GLbyte> cvec2;
}


namespace cube {
    
    struct CubeVertex {
        glm::cvec3 vertex;
        glm::cvec3 normal;
        glm::cvec2 texture;
        GLushort data;
        
        CubeVertex() = default;
        
        CubeVertex(glm::cvec3 vertex, glm::cvec3 normal, glm::cvec2 texture, GLushort data = CubeData::AIR);
    };
}
#endif // OPENGL_CUBEVERTEX_HPP

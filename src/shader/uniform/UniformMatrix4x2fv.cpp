#include <shader/uniform/UniformMatrix4x2fv.hpp>


namespace shader {
    
    void UniformMatrix4x2fv::load(const void *value) {
        glUniformMatrix4x2fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}

#include <shader/uniform/UniformMatrix3x4fv.hpp>


namespace shader {
    
    void UniformMatrix3x4fv::load(const void *value) {
        glUniformMatrix3x4fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}

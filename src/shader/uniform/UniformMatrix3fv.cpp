#include <shader/uniform/UniformMatrix3fv.hpp>


namespace shader {
    
    void UniformMatrix3fv::load(const void *value) {
        glUniformMatrix3fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}

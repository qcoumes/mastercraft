#include <shader/uniform/UniformMatrix4fv.hpp>


namespace shader {
    
    void UniformMatrix4fv::load(const void *value) {
        glUniformMatrix4fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}

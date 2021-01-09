#include <shader/uniform/Uniform3fv.hpp>


namespace shader {
    
    void Uniform3fv::load(const void *value) {
        glUniform3fv(this->location, 1, static_cast<const GLfloat *>(value));
    }
}

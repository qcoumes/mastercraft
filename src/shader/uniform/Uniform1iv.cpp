#include <shader/uniform/Uniform1iv.hpp>


namespace shader {
    
    void Uniform1iv::load(const void *value) {
        glUniform1iv(this->location, 1, static_cast<const GLint *>(value));
    }
}

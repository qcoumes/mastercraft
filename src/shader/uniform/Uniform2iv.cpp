#include <shader/uniform/Uniform2iv.hpp>


namespace shader {
    
    void Uniform2iv::load(const void *value) {
        glUniform2iv(this->location, 1, static_cast<const GLint *>(value));
    }
}

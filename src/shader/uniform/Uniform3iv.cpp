#include <shader/uniform/Uniform3iv.hpp>


namespace shader {
    
    void Uniform3iv::load(const void *value) {
        glUniform3iv(this->location, 1, static_cast<const GLint *>(value));
    }
}

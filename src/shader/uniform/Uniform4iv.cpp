#include <shader/uniform/Uniform4iv.hpp>


namespace shader {
    
    void Uniform4iv::load(const void *value) {
        glUniform4iv(this->location, 1, static_cast<const GLint *>(value));
    }
}

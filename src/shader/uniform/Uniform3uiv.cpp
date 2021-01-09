#include <shader/uniform/Uniform3uiv.hpp>


namespace shader {
    
    void Uniform3uiv::load(const void *value) {
        glUniform3uiv(this->location, 1, static_cast<const GLuint *>(value));
    }
}

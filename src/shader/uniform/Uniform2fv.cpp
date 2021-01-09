#include <shader/uniform/Uniform2fv.hpp>


namespace shader {
    
    void Uniform2fv::load(const void *value) {
        glUniform2fv(this->location, 1, static_cast<const GLfloat *>(value));
    }
}

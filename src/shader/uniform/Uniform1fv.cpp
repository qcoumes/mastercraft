#include <shader/uniform/Uniform1fv.hpp>


namespace shader {
    
    void Uniform1fv::load(const void *value) {
        glUniform1fv(this->location, 1, static_cast<const GLfloat *>(value));
    }
}

#include <shader/uniform/UniformSampler2D.hpp>


namespace shader {
    
    void UniformSampler2D::load(const void *value) {
        glUniform1iv(this->location, 1, static_cast<const GLint *>(value));
    }
}

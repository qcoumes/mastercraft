#include <iostream>

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    IUniform::IUniform(GLuint t_program, const GLchar *t_name) :
            name(t_name), program(t_program) {
        
        this->location = glGetUniformLocation(t_program, t_name);
        if (this->location == -1) {
            std::cerr << "Warning: '" << name << "' does not correspond to an active uniform variable in program '"
                      << t_program << "'." << std::endl;
        }
    }
}

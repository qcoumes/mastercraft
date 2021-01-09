#ifndef OPENGL_UNIFORMMATRIX32_HPP
#define OPENGL_UNIFORMMATRIX32_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class UniformMatrix3x2fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORMMATRIX32_HPP

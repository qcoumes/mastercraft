#ifndef OPENGL_UNIFORMMATRIX42_HPP
#define OPENGL_UNIFORMMATRIX42_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class UniformMatrix4x2fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORMMATRIX42_HPP

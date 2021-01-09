#ifndef OPENGL_UNIFORMMATRIX4_HPP
#define OPENGL_UNIFORMMATRIX4_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class UniformMatrix4fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORMMATRIX4_HPP

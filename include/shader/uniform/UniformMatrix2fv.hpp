#ifndef OPENGL_UNIFORMMATRIX2_HPP
#define OPENGL_UNIFORMMATRIX2_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class UniformMatrix2fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORMMATRIX2_HPP

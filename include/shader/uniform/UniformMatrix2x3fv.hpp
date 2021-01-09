#ifndef OPENGL_UNIFORMATRIX23_HPP
#define OPENGL_UNIFORMATRIX23_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class UniformMatrix2x3fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORMATRIX23_HPP

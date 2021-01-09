#ifndef OPENGL_UNIFORM3FV_HPP
#define OPENGL_UNIFORM3FV_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class Uniform3fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORM3FV_HPP

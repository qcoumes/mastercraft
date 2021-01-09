#ifndef OPENGL_UNIFORM1iv_HPP
#define OPENGL_UNIFORM1iv_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class Uniform1iv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORM1iv_HPP

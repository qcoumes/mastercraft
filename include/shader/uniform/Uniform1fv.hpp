#ifndef OPENGL_UNIFORM1FV_HPP
#define OPENGL_UNIFORM1FV_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class Uniform1fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORM1FV_HPP

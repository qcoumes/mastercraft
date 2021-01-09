#ifndef OPENGL_UNIFORM4iv_HPP
#define OPENGL_UNIFORM4iv_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class Uniform4iv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORM4iv_HPP

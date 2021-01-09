#ifndef OPENGL_UNIFORM1uiv_HPP
#define OPENGL_UNIFORM1uiv_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class Uniform1uiv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORM1uiv_HPP

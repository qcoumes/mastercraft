#ifndef OPENGL_UNIFORMSAMPLER2D_HPP
#define OPENGL_UNIFORMSAMPLER2D_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class UniformSampler2D : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORMSAMPLER2D_HPP

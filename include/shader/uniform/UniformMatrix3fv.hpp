#ifndef OPENGL_UNIFORMMAXTRIX3_HPP
#define OPENGL_UNIFORMMAXTRIX3_HPP

#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class UniformMatrix3fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif // OPENGL_UNIFORMMAXTRIX3_HPP

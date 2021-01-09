#ifndef OPENGL_SHADERTEXTURE_HPP
#define OPENGL_SHADERTEXTURE_HPP

#include <shader/Shader.hpp>
#include <shader/Texture.hpp>


namespace shader {
    
    class ShaderTexture : public Shader {
        private:
            GLint uTexture = -1;
        
        public:
            
            ShaderTexture() = default;
            
            ShaderTexture(const std::string &vsFile, const std::string &fsFile);
            
            void bindTexture(const Texture &texture) const;
            
            void unbindTexture() const;
    };
}

#endif // OPENGL_SHADERTEXTURE_HPP


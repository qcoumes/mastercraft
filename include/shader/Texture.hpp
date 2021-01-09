#ifndef OPENGL_TEXTURE_HPP
#define OPENGL_TEXTURE_HPP

#include <memory>

#include <GL/glew.h>

#include <misc/INonCopyable.hpp>
#include <misc/Image.hpp>


namespace shader {
    
    class Texture {
        private:
            GLuint textureId = 0;
            
            explicit Texture(GLuint textureId);
        
        public:
            
            Texture() = default;
            
            explicit Texture(const misc::Image *texture);
            
            void bind() const;
            
            void unbind() const;
    };
}

#endif // OPENGL_TEXTURE_HPP

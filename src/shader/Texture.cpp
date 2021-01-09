#include <shader/Texture.hpp>


namespace shader {
    
    Texture::Texture(const misc::Image *texture) {
        glGenTextures(1, &this->textureId);
        
        glBindTexture(GL_TEXTURE_2D, this->textureId);
        glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(texture->getWidth()),
                static_cast<GLsizei>(texture->getHeight()), 0, GL_RGBA, GL_FLOAT, texture->getPixels()
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    Texture::Texture(GLuint t_textureId) :
            textureId(t_textureId) {
    }
    
    
    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, this->textureId);
    }
    
    
    void Texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

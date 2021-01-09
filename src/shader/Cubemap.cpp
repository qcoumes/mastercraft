#include <shader/Cubemap.hpp>


namespace shader {
    
    Cubemap::Cubemap(std::unique_ptr<misc::Image> texture[6]) {
        glGenTextures(1, &this->textureId);
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
        
        for (GLuint i = 0; i < 6; i++) {
            glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, static_cast<GLsizei>(texture[i]->getWidth()),
                    static_cast<GLsizei>(texture[i]->getHeight()), 0, GL_RGBA, GL_FLOAT, texture[i]->getPixels()
            );
        }
        
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    
    
    GLuint Cubemap::getCubemapId() const {
        return this->textureId;
    }
}

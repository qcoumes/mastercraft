#include <shader/ShaderCubemap.hpp>


namespace shader {
    
    ShaderCubemap::ShaderCubemap(const std::string &vsFile, const std::string &fsFile) :
            Shader(vsFile, fsFile) {
        this->uTexture = glGetUniformLocation(this->programId, "uTexture");
    }
    
    
    void ShaderCubemap::bindCubemap(const Cubemap &texture) const {
        glUniform1i(this->uTexture, 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture.getCubemapId());
    }
    
    
    void ShaderCubemap::unbindCubemap() const {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}

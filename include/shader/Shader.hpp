#ifndef OPENGL_SHADER_HPP
#define OPENGL_SHADER_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <misc/INonCopyable.hpp>
#include <shader/uniform/IUniform.hpp>


namespace shader {
    
    class Shader : public misc::INonCopyable {
        protected:
            std::unordered_map<std::string, std::shared_ptr<IUniform>> uniforms;
            GLuint programId;
            GLuint vsId;
            GLuint fsId;
        
        public:
            
            Shader() = default;
            
            Shader(const std::string &vsPath, const std::string &fsPath);
            
            ~Shader();
            
            void addUniform(const std::string &name, UniformType type);
            
            void loadUniform(const std::string &name, const void *value) const;
            
            void use() const;
            
            void stop() const;
    };
}

#endif // OPENGL_SHADER_HPP


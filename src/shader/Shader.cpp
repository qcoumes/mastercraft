#include <algorithm>
#include <iostream>

#include <shader/Shader.hpp>
#include <shader/uniform/uniform_all.hpp>
#include <misc/FileReader.hpp>


namespace shader {
    
    static std::string getHeader(const std::string &driver) {
        std::string header;
        
        if (driver.find("NVIDIA") != std::string::npos) {
            header = "#version 330 core";
        }
        else if (driver.find("Mesa") != std::string::npos) {
            header = "#version 300 es\n\nprecision mediump float;";
        }
        else {
            throw std::runtime_error("Error : Unknown driver : " + driver);
        }
        
        return header;
    }
    
    
    static std::string addVersion(const std::string &shaderSrc) {
        static const std::string driver = std::string(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
        static const std::string header = getHeader(driver);
        
        std::string newSrc = shaderSrc;
        newSrc = newSrc.replace(0, 13, header);
        
        return newSrc;
    }
    
    
    static std::string getProgramInfoLog(GLuint programId) {
        std::string logString;
        GLint length;
        char *log;
        
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
        log = new char[static_cast<GLuint64>(length)];
        glGetProgramInfoLog(programId, length, nullptr, log);
        
        logString = log;
        delete[] log;
        
        return logString;
    }
    
    
    static std::string getShaderInfoLog(GLuint shaderId) {
        std::string logString;
        GLint length;
        char *log;
        
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        log = new char[static_cast<GLuint64>(length)];
        glGetShaderInfoLog(shaderId, length, nullptr, log);
        
        logString = log;
        delete[] log;
        
        return logString;
    }
    
    
    Shader::Shader(const std::string &vsPath, const std::string &fsPath) :
            programId(glCreateProgram()), vsId(glCreateShader(GL_VERTEX_SHADER)),
            fsId(glCreateShader(GL_FRAGMENT_SHADER)) {
        const std::string vsSource = addVersion(misc::FileReader::read(vsPath));
        const std::string fsSource = addVersion(misc::FileReader::read(fsPath));
        const char *cVsSource = vsSource.c_str();
        const char *cFsSource = fsSource.c_str();
        GLint status;
        
        glShaderSource(this->vsId, 1, &cVsSource, nullptr);
        glShaderSource(this->fsId, 1, &cFsSource, nullptr);
        
        glCompileShader(this->vsId);
        glGetShaderiv(this->vsId, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            throw std::runtime_error(
                    "Failed to compile vertex shader (from file '" + vsPath + "'): " + getShaderInfoLog(this->vsId)
            );
        }
        glCompileShader(this->fsId);
        glGetShaderiv(this->fsId, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            throw std::runtime_error(
                    "Failed to compile fragment shader (from file '" + fsPath + "'): " + getShaderInfoLog(this->fsId)
            );
        }
        
        glAttachShader(this->programId, this->vsId);
        glAttachShader(this->programId, this->fsId);
        
        glLinkProgram(this->programId);
        glGetProgramiv(this->programId, GL_LINK_STATUS, &status);
        if (status != GL_TRUE) {
            throw std::runtime_error(
                    "Failed to link shaders'" + vsPath + "' and '" + fsPath + "': " + getProgramInfoLog(this->programId)
            );
        }
    }
    
    
    void Shader::addUniform(const std::string &name, UniformType type) {
        std::shared_ptr<IUniform> uniform;
        
        switch (type) {
            case UNIFORM_1_F:
                uniform = std::make_shared<Uniform1fv>(this->programId, name.c_str());
                break;
            case UNIFORM_2_F:
                uniform = std::make_shared<Uniform2fv>(this->programId, name.c_str());
                break;
            case UNIFORM_3_F:
                uniform = std::make_shared<Uniform3fv>(this->programId, name.c_str());
                break;
            case UNIFORM_4_F:
                uniform = std::make_shared<Uniform4fv>(this->programId, name.c_str());
                break;
            case UNIFORM_1_I:
                uniform = std::make_shared<Uniform1iv>(this->programId, name.c_str());
                break;
            case UNIFORM_2_I:
                uniform = std::make_shared<Uniform2iv>(this->programId, name.c_str());
                break;
            case UNIFORM_3_I:
                uniform = std::make_shared<Uniform3iv>(this->programId, name.c_str());
                break;
            case UNIFORM_4_I:
                uniform = std::make_shared<Uniform4iv>(this->programId, name.c_str());
                break;
            case UNIFORM_1_UI:
                uniform = std::make_shared<Uniform1uiv>(this->programId, name.c_str());
                break;
            case UNIFORM_2_UI:
                uniform = std::make_shared<Uniform2uiv>(this->programId, name.c_str());
                break;
            case UNIFORM_3_UI:
                uniform = std::make_shared<Uniform3uiv>(this->programId, name.c_str());
                break;
            case UNIFORM_4_UI:
                uniform = std::make_shared<Uniform4uiv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_2F:
                uniform = std::make_shared<UniformMatrix2fv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_3F:
                uniform = std::make_shared<UniformMatrix3fv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_4F:
                uniform = std::make_shared<UniformMatrix4fv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_2X3F:
                uniform = std::make_shared<UniformMatrix2x3fv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_3X2F:
                uniform = std::make_shared<UniformMatrix3x2fv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_2X4F:
                uniform = std::make_shared<UniformMatrix2x4fv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_4X2F:
                uniform = std::make_shared<UniformMatrix4x2fv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_3X4F:
                uniform = std::make_shared<UniformMatrix3x4fv>(this->programId, name.c_str());
                break;
            case UNIFORM_MATRIX_4X3F:
                uniform = std::make_shared<UniformMatrix4x3fv>(this->programId, name.c_str());
                break;
            case UNIFORM_SAMPLER2D:
                uniform = std::make_shared<UniformSampler2D>(this->programId, name.c_str());
                break;
        }
        
        this->uniforms.emplace(name, uniform);
    }
    
    
    void Shader::loadUniform(const std::string &name, const void *value) const {
        try {
            this->uniforms.at(name)->load(value);
        } catch (const std::out_of_range &) {
            std::string error = "Error: Trying to specify the value of a non-existent uniform variable '" + name
                                + "' of program '" + std::to_string(this->programId) + "'.";
            throw std::runtime_error(error);
        }
    }
    
    
    void Shader::use() const {
        glUseProgram(this->programId);
    }
    
    
    void Shader::stop() const {
        glUseProgram(0);
    }
    
    
    Shader::~Shader() {
        glDeleteShader(vsId);
        glDeleteShader(fsId);
        glDeleteProgram(programId);
    }
}

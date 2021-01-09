#ifndef OPENGL_CUBEMAP_HPP
#define OPENGL_CUBEMAP_HPP

#include <memory>

#include <GL/glew.h>

#include <misc/INonCopyable.hpp>
#include <misc/Image.hpp>


namespace shader {
    
    class Cubemap : public misc::INonCopyable {
        private:
            GLuint textureId = 0;
        
        public:
            
            Cubemap() = default;
            
            explicit Cubemap(std::unique_ptr<misc::Image> texture[6]);
            
            [[nodiscard]] GLuint getCubemapId() const;
    };
}

#endif // OPENGL_CUBEMAP_HPP

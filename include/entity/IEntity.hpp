#ifndef OPENGL_IENTITY_HPP
#define OPENGL_IENTITY_HPP

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <misc/INonCopyable.hpp>


namespace entity {
    
    class IEntity : public misc::INonCopyable {
        
        protected:
            glm::vec3 position;
        
        public:
            
            IEntity(const glm::vec3 &pos);
            
            virtual ~IEntity() = default;
            
            virtual GLuint update() = 0;
            
            virtual GLuint render() = 0;
            
            [[nodiscard]] glm::vec3 getPosition();
    };
}
#endif //OPENGL_IENTITY_HPP

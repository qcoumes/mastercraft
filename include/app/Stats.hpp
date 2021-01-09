#ifndef OPENGL_STATS_HPP
#define OPENGL_STATS_HPP

#include <GL/glew.h>

#include <misc/ISingleton.hpp>


namespace app {
    
    class Stats : public misc::ISingleton {
        
        public:
            GLuint fps;
        
        private:
            
            Stats() = default;
        
        public:
            
            static Stats *getInstance();
    };
}

#endif // OPENGL_STATS_HPP

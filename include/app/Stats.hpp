#ifndef OPENGL_STATS_HPP
#define OPENGL_STATS_HPP

#include <GL/glew.h>

#include <misc/ISingleton.hpp>


namespace app {
    
    class Stats : public misc::ISingleton {
        
        public:
            GLuint fps;                     /**< Current FPS/ */
            GLuint l_superchunk = 0;        /**< Number of SuperChunk loaded. */
            GLuint l_chunk = 0;             /**< Number of Chunk loaded. */
            GLuint l_cube = 0;              /**< Number of cube loaded. */
            GLuint l_face = 0;              /**< Number of face loaded. */
            GLuint r_superchunk = 0;        /**< Number of SuperChunk rendered. */
            GLuint r_chunk = 0;             /**< Number of Chunk rendered. */
            GLuint r_cube = 0;              /**< Number of cube rendered. */
            GLuint r_face = 0;              /**< Number of face rendered. */
            GLuint64 occludedFace = 0;      /**< Number of face occluded. */
            GLuint64 frustumCulledFace = 0; /**< Number of face culled. */
            
        private:
            
            Stats() = default;
        
        public:
            
            static Stats *getInstance();
    };
}

#endif // OPENGL_STATS_HPP

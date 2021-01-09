#ifndef OPENGL_ISINGLETON_HPP
#define OPENGL_ISINGLETON_HPP

#include "INonCopyable.hpp"


namespace misc {
    
    /**
     * Common interface for Singletons.
     */
    class ISingleton : public INonCopyable {
        
        protected:
            
            ISingleton() = default;
        
        public:
            
            /**
             * Delete move constructor.
             */
            ISingleton(ISingleton &&) = delete;
    };
}

#endif // OPENGL_ISINGLETON_HPP

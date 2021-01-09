#ifndef OPENGL_INONCOPYABLE_HPP
#define OPENGL_INONCOPYABLE_HPP

namespace misc {
    
    /**
     * Common interface for non copyable classes.
     */
    class INonCopyable {
        public:
            
            /**
             * Delete copy constructor.
             */
            INonCopyable(const INonCopyable &) = delete;
            
            /**
             * Delete assignment operator.
             */
            INonCopyable &operator=(const INonCopyable &) = delete;
        
        protected:
            
            INonCopyable() = default;
            
            ~INonCopyable() = default;
    };
}

#endif // OPENGL_INONCOPYABLE_HPP

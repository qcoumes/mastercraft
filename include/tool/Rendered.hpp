#ifndef OPENGL_RENDERED_HPP
#define OPENGL_RENDERED_HPP

namespace tool {
    
    class Rendered {
        
        public:
            
            virtual ~Rendered() = default;
            
            virtual void update() = 0;
            
            virtual void render() const = 0;
    };
}

#endif // OPENGL_RENDERED_HPP

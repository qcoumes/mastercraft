#ifndef OPENGL_WINDOW_HPP
#define OPENGL_WINDOW_HPP

#include <SDL_video.h>
#include <SDL_events.h>

#include <tool/Camera.hpp>
#include <misc/ISingleton.hpp>


namespace tool {
    
    class Window : public misc::INonCopyable {
        private:
            SDL_Window *window;
            SDL_GLContext context;
        
        public:
            
            explicit Window(const char *title, uint32_t flags = 0);
            
            explicit Window(const char *title, int32_t width, int32_t height, uint32_t flags = 0);
            
            ~Window();
            
            void refresh();
            
            [[nodiscard]] SDL_Window *getWindow() const;
            
            [[nodiscard]] SDL_GLContext getContext() const;
            
            [[nodiscard]] SDL_DisplayMode getDisplayMode() const;
    };
}

#endif // OPENGL_WINDOW_HPP

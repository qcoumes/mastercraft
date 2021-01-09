#ifndef OPENGL_IMGUIHANDLER_HPP
#define OPENGL_IMGUIHANDLER_HPP

#include <SDL_video.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>


namespace tool {
    
    class ImGuiHandler {
        
        private:
            ImGuiIO io;
            SDL_Window *window;
        
        public:
            
            ImGuiHandler(SDL_Window *window, SDL_GLContext context);
            
            ~ImGuiHandler();
            
            void newFrame();
            
            void handleEvent(const SDL_Event &event);
            
            void render();
            
            [[nodiscard]] bool wantCaptureMouse();
            
            [[nodiscard]] bool wantCaptureKeyboard();
            
            static void HelpMarker(const char *desc);
    };
}

#endif // OPENGL_IMGUIHANDLER_HPP

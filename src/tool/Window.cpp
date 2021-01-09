#include <iostream>

#include <SDL.h>

#include <tool/Window.hpp>


namespace tool {
    
    Window::Window(const char *title, uint32_t flags) {
        if (0 != SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->window = SDL_CreateWindow(
                title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
                SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | flags
        );
        if (this->window == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->context = SDL_GL_CreateContext(this->window);
        if (this->context == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
        
        SDL_GL_MakeCurrent(this->window, this->context);
    }
    
    
    Window::Window(const char *title, int32_t width, int32_t height, uint32_t flags) {
        if (0 != SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->window = SDL_CreateWindow(
                title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                SDL_WINDOW_OPENGL | flags
        );
        if (this->window == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->context = SDL_GL_CreateContext(this->window);
        if (this->context == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
        
        SDL_GL_MakeCurrent(this->window, this->context);
    }
    
    
    Window::~Window() {
        SDL_GL_DeleteContext(this->context);
        SDL_DestroyWindow(this->window);
    }
    
    
    void Window::refresh() {
        SDL_GL_SwapWindow(this->window);
    }
    
    
    SDL_Window *Window::getWindow() const {
        return this->window;
    }
    
    
    SDL_GLContext Window::getContext() const {
        return this->context;
    }
    
    
    SDL_DisplayMode Window::getDisplayMode() const {
        SDL_DisplayMode mode;
        
        if (SDL_GetDesktopDisplayMode(0, &mode)) {
            throw std::runtime_error(SDL_GetError());
        }
        
        return mode;
    }
}

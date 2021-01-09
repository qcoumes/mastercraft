#ifndef OPENGL_ENGINE_HPP
#define OPENGL_ENGINE_HPP

#include <cstdint>
#include <chrono>
#include <string>
#include <memory>

#include <GL/glew.h>

#include <tool/Window.hpp>
#include <tool/Camera.hpp>
#include <tool/Input.hpp>
#include <tool/ImGuiHandler.hpp>
#include <tool/Rendered.hpp>


namespace app {
    
    class Engine : public misc::ISingleton {
        private:
            std::chrono::steady_clock::time_point lastTick;
            GLboolean running = true;
            GLuint tickSecond = 0;
            GLuint tickCount = 0;
        
        public:
            std::unordered_map<std::string, std::shared_ptr<tool::Rendered>> rendered;
            std::unique_ptr<tool::ImGuiHandler> imGui = nullptr;
            std::unique_ptr<tool::Window> window = nullptr;
            std::unique_ptr<tool::Camera> camera = nullptr;
            std::unique_ptr<tool::Input> input = nullptr;
        
        private:
            
            void debug() const;
            
            void _render() const;
            
            Engine() = default;
        
        public:
            
            static Engine *getInstance();
            
            void init();
            
            GLboolean tick();
            
            void update();
            
            void render() const;
            
            void cleanup();
            
            [[nodiscard]] GLboolean isRunning();
    };
}

#endif // OPENGL_ENGINE_HPP

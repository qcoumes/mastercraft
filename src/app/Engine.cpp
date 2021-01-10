#include <chrono>
#include <iostream>
#include <iomanip>
#include <memory>

#include <imgui/imgui.h>

#include <tool/ImGuiHandler.hpp>
#include <app/Engine.hpp>
#include <app/Config.hpp>
#include <app/Stats.hpp>
#include <algorithm>


namespace app {
    
    Engine *Engine::getInstance() {
        static Engine engine;
        return &engine;
    }
    
    
    void Engine::init() {
        this->window = std::make_unique<tool::Window>("OpenGL");
        
        GLenum glewInitError = glewInit();
        if (GLEW_OK != glewInitError) {
            throw std::runtime_error(
                reinterpret_cast<const char *>(glewGetErrorString(glewInitError)));
        }
        
        this->lastTick = std::chrono::steady_clock::now();
        this->camera = std::make_unique<tool::Camera>();
        this->camera->moveForward(-5);
        this->camera->moveUp(Config::GEN_MAX_H + 1);
        this->input = std::make_unique<tool::Input>();
        this->imGui = std::make_unique<tool::ImGuiHandler>(this->window->getWindow(),
                                                           this->window->getContext());
        Config::getInstance()->init(*this->window, *this->camera);
        
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        
        this->world = std::make_unique<app::World>();
    }
    
    
    GLboolean Engine::tick() {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        GLint64 duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - this->lastTick
        ).count();
        
        if (duration >= Config::MS_PER_TICK) {
            this->lastTick = now;
            this->tickCount++;
            this->tickSecond = (this->tickSecond + 1) % Config::TICK_PER_SEC;
            this->world->tickCycle = (this->world->tickCycle + 1) % Config::TICK_PER_DAY_CYCLE;
            return true;
        }
        
        return false;
    }
    
    
    void Engine::update() {
        Config *config = Config::getInstance();
        GLfloat speed = config->getSpeed();
        SDL_Event event;
        this->input->reset();
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEWHEEL:
                    if (this->imGui->wantCaptureMouse()) {
                        this->imGui->handleEvent(event);
                    }
                    else {
                        this->input->handleInput(event);
                    }
                    break;
                
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    if (this->imGui->wantCaptureKeyboard()) {
                        this->imGui->handleEvent(event);
                    }
                    else {
                        this->input->handleInput(event);
                    }
                    break;
                
                default:
                    this->input->handleInput(event);
            }
        }
        
        // Close app
        if (this->input->ended() || this->input->isReleasedKey(SDL_SCANCODE_ESCAPE)) {
            this->running = false;
        }
        
        // Movements
        if (this->input->isHeldKey(SDL_SCANCODE_A)) {
            this->camera->moveLeft(speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_D)) {
            this->camera->moveLeft(-speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_W)) {
            this->camera->moveForward(speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_S)) {
            this->camera->moveForward(-speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_SPACE)) {
            this->camera->moveUp(speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_LCTRL)) {
            this->camera->moveUp(-speed);
        }
        
        // Camera rotation
        if (!config->getFreeMouse()) {
            glm::vec2 motion = this->input->getRelativeMotion();
            GLfloat sensitivity = config->getMouseSensitivity();
            this->camera->rotateLeft(-motion.x * sensitivity);
            this->camera->rotateUp(-motion.y * sensitivity);
        }
        
        // Toggle free mouse
        if (this->input->isReleasedKey(SDL_SCANCODE_LALT)) {
            config->switchFreeMouse();
        }
        
        // Toggle day / night
        if (this->input->isReleasedKey(SDL_SCANCODE_E)) {
            if (this->world->tickCycle < Config::TICK_PER_DAY_CYCLE / 2) {
                this->world->tickCycle = Config::DUSK_END;
            }
            else {
                this->world->tickCycle = Config::DAWN_END;
            }
        }
        
        // Toggle debug
        if (this->input->isReleasedKey(SDL_SCANCODE_F1)) {
            config->switchDebug();
        }
        
        this->world->update();
    }
    
    
    void Engine::debug() const {
        Config *config = Config::getInstance();
        Engine *engine = Engine::getInstance();
        
        
        glm::dvec3 position = engine->camera->getPosition();
        glm::dvec3 lookingAt = engine->camera->getFrontVector();
        
        glm::mat4 MVMatrix = engine->camera->getViewMatrix();
        glm::vec3 lightPos = glm::vec3(MVMatrix * glm::vec4(engine->world->sun->getPosition(), 0));
        glm::vec3 lightColor = Config::getLightColor(engine->world->tickCycle);
        GLfloat lightDirIntensity = Config::getLightDirIntensity(engine->world->tickCycle);
        GLfloat lightAmbIntensity = Config::getLightAmbIntensity(engine->world->tickCycle);
        
        std::stringstream ss;
        GLint length;
        
        this->imGui->newFrame();
        ImGui::SetNextWindowSize({ 600, 600 }, ImGuiCond_Once);
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %d /", Stats::getInstance()->fps);
        ImGui::SameLine();
        ImGui::PushItemWidth(105);
        if (ImGui::BeginCombo("", config->getFramerateString().c_str())) {
            for (GLint i = 0; i <= Framerate::FRAMERATE_LAST; i++) {
                bool is_selected = (config->getFramerateOpt() == i);
                if (ImGui::Selectable(config->getFramerateString(i).c_str(), is_selected)) {
                    config->setFramerate(static_cast<Framerate>(i));
                }
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::SameLine();
        tool::ImGuiHandler::HelpMarker("VSYNC can be overridden by your driver / OpenGL settings.");
        length = static_cast<GLint>(std::to_string(Config::TICK_PER_SEC).size());
        ss.str(std::string());
        ss << "Tick: " << std::setfill('0') << std::setw(length) << engine->tickSecond << "/"
           << Config::TICK_PER_SEC;
        ImGui::Text("%s", ss.str().c_str());
        length = static_cast<GLint>(std::to_string(Config::TICK_PER_DAY_CYCLE).size());
        ss.str(std::string());
        ss << "Day cycle: " << std::setfill('0') << std::setw(length) << engine->world->tickCycle
           << "/" << Config::TICK_PER_DAY_CYCLE << " (Cycle of " << Config::SECONDS_DAY_CYCLE
           << " seconds)";
        ImGui::Text("%s", ss.str().c_str());
        ImGui::Text("Position: (%.2f, %.2f, %.2f)", position.x, position.y, position.z);
        ImGui::Text("Looking at: (%.2f, %.2f, %.2f)", lookingAt.x, lookingAt.y, lookingAt.z);
        ImGui::Dummy({ 0.0f, 6.0f });
        
        if (ImGui::CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::BulletText("Movement :");
            ImGui::Indent();
            ImGui::BulletText("W : Move forward.");
            ImGui::BulletText("S : Move backward.");
            ImGui::BulletText("A : Strafe left.");
            ImGui::BulletText("D : Strafe right.");
            ImGui::BulletText("CTRL : Move downward.");
            ImGui::BulletText("SPACE : Move upward.");
            ImGui::Unindent();
            ImGui::BulletText("E To switch between day and night.");
            ImGui::BulletText("F1 : Displays / closes the debug menu.");
            ImGui::BulletText("LEFT ALT: Free / lock the mouse cursor.");
            ImGui::Dummy({ 0.0f, 3.0f });
            ImGui::Text("Freeing the cursor allow you to interact with this menu.");
        }
        
        if (ImGui::CollapsingHeader("Lightning", ImGuiTreeNodeFlags_DefaultOpen)) {
            ss.str(std::string());
            ss << "Light position: (" << lightPos.x << ", " << lightPos.y << ", " << lightPos.z
               << ")";
            ImGui::Text("%s", ss.str().c_str());
            
            ss.str(std::string());
            ss << "Light color: ";
            ImGui::Text("%s", ss.str().c_str());
            ImGui::SameLine(215);
            ImGui::ColorEdit3("", reinterpret_cast<float *>(&lightColor));
            
            ss.str(std::string());
            ss << "Directional light intensity: ";
            ImGui::Text("%s", ss.str().c_str());
            ImGui::SameLine(215);
            ImGui::SliderFloat("", &lightDirIntensity, 0, 1.f);
            
            ss.str(std::string());
            ss << "Ambient light intensity: ";
            ImGui::Text("%s", ss.str().c_str());
            ImGui::SameLine(215);
            ImGui::SliderFloat("", &lightAmbIntensity, 0, 1.f);
        }
        
        if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen)) {
            ss.str(std::string());
            ss << "Superchunk : " << config->l_superchunk;
            ImGui::Text("%s", ss.str().c_str());
            
            ss.str(std::string());
            ss << "Chunk : " << config->l_chunk;
            ImGui::Text("%s", ss.str().c_str());
            
            ss.str(std::string());
            ss << "Cube : " << config->l_cube;
            ImGui::Text("%s", ss.str().c_str());
            
            ss.str(std::string());
            ss << "Face : " << config->l_face << " - " << config->r_face << " ("
               << static_cast<GLfloat>(config->r_face) / static_cast<GLfloat>(config->l_face) * 100
               << "%) rendered";
            ImGui::Text("%s", ss.str().c_str());
        }
        
        if (ImGui::CollapsingHeader("Hardware & Drivers")) {
            GLfloat offset = 120;
            ImGui::Text("CPU:");
            ImGui::SameLine(offset);
            ImGui::Text("%s", config->getCpuInfo().c_str());
            ImGui::Separator();
            
            ImGui::Text("GPU:");
            ImGui::SameLine(offset);
            ImGui::Text("%s", config->getGPUInfo().c_str());
            ImGui::Text("Driver:");
            ImGui::SameLine(offset);
            ImGui::Text("%s", config->getGPUDriver().c_str());
            if (ImGui::TreeNode("Extensions")) {
                for (const std::string &s : config->getGPUExtensions()) {
                    ImGui::BulletText("%s", s.c_str());
                }
                ImGui::TreePop();
            }
            ImGui::Separator();
            
            ImGui::Text("GLEW Version:");
            ImGui::SameLine(offset);
            ImGui::Text("%s", config->getGlewVersion().c_str());
        }
        
        if (ImGui::CollapsingHeader("Settings")) {
            bool faceCulling = config->getFaceCulling();
            ImGui::Checkbox("Face Culling", &faceCulling);
            if (faceCulling != config->getFaceCulling()) {
                config->switchFaceCulling();
            }
        }
        
        ImGui::End();
        this->imGui->render();
    }
    
    
    void Engine::_render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        this->world->render();
        
        if (Config::getInstance()->getDebug()) {
            this->debug();
        }
        
        this->window->refresh();
    }
    
    
    void Engine::render() const {
        static std::chrono::steady_clock::time_point cmptStart = std::chrono::steady_clock::now();
        static std::chrono::steady_clock::time_point limiterStart = cmptStart;
        static GLuint fps = 0;
        
        std::chrono::steady_clock::time_point now;
        GLint64 duration;
        
        if (Config::getInstance()->getFramerate() > 0) { // Capped framerate
            now = std::chrono::steady_clock::now();
            duration =
                std::chrono::duration_cast<std::chrono::microseconds>(now - limiterStart).count();
            
            if (duration >= Config::getInstance()->getFramerateInv()) {
                this->_render();
                limiterStart = now;
                fps++;
            }
        }
        else { // Uncapped framerate
            this->_render();
            fps++;
        }
        
        // Computing FPS
        now = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::seconds>(now - cmptStart).count();
        if (duration >= 1) {
            Stats::getInstance()->fps = static_cast<GLuint>(fps);
            fps = 0;
            cmptStart = now;
        }
    }
    
    
    void Engine::cleanup() {
    }
    
    
    GLboolean Engine::isRunning() {
        return this->running;
    }
}

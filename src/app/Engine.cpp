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
        Config *config = Config::getInstance();
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        GLint64 duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - this->lastTick
        ).count();
        
        if (duration >= Config::MS_PER_TICK) {
            this->lastTick = now;
            this->tickCount++;
            this->tickSecond = (this->tickSecond + 1) % Config::TICK_PER_SEC;
            this->world->tickCycle = static_cast<GLfloat>(
                static_cast<GLint>((this->world->tickCycle + 1))
                % static_cast<GLint>(config->getTickPerDay())
            );
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
            if (this->world->tickCycle < config->getTickPerDay() / 2) {
                this->world->tickCycle = config->getTickDuskEnd();
            }
            else {
                this->world->tickCycle = config->getTickDawnEnd();
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
        Stats *stats = Stats::getInstance();
        
        glm::vec3 position = this->camera->getPosition();
        glm::vec3 superchunk = cube::ChunkManager::getSuperChunkCoordinates(position);
        glm::vec3 lookingAt = this->camera->getFrontVector();
        
        glm::mat4 MVMatrix = this->camera->getViewMatrix();
        glm::vec3 lightPos = glm::vec3(MVMatrix * glm::vec4(this->world->sun->getPosition(), 0));
        glm::vec3 lightColor = config->getLightColor(this->world->tickCycle);
        
        glm::vec3 dawnDuskSkyboxColor = config->getDawnDuskSkyboxCol();
        glm::vec3 daySkyboxColor = config->getDaySkyboxCol();
        glm::vec3 nightSkyboxColor = config->getNightSkyboxCol();
        
        glm::vec3 dawnDuskLightColor = config->getDawnDuskLightCol();
        glm::vec3 dayLightColor = config->getDayLightCol();
        glm::vec3 nightLightColor = config->getNightLightCol();
        
        GLfloat dawnDuskLighDirIntensity = config->getDawnDuskLightDirIntensity();
        GLfloat nightLighDirIntensity = config->getNightLightDirIntensity();
        GLfloat dayLighDirIntensity = config->getDayLightDirIntensity();
        
        GLfloat dawnDuskLighAmbIntensity = config->getDawnDuskLightAmbIntensity();
        GLfloat nightLighAmbIntensity = config->getNightLightAmbIntensity();
        GLfloat dayLighAmbIntensity = config->getDayLightAmbIntensity();
    
        
        GLuint dawnStart = static_cast<GLuint>(config->getTickDawnStart());
        GLuint dawn = static_cast<GLuint>(config->getTickDawn());
        GLuint dawnEnd = static_cast<GLuint>(config->getTickDawnEnd());
        GLuint duskStart = static_cast<GLuint>(config->getTickDuskStart());
        GLuint dusk = static_cast<GLuint>(config->getTickDusk());
        GLuint duskEnd = static_cast<GLuint>(config->getTickDuskEnd());
        glm::ivec3 dawnArray = {dawnStart, dawn, dawnEnd};
        glm::ivec3 duskArray = {duskStart, dusk, duskEnd};
        
        GLfloat lightDirIntensity = config->getLightDirIntensity(this->world->tickCycle);
        GLfloat lightAmbIntensity = config->getLightAmbIntensity(this->world->tickCycle);
        
        float speed = config->getSpeed();
        bool faceCulling = config->getFaceCulling();
        bool occlusionCulling = config->getOcclusionCulling();
        
        std::stringstream ss;
        
        this->imGui->newFrame();
        
        // FPS
        ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_Always);
        ImGui::SetNextWindowSize({ 600, 600 }, ImGuiCond_Once);
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %d / %s", stats->fps, config->getFramerateString().c_str());
        ImGui::SameLine();
        tool::ImGuiHandler::HelpMarker(
            "Your driver / OpenGL settings may lock you on VSYNC.\n"
            "VSYNC's value can differs from the one display, based on your driver / OpenGL settings."
        );
    
        ImGui::PushItemWidth(200);
        
        // Tick
        GLint tickSecond = static_cast<GLint>(this->tickSecond);
        GLint tickCycle = static_cast<GLint>(this->world->tickCycle);
        ImGui::Text("Tick:");
        ImGui::SameLine(90);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.6f);
        ImGui::SliderInt("##sliderTick", &tickSecond, 0, Config::TICK_PER_SEC);
        ImGui::PopStyleVar();
        ImGui::SameLine(300);
        ImGui::Text("Day:");
        ImGui::SameLine(380);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.6f);
        ImGui::SliderInt("##sliderCycle", &tickCycle, 0, static_cast<int>(config->getTickPerDay()));
        ImGui::PopStyleVar();
        
        // Dawn / Dusk
        ImGui::PushItemWidth(200);
        ImGui::Text("Dawn Tresh.:");
        ImGui::SameLine(90);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.6f);
        ImGui::InputInt3("", reinterpret_cast<int *>(&dawnArray));
        ImGui::PopStyleVar();
        ImGui::SameLine(300);
        ImGui::Text("Dusk Tresh.:");
        ImGui::SameLine(380);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.6f);
        ImGui::InputInt3("", reinterpret_cast<int *>(&duskArray));
        ImGui::PopStyleVar();
        
        // Position
        ImGui::PushItemWidth(200);
        ImGui::Text("Position:");
        ImGui::SameLine(90);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::InputFloat3("", reinterpret_cast<float *>(&position));
        ImGui::PopStyleVar();
        ImGui::SameLine(300);
        ImGui::Text("SuperChunk:");
        ImGui::SameLine(380 );
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::InputFloat3("", reinterpret_cast<float *>(&superchunk));
        ImGui::PopStyleVar();
        
        ImGui::Text("Looking at:");
        ImGui::SameLine(90);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.6f);
        ImGui::InputFloat3("", reinterpret_cast<float *>(&lookingAt));
        ImGui::PopStyleVar();
        
        // Lighting
        ImGui::Dummy({ 0.0f, 3.0f });
        ImGui::PushItemWidth(200);
        ImGui::Text("Light position:");
        ImGui::SameLine(175);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::InputFloat3("##dirLightPosDisplay", reinterpret_cast<float *>(&lightPos));
        ImGui::PopStyleVar();
        
        ImGui::Text("Light color:");
        ImGui::SameLine(175);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::ColorEdit3("##dirLightColDisplay", reinterpret_cast<float *>(&lightColor));
        ImGui::PopStyleVar();
        
        ImGui::Text("Directional intensity:");
        ImGui::SameLine(175);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::SliderFloat("##dirLightIntDisplay", &lightDirIntensity, 0, 1.f);
        ImGui::PopStyleVar();
        
        ImGui::Text("Ambient intensity:");
        ImGui::SameLine(175);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::SliderFloat("##ambLightDisplay", &lightAmbIntensity, 0, 1.f);
        ImGui::PopStyleVar();
        
        if (ImGui::CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Indent();
            
            ImGui::BulletText("Movement :");
            ImGui::Indent();
            ImGui::BulletText("W : Move forward.");
            ImGui::BulletText("S : Move backward.");
            ImGui::BulletText("A : Strafe left.");
            ImGui::BulletText("D : Strafe right.");
            ImGui::BulletText("CTRL : Move downward.");
            ImGui::BulletText("SPACE : Move upward.");
            ImGui::Unindent();
            ImGui::BulletText("E: To switch between day and night.");
            ImGui::BulletText("F1 : Displays / closes the debug menu.");
            ImGui::BulletText("LEFT ALT: Free / lock the mouse cursor.");
            ImGui::Dummy({ 0.0f, 3.0f });
            ImGui::Text("Freeing the cursor allows you to interact with this menu.");
            
            ImGui::Unindent();
        }
        
        // Settings
        if (ImGui::CollapsingHeader("Settings")) {
            ImGui::Indent();
            
            // FPS
            ImGui::Text("Max FPS:");
            ImGui::SameLine(160);
            ImGui::PushItemWidth(100);
            if (ImGui::BeginCombo("##fpsSetting", config->getFramerateString().c_str())) {
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
            
            // Distance view
            ImGui::Text("Distance view:");
            ImGui::SameLine(160);
            if (ImGui::BeginCombo("##distanceViewSetting",
                                  std::to_string(config->getDistanceView()).c_str())) {
                for (GLint i = 0; i <= 10; i++) {
                    bool is_selected = (config->getDistanceView() == i);
                    if (ImGui::Selectable(std::to_string(i).c_str(), is_selected)) {
                        config->setDistanceView(i);
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
            
            // Speed
            ImGui::Text("Speed:");
            ImGui::SameLine(160);
            ImGui::SliderFloat("##speedSetting", &speed, 0.1f, 3.f);
            config->setSpeed(speed);
            
            
            // Culling
            ImGui::Text("Face Culling:");
            ImGui::SameLine(160);
            ImGui::Checkbox("##faceCullingSetting", &faceCulling);
            config->setFaceCulling(faceCulling);
            
            ImGui::Text("Occlusion Culling:");
            ImGui::SameLine(160);
            ImGui::Checkbox("##occlusionCullingSetting", &occlusionCulling);
            config->setOcclusionCulling(occlusionCulling);
            ImGui::SameLine();
            tool::ImGuiHandler::HelpMarker(
                "Disabling this setting with a medium to high distance view (3+)\n"
                "May freeze the game. This settings only affect newly-loaded chunks."
            );
            
            if (ImGui::CollapsingHeader("Skybox")) {
                ImGui::Indent();
                
                // Skybox Color
                ImGui::Dummy({ 0.0f, 3.0f });
                ImGui::Text("Skybox color");
                ImGui::SameLine();
                ss.str(std::string());
                ss << "Dawn start at tick " << dawnStart << " and finish at tick "
                   << dawnEnd << ".\nDuring this transition, color "
                   << "will interpolate between Night and Dawn/Dusk until tick "
                   << dawn << " before interpolating between Dawn/Dusk and Day.\n\n"
                   << "Dusk start at tick " << duskStart << " and finish at tick "
                   << duskEnd << ".\nDuring this transition, color "
                   << "will interpolate between Day and Dawn/Dusk until tick "
                   << dusk << " before interpolating between Dawn/Dusk and Night.";
                tool::ImGuiHandler::HelpMarker(ss.str().c_str());
                
                ImGui::BulletText("Dawn/Dusk:");
                ImGui::SameLine(150);
                ImGui::ColorEdit3(
                    "##dawnDuskSkyboxColor", reinterpret_cast<float *>(&dawnDuskSkyboxColor)
                );
                config->setDawnDuskSkyboxCol(dawnDuskSkyboxColor);
                
                ImGui::BulletText("Night:");
                ImGui::SameLine(150);
                ImGui::ColorEdit3(
                    "##nightSkyboxColor", reinterpret_cast<float *>(&nightSkyboxColor)
                );
                config->setNightSkyboxCol(nightSkyboxColor);
                
                ImGui::BulletText("Day:");
                ImGui::SameLine(150);
                ImGui::ColorEdit3(
                    "##daySkyboxColor", reinterpret_cast<float *>(&daySkyboxColor)
                );
                config->setDaySkyboxCol(daySkyboxColor);
                
                ImGui::Unindent();
            }
            
            if (ImGui::CollapsingHeader("Lighting")) {
                ImGui::Indent();
                // Light Color
                ImGui::Dummy({ 0.0f, 3.0f });
                ImGui::Text("Light");
                ImGui::SameLine();
                ss.str(std::string());
                ss << "Dawn start at tick " << dawnStart << " and finish at tick "
                   << dawnEnd << ".\nDuring this transition, color and intensities "
                   << "will interpolate between Night and Dawn/Dusk until tick "
                   << dawn << " before interpolating between Dawn/Dusk and Day.\n\n"
                   << "Dusk start at tick " << duskStart << " and finish at tick "
                   << duskEnd << ".\nDuring this transition, color and intensities "
                   << "will interpolate between Day and Dawn/Dusk until tick "
                   << dusk << " before interpolating between Dawn/Dusk and Night.";
                tool::ImGuiHandler::HelpMarker(ss.str().c_str());
                
                ImGui::BulletText("Dawn/Dusk:");
                ImGui::Indent();
                ImGui::BulletText("Directional Intensity:");
                ImGui::SameLine(255);
                ImGui::SliderFloat("##dawnDuskIntensity", &dawnDuskLighDirIntensity, 0.f, 1.f);
                config->setDawnDuskLightDirIntensity(dawnDuskLighDirIntensity);
                ImGui::BulletText("Ambient Intensity:");
                ImGui::SameLine(255);
                ImGui::SliderFloat("##dawnDuskAmbIntensity", &dawnDuskLighAmbIntensity, 0.f, 1.f);
                config->setDawnDuskLightAmbIntensity(dawnDuskLighAmbIntensity);
                ImGui::BulletText("Color:");
                ImGui::SameLine(255);
                ImGui::ColorEdit3(
                    "##dawnDuskLightColor", reinterpret_cast<float *>(&dawnDuskLightColor)
                );
                config->setDawnDuskLightCol(dawnDuskLightColor);
                ImGui::Unindent();
                
                ImGui::BulletText("Night:");
                ImGui::Indent();
                ImGui::BulletText("Directional Intensity:");
                ImGui::SameLine(255);
                ImGui::SliderFloat("##nightLighDirIntensity", &nightLighDirIntensity, 0.f, 1.f);
                config->setNightLightDirIntensity(nightLighDirIntensity);
                ImGui::BulletText("Ambient Intensity:");
                ImGui::SameLine(255);
                ImGui::SliderFloat("##nightLighAmbIntensity", &nightLighAmbIntensity, 0.f, 1.f);
                config->setNightLightAmbIntensity(nightLighAmbIntensity);
                ImGui::BulletText("Color:");
                ImGui::SameLine(255);
                ImGui::ColorEdit3(
                    "##nightLightColor", reinterpret_cast<float *>(&nightLightColor)
                );
                config->setNightLightCol(nightLightColor);
                ImGui::Unindent();
                
                ImGui::BulletText("Day:");
                ImGui::Indent();
                ImGui::BulletText("Directional Intensity:");
                ImGui::SameLine(255);
                ImGui::SliderFloat("##dayLighDirIntensity", &dayLighDirIntensity, 0.f, 1.f);
                config->setDayLightDirIntensity(dayLighDirIntensity);
                ImGui::BulletText("Ambient Intensity:");
                ImGui::SameLine(255);
                ImGui::SliderFloat("##dayLighAmbIntensity", &dayLighAmbIntensity, 0.f, 1.f);
                config->setDayLightAmbIntensity(dayLighAmbIntensity);
                ImGui::BulletText("Color:");
                ImGui::SameLine(255);
                ImGui::ColorEdit3(
                    "##dayLightColor", reinterpret_cast<float *>(&dayLightColor)
                );
                config->setDayLightCol(dayLightColor);
                ImGui::Unindent();
                
                ImGui::Unindent();
            }
            
            ImGui::Unindent();
        }
        
        if (ImGui::CollapsingHeader("Stats")) {
            ImGui::Indent();
            ss.str(std::string());
            ss << "Superchunk : " << stats->l_superchunk;
            ImGui::Text("%s", ss.str().c_str());
            
            ss.str(std::string());
            ss << "Chunk : " << stats->l_chunk;
            ImGui::Text("%s", ss.str().c_str());
            
            ss.str(std::string());
            ss << "Cube : " << stats->l_cube;
            ImGui::Text("%s", ss.str().c_str());
            
            ss.str(std::string());
            ss << "Face : " << stats->l_face << " - " << stats->r_face << " ("
               << static_cast<GLfloat>(stats->r_face) / static_cast<GLfloat>(stats->l_face) * 100
               << "%) rendered";
            ImGui::Text("%s", ss.str().c_str());
            ImGui::Unindent();
        }
        
        if (ImGui::CollapsingHeader("Hardware & Drivers")) {
            ImGui::Indent();
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
    
    
    GLboolean Engine::isRunning() const {
        return this->running;
    }
}

#include <sstream>
#include <iostream>
#include <iterator>

#include <SDL_mouse.h>
#include <libcpuid.h>

#include <app/Config.hpp>


static GLfloat changeIntervalTo01(GLfloat x, GLfloat oldMin, GLfloat oldMax) {
    GLfloat oldRange = (oldMax - oldMin);
    GLfloat newRange = (1.f - 0.f);
    
    return std::min(1.f, std::max(0.f, (((x - oldMin) * newRange) / oldRange)));
}


namespace app {
    
    Config *Config::getInstance() {
        static Config config;
        return &config;
    }
    
    
    void Config::init(const tool::Window &window, tool::Camera &camera) {
        this->GPUInfo = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
        this->GPUDriver = reinterpret_cast<const char *>(glGetString(GL_VERSION));
        this->GLEWVersion = reinterpret_cast<const char *>(glewGetString(GLEW_VERSION));
        std::istringstream
            iss = std::istringstream(reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS)));
        this->GPUExtensions = std::vector<std::string>(
            std::istream_iterator<std::string> { iss },
            std::istream_iterator<std::string>()
        );
        this->setFramerate(Framerate::FRAMERATE_VSYNC);
        this->setFov(70, window, camera);
        this->setFaceCulling(true);
        
        SDL_DisplayMode display = window.getDisplayMode();
        this->width = display.w;
        this->height = display.h;
        GLuint fps = static_cast<GLuint>(window.getDisplayMode().refresh_rate);
        this->vSyncFramerate = fps ? fps : 60;
        this->setFramerate(FRAMERATE_VSYNC);
        
        struct cpu_raw_data_t raw {};
        struct cpu_id_t data {};
        if (cpuid_get_raw_data(&raw) < 0 || cpu_identify(&raw, &data) < 0) {
            this->CPUInfo = "Unknown";
        }
        else {
            std::stringstream ss;
            ss << data.brand_str << " - " << data.num_cores << " cores (" << data.num_logical_cpus
               << " threads)";
            this->CPUInfo = ss.str();
        }
    }
    
    
    [[maybe_unused]] std::string Config::getGPUDriver() const {
        return this->GPUDriver;
    }
    
    
    [[maybe_unused]] std::string Config::getGPUInfo() const {
        return this->GPUInfo;
    }
    
    
    [[maybe_unused]] std::vector<std::string> Config::getGPUExtensions() const {
        return this->GPUExtensions;
    }
    
    
    [[maybe_unused]] [[maybe_unused]]std::string Config::getGlewVersion() const {
        return this->GLEWVersion;
    }
    
    
    [[maybe_unused]] std::string Config::getCpuInfo() const {
        return this->CPUInfo;
    }
    
    
    [[maybe_unused]] GLfloat Config::getMouseSensitivity() const {
        return mouseSensitivity;
    }
    
    
    [[maybe_unused]] void Config::setMouseSensitivity(GLfloat mouseSensitivity) {
        this->mouseSensitivity = mouseSensitivity;
    }
    
    
    [[maybe_unused]] GLfloat Config::getSpeed() const {
        return this->speed;
    }
    
    
    [[maybe_unused]] void Config::setSpeed(GLfloat speed) {
        this->speed = speed;
    }
    
    
    [[maybe_unused]] void Config::setWidth(GLint width) {
        this->width = width;
    }
    
    
    [[maybe_unused]] void Config::setHeight(GLint height) {
        this->height = height;
    }
    
    
    [[maybe_unused]] GLint Config::getWidth() const {
        return this->width;
    }
    
    
    [[maybe_unused]] GLint Config::getHeight() const {
        return this->height;
    }
    
    
    [[maybe_unused]] GLuint Config::getFramerate() const {
        return framerate;
    }
    
    
    [[maybe_unused]] GLuint Config::getFramerateInv() const {
        return usPerFrame;
    }
    
    
    [[maybe_unused]] Framerate Config::getFramerateOpt() const {
        return this->framerateOpt;
    }
    
    
    [[maybe_unused]] std::string Config::getFramerateString(GLint fps) const {
        if (fps == -1) {
            fps = this->framerateOpt;
        }
        
        switch (fps) {
            case Framerate::FRAMERATE_60:
                return "60";
            case Framerate::FRAMERATE_75:
                return "75";
            case Framerate::FRAMERATE_120:
                return "120";
            case Framerate::FRAMERATE_144:
                return "144";
            case Framerate::FRAMERATE_180:
                return "180";
            case Framerate::FRAMERATE_240:
                return "240";
            case Framerate::FRAMERATE_VSYNC:
                return std::to_string(this->vSyncFramerate) + " (VSYNC)";
            case Framerate::FRAMERATE_UNCAPPED:
                return "Uncapped";
            default:
                return "Unknown";
        }
    }
    
    
    [[maybe_unused]] void Config::setFramerate(Framerate framerate) {
        this->framerateOpt = framerate;
        
        switch (framerate) {
            case Framerate::FRAMERATE_60:
                this->framerate = 60;
                this->usPerFrame = static_cast<GLuint>(1. / 60. * 1e6);
                break;
            case Framerate::FRAMERATE_75:
                this->framerate = 75;
                this->usPerFrame = static_cast<GLuint>(1. / 75. * 1e6);
                break;
            case Framerate::FRAMERATE_120:
                this->framerate = 120;
                this->usPerFrame = static_cast<GLuint>(1. / 120. * 1e6);
                break;
            case Framerate::FRAMERATE_144:
                this->framerate = 144;
                this->usPerFrame = static_cast<GLuint>(1. / 144. * 1e6);
                break;
            case Framerate::FRAMERATE_180:
                this->framerate = 180;
                this->usPerFrame = static_cast<GLuint>(1. / 180. * 1e6);
                break;
            case Framerate::FRAMERATE_240:
                this->framerate = 240;
                this->usPerFrame = static_cast<GLuint>(1. / 240. * 1e6);
                break;
            case Framerate::FRAMERATE_VSYNC:
                this->framerate = this->vSyncFramerate;
                this->usPerFrame = static_cast<GLuint>(1. / this->framerate * 1e6);
                break;
            case Framerate::FRAMERATE_UNCAPPED:
                this->framerate = 0;
                this->usPerFrame = 0;
                break;
        }
    }
    
    
    [[maybe_unused]] void Config::cycleFramerate() {
        switch (this->framerateOpt) {
            case Framerate::FRAMERATE_60:
                this->setFramerate(Framerate::FRAMERATE_75);
                break;
            case Framerate::FRAMERATE_75:
                this->setFramerate(Framerate::FRAMERATE_120);
                break;
            case Framerate::FRAMERATE_120:
                this->setFramerate(Framerate::FRAMERATE_144);
                break;
            case Framerate::FRAMERATE_144:
                this->setFramerate(Framerate::FRAMERATE_180);
                break;
            case Framerate::FRAMERATE_180:
                this->setFramerate(Framerate::FRAMERATE_240);
                break;
            case Framerate::FRAMERATE_240:
                this->setFramerate(Framerate::FRAMERATE_VSYNC);
                break;
            case Framerate::FRAMERATE_VSYNC:
                this->setFramerate(Framerate::FRAMERATE_UNCAPPED);
                break;
            case Framerate::FRAMERATE_UNCAPPED:
                this->setFramerate(Framerate::FRAMERATE_60);
                break;
        }
    }
    
    
    [[maybe_unused]] GLfloat Config::getFov() const {
        return fov;
    }
    
    
    [[maybe_unused]] void Config::setFov(GLfloat fov, const tool::Window &window,
                                         tool::Camera &camera) {
        this->fov = fov;
        SDL_DisplayMode display = window.getDisplayMode();
        camera.setProjMatrix(fov, display.w, display.h);
    }
    
    
    [[maybe_unused]] GLint Config::getDistanceView() const {
        return distanceView;
    }
    
    
    [[maybe_unused]] void Config::setDistanceView(GLint distanceView) {
        this->distanceView = distanceView;
    }
    
    
    [[maybe_unused]] GLboolean Config::getFreeMouse() const {
        return freeMouse;
    }
    
    
    [[maybe_unused]] void Config::setFreeMouse(GLboolean freeMouse) {
        this->freeMouse = freeMouse;
        SDL_SetRelativeMouseMode(freeMouse ? SDL_FALSE : SDL_TRUE);
    }
    
    
    [[maybe_unused]] void Config::switchFreeMouse() {
        this->setFreeMouse(!this->freeMouse);
    }
    
    
    [[maybe_unused]] GLboolean Config::getFaceCulling() const {
        return faceCulling;
    }
    
    
    [[maybe_unused]] void Config::setFaceCulling(GLboolean faceCulling) {
        this->faceCulling = faceCulling;
    }
    
    
    [[maybe_unused]] void Config::switchFaceCulling() {
        this->faceCulling = !this->faceCulling;
    }
    
    
    [[maybe_unused]] GLboolean Config::getOcclusionCulling() const {
        return occlusionCulling;
    }
    
    
    [[maybe_unused]] void Config::setOcclusionCulling(GLboolean occlusionCulling) {
        this->occlusionCulling = occlusionCulling;
    }
    
    
    [[maybe_unused]] void Config::switchOcclusionCulling() {
        this->occlusionCulling = !this->occlusionCulling;
    }
    
    
    [[maybe_unused]] GLboolean Config::getFrustumCulling() const {
        return frustumCulling;
    }
    
    
    [[maybe_unused]] void Config::setFrustumCulling(GLboolean frustumCulling) {
        this->frustumCulling = frustumCulling;
    }
    
    
    [[maybe_unused]] void Config::switchFrustumCulling() {
        this->frustumCulling = !this->frustumCulling;
    }
    
    
    [[maybe_unused]] GLboolean Config::getDebug() const {
        return debug;
    }
    
    
    [[maybe_unused]] void Config::setDebug(GLboolean debug) {
        this->debug = debug;
    }
    
    
    [[maybe_unused]] void Config::switchDebug() {
        this->debug = !this->debug;
    }
    
    
    [[maybe_unused]] glm::vec3 Config::getLightColor(GLint tick) {
        GLfloat value;
        
        // Day
        if (DUSK_START - DAWN_END < 0
            && ((tick >= DAWN_END && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK_START)) {
            return DAY_LIGHT_COL;
        }
        if (tick >= DAWN_END && tick <= DUSK_START) {
            return DAY_LIGHT_COL;
        }
        
        // Night
        if (DAWN_START - DUSK_END < 0
            && ((tick >= DUSK_END && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN_START)) {
            return NIGHT_LIGHT_COL;
        }
        if (tick >= DUSK_END && tick <= DAWN_START) {
            return NIGHT_LIGHT_COL;
        }
        
        // Day to Dusk
        if (DUSK - DUSK_START < 0
            && ((tick >= DUSK_START && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK)) {
            if (tick > 0 && 0 < DUSK) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                       DUSK + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(DAY_LIGHT_COL, DAWN_DUSK_LIGHT_COL, value);
        }
        if (tick >= DUSK_START && tick <= DUSK) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DUSK_START, DUSK);
            return glm::mix(DAY_LIGHT_COL, DAWN_DUSK_LIGHT_COL, value);
        }
        
        // Dusk to Night
        if (DUSK_END - DUSK < 0
            && ((tick >= DUSK && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK_END)) {
            if (tick > 0 && 0 < DUSK_END) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value =
                changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                   DUSK_END + TICK_DAY_NIGHT_CYCLE
                );
            return glm::mix(DAWN_DUSK_LIGHT_COL, NIGHT_LIGHT_COL, value);
        }
        if (tick >= DUSK && tick <= DUSK_END) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DUSK, DUSK_END);
            return glm::mix(DAWN_DUSK_LIGHT_COL, NIGHT_LIGHT_COL, value);
        }
        
        // Night to Dawn
        if (DAWN - DAWN_START < 0
            && ((tick >= DAWN_START && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN)) {
            if (tick > 0 && 0 < DAWN) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                       DAWN + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(NIGHT_LIGHT_COL, DAWN_DUSK_LIGHT_COL, value);
        }
        if (tick >= DAWN_START && tick <= DAWN) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START, DAWN);
            return glm::mix(NIGHT_LIGHT_COL, DAWN_DUSK_LIGHT_COL, value);
        }
        
        // Dawn to Day
        if (DAWN_END - DAWN < 0
            && ((tick >= DAWN && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN_END)) {
            if (tick > 0 && 0 < DAWN_END) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN,
                                       DAWN_END + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(DAWN_DUSK_LIGHT_COL, DAY_LIGHT_COL, value);
        }
        else {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN, DAWN_END);
            return glm::mix(DAWN_DUSK_LIGHT_COL, DAY_LIGHT_COL, value);
        }
    }
    
    
    [[maybe_unused]] GLfloat Config::getLightDirIntensity(GLint tick) {
        GLfloat value;
        
        // Day
        if (DUSK_START - DAWN_END < 0
            && ((tick >= DAWN_END && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK_START)) {
            return DAY_LIGHT_DIR_INTENSITY;
        }
        if (tick >= DAWN_END && tick <= DUSK_START) {
            return DAY_LIGHT_DIR_INTENSITY;
        }
        
        // Night
        if (DAWN_START - DUSK_END < 0
            && ((tick >= DUSK_END && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN_START)) {
            return NIGHT_LIGHT_DIR_INTENSITY;
        }
        if (tick >= DUSK_END && tick <= DAWN_START) {
            return NIGHT_LIGHT_DIR_INTENSITY;
        }
        
        // Day to Dusk
        if (DUSK - DUSK_START < 0
            && ((tick >= DUSK_START && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK)) {
            if (tick > 0 && 0 < DUSK) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                       DUSK + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(DAY_LIGHT_DIR_INTENSITY, DAWN_DUSK_LIGHT_DIR_INTENSITY, value);
        }
        if (tick >= DUSK_START && tick <= DUSK) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DUSK_START, DUSK);
            return glm::mix(DAY_LIGHT_DIR_INTENSITY, DAWN_DUSK_LIGHT_DIR_INTENSITY, value);
        }
        
        // Dusk to Night
        if (DUSK_END - DUSK < 0
            && ((tick >= DUSK && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK_END)) {
            if (tick > 0 && 0 < DUSK_END) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value =
                changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                   DUSK_END + TICK_DAY_NIGHT_CYCLE
                );
            return glm::mix(DAWN_DUSK_LIGHT_DIR_INTENSITY, NIGHT_LIGHT_DIR_INTENSITY, value);
        }
        if (tick >= DUSK && tick <= DUSK_END) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DUSK, DUSK_END);
            return glm::mix(DAWN_DUSK_LIGHT_DIR_INTENSITY, NIGHT_LIGHT_DIR_INTENSITY, value);
        }
        
        // Night to Dawn
        if (DAWN - DAWN_START < 0
            && ((tick >= DAWN_START && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN)) {
            if (tick > 0 && 0 < DAWN) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                       DAWN + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(NIGHT_LIGHT_DIR_INTENSITY, DAWN_DUSK_LIGHT_DIR_INTENSITY, value);
        }
        if (tick >= DAWN_START && tick <= DAWN) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START, DAWN);
            return glm::mix(NIGHT_LIGHT_DIR_INTENSITY, DAWN_DUSK_LIGHT_DIR_INTENSITY, value);
        }
        
        // Dawn to Day
        if (DAWN_END - DAWN < 0
            && ((tick >= DAWN && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN_END)) {
            if (tick > 0 && 0 < DAWN_END) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN,
                                       DAWN_END + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(DAWN_DUSK_LIGHT_DIR_INTENSITY, DAY_LIGHT_DIR_INTENSITY, value);
        }
        else {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN, DAWN_END);
            return glm::mix(DAWN_DUSK_LIGHT_DIR_INTENSITY, DAY_LIGHT_DIR_INTENSITY, value);
        }
    }
    
    
    [[maybe_unused]] GLfloat Config::getLightAmbIntensity(GLint tick) {
        GLfloat value;
        
        // Day
        if (DUSK_START - DAWN_END < 0
            && ((tick >= DAWN_END && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK_START)) {
            return DAY_LIGHT_AMB_INTENSITY;
        }
        if (tick >= DAWN_END && tick <= DUSK_START) {
            return DAY_LIGHT_AMB_INTENSITY;
        }
        
        // Night
        if (DAWN_START - DUSK_END < 0
            && ((tick >= DUSK_END && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN_START)) {
            return NIGHT_LIGHT_AMB_INTENSITY;
        }
        if (tick >= DUSK_END && tick <= DAWN_START) {
            return NIGHT_LIGHT_AMB_INTENSITY;
        }
        
        // Day to Dusk
        if (DUSK - DUSK_START < 0
            && ((tick >= DUSK_START && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK)) {
            if (tick > 0 && 0 < DUSK) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                       DUSK + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(DAY_LIGHT_AMB_INTENSITY, DAWN_DUSK_LIGHT_AMB_INTENSITY, value);
        }
        if (tick >= DUSK_START && tick <= DUSK) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DUSK_START, DUSK);
            return glm::mix(DAY_LIGHT_AMB_INTENSITY, DAWN_DUSK_LIGHT_AMB_INTENSITY, value);
        }
        
        // Dusk to Night
        if (DUSK_END - DUSK < 0
            && ((tick >= DUSK && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DUSK_END)) {
            if (tick > 0 && 0 < DUSK_END) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value =
                changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                   DUSK_END + TICK_DAY_NIGHT_CYCLE
                );
            return glm::mix(DAWN_DUSK_LIGHT_AMB_INTENSITY, NIGHT_LIGHT_AMB_INTENSITY, value);
        }
        if (tick >= DUSK && tick <= DUSK_END) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DUSK, DUSK_END);
            return glm::mix(DAWN_DUSK_LIGHT_AMB_INTENSITY, NIGHT_LIGHT_AMB_INTENSITY, value);
        }
        
        // Night to Dawn
        if (DAWN - DAWN_START < 0
            && ((tick >= DAWN_START && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN)) {
            if (tick > 0 && 0 < DAWN) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START,
                                       DAWN + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(NIGHT_LIGHT_AMB_INTENSITY, DAWN_DUSK_LIGHT_AMB_INTENSITY, value);
        }
        if (tick >= DAWN_START && tick <= DAWN) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN_START, DAWN);
            return glm::mix(NIGHT_LIGHT_AMB_INTENSITY, DAWN_DUSK_LIGHT_AMB_INTENSITY, value);
        }
        
        // Dawn to Day
        if (DAWN_END - DAWN < 0
            && ((tick >= DAWN && tick <= TICK_DAY_NIGHT_CYCLE) || tick <= DAWN_END)) {
            if (tick > 0 && 0 < DAWN_END) {
                tick += TICK_DAY_NIGHT_CYCLE;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN,
                                       DAWN_END + TICK_DAY_NIGHT_CYCLE
            );
            return glm::mix(DAWN_DUSK_LIGHT_AMB_INTENSITY, DAY_LIGHT_AMB_INTENSITY, value);
        }
        else {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), DAWN, DAWN_END);
            return glm::mix(DAWN_DUSK_LIGHT_AMB_INTENSITY, DAY_LIGHT_AMB_INTENSITY, value);
        }
    }
}

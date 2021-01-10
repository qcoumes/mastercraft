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
            case Framerate::FRAMERATE_30:
                return "30";
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
            case Framerate::FRAMERATE_30:
                this->framerate = 30;
                this->usPerFrame = static_cast<GLuint>(1. / 30. * 1e6);
                break;
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
            case Framerate::FRAMERATE_30:
                this->setFramerate(Framerate::FRAMERATE_60);
                break;
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
                this->setFramerate(Framerate::FRAMERATE_30);
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
    
    
    [[maybe_unused]] glm::vec3 Config::getSkyboxColor(GLfloat tick) {
        GLfloat value;
        
        // Day
        if (tick_dusk_start - tick_dawn_end < 0
            && ((tick >= tick_dawn_end && tick <= tick_per_day) || tick <= tick_dusk_start)) {
            return day_skybox_col;
        }
        if (tick >= tick_dawn_end && tick <= tick_dusk_start) {
            return day_skybox_col;
        }
        
        // Night
        if (tick_dawn_start - tick_dusk_end < 0
            && ((tick >= tick_dusk_end && tick <= tick_per_day) || tick <= tick_dawn_start)) {
            return night_skybox_col;
        }
        if (tick >= tick_dusk_end && tick <= tick_dawn_start) {
            return night_skybox_col;
        }
        
        // Day to Dusk
        if (tick_dusk - tick_dusk_start < 0
            && ((tick >= tick_dusk_start && tick <= tick_per_day) || tick <= tick_dusk)) {
            if (tick > 0 && 0 < tick_dusk) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                       tick_dusk + tick_per_day
            );
            return glm::mix(day_skybox_col, dawn_dusk_skybox_col, value);
        }
        if (tick >= tick_dusk_start && tick <= tick_dusk) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dusk_start, tick_dusk);
            return glm::mix(day_skybox_col, dawn_dusk_skybox_col, value);
        }
        
        // Dusk to Night
        if (tick_dusk_end - tick_dusk < 0
            && ((tick >= tick_dusk && tick <= tick_per_day) || tick <= tick_dusk_end)) {
            if (tick > 0 && 0 < tick_dusk_end) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(
                static_cast<GLfloat>(tick),
                tick_dawn_start, tick_dusk_end + tick_per_day
            );
            return glm::mix(dawn_dusk_skybox_col, night_skybox_col, value);
        }
        if (tick >= tick_dusk && tick <= tick_dusk_end) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dusk, tick_dusk_end);
            return glm::mix(dawn_dusk_skybox_col, night_skybox_col, value);
        }
        
        // Night to Dawn
        if (tick_dawn - tick_dawn_start < 0
            && ((tick >= tick_dawn_start && tick <= tick_per_day) || tick <= tick_dawn)) {
            if (tick > 0 && 0 < tick_dawn) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                       tick_dawn + tick_per_day
            );
            return glm::mix(night_skybox_col, dawn_dusk_skybox_col, value);
        }
        if (tick >= tick_dawn_start && tick <= tick_dawn) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start, tick_dawn);
            return glm::mix(night_skybox_col, dawn_dusk_skybox_col, value);
        }
        
        // Dawn to Day
        if (tick_dawn_end - tick_dawn < 0
            && ((tick >= tick_dawn && tick <= tick_per_day) || tick <= tick_dawn_end)) {
            if (tick > 0 && 0 < tick_dawn_end) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn,
                                       tick_dawn_end + tick_per_day
            );
            return glm::mix(dawn_dusk_skybox_col, day_skybox_col, value);
        }
        else {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn, tick_dawn_end);
            return glm::mix(dawn_dusk_skybox_col, day_skybox_col, value);
        }
    }
    
    
    [[maybe_unused]] glm::vec3 Config::getLightColor(GLfloat tick) {
        GLfloat value;
        
        // Day
        if (tick_dusk_start - tick_dawn_end < 0
            && ((tick >= tick_dawn_end && tick <= tick_per_day) || tick <= tick_dusk_start)) {
            return day_light_col;
        }
        if (tick >= tick_dawn_end && tick <= tick_dusk_start) {
            return day_light_col;
        }
        
        // Night
        if (tick_dawn_start - tick_dusk_end < 0
            && ((tick >= tick_dusk_end && tick <= tick_per_day) || tick <= tick_dawn_start)) {
            return night_light_col;
        }
        if (tick >= tick_dusk_end && tick <= tick_dawn_start) {
            return night_light_col;
        }
        
        // Day to Dusk
        if (tick_dusk - tick_dusk_start < 0
            && ((tick >= tick_dusk_start && tick <= tick_per_day) || tick <= tick_dusk)) {
            if (tick > 0 && 0 < tick_dusk) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                       tick_dusk + tick_per_day
            );
            return glm::mix(day_light_col, dawn_dusk_light_col, value);
        }
        if (tick >= tick_dusk_start && tick <= tick_dusk) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dusk_start, tick_dusk);
            return glm::mix(day_light_col, dawn_dusk_light_col, value);
        }
        
        // Dusk to Night
        if (tick_dusk_end - tick_dusk < 0
            && ((tick >= tick_dusk && tick <= tick_per_day) || tick <= tick_dusk_end)) {
            if (tick > 0 && 0 < tick_dusk_end) {
                tick += tick_per_day;
            }
            
            value =
                changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                   tick_dusk_end + tick_per_day
                );
            return glm::mix(dawn_dusk_light_col, night_light_col, value);
        }
        if (tick >= tick_dusk && tick <= tick_dusk_end) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dusk, tick_dusk_end);
            return glm::mix(dawn_dusk_light_col, night_light_col, value);
        }
        
        // Night to Dawn
        if (tick_dawn - tick_dawn_start < 0
            && ((tick >= tick_dawn_start && tick <= tick_per_day) || tick <= tick_dawn)) {
            if (tick > 0 && 0 < tick_dawn) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                       tick_dawn + tick_per_day
            );
            return glm::mix(night_light_col, dawn_dusk_light_col, value);
        }
        if (tick >= tick_dawn_start && tick <= tick_dawn) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start, tick_dawn);
            return glm::mix(night_light_col, dawn_dusk_light_col, value);
        }
        
        // Dawn to Day
        if (tick_dawn_end - tick_dawn < 0
            && ((tick >= tick_dawn && tick <= tick_per_day) || tick <= tick_dawn_end)) {
            if (tick > 0 && 0 < tick_dawn_end) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn,
                                       tick_dawn_end + tick_per_day
            );
            return glm::mix(dawn_dusk_light_col, day_light_col, value);
        }
        else {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn, tick_dawn_end);
            return glm::mix(dawn_dusk_light_col, day_light_col, value);
        }
    }
    
    
    [[maybe_unused]] GLfloat Config::getLightDirIntensity(GLfloat tick) const {
        GLfloat value;
        
        // Day
        if (tick_dusk_start - tick_dawn_end < 0
            && ((tick >= tick_dawn_end && tick <= tick_per_day) || tick <= tick_dusk_start)) {
            return day_light_dir_intensity;
        }
        if (tick >= tick_dawn_end && tick <= tick_dusk_start) {
            return day_light_dir_intensity;
        }
        
        // Night
        if (tick_dawn_start - tick_dusk_end < 0
            && ((tick >= tick_dusk_end && tick <= tick_per_day) || tick <= tick_dawn_start)) {
            return night_light_dir_intensity;
        }
        if (tick >= tick_dusk_end && tick <= tick_dawn_start) {
            return night_light_dir_intensity;
        }
        
        // Day to Dusk
        if (tick_dusk - tick_dusk_start < 0
            && ((tick >= tick_dusk_start && tick <= tick_per_day) || tick <= tick_dusk)) {
            if (tick > 0 && 0 < tick_dusk) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                       tick_dusk + tick_per_day
            );
            return glm::mix(day_light_dir_intensity, dawn_dusk_light_dir_intensity, value);
        }
        if (tick >= tick_dusk_start && tick <= tick_dusk) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dusk_start, tick_dusk);
            return glm::mix(day_light_dir_intensity, dawn_dusk_light_dir_intensity, value);
        }
        
        // Dusk to Night
        if (tick_dusk_end - tick_dusk < 0
            && ((tick >= tick_dusk && tick <= tick_per_day) || tick <= tick_dusk_end)) {
            if (tick > 0 && 0 < tick_dusk_end) {
                tick += tick_per_day;
            }
            
            value =
                changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                   tick_dusk_end + tick_per_day
                );
            return glm::mix(dawn_dusk_light_dir_intensity, night_light_dir_intensity, value);
        }
        if (tick >= tick_dusk && tick <= tick_dusk_end) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dusk, tick_dusk_end);
            return glm::mix(dawn_dusk_light_dir_intensity, night_light_dir_intensity, value);
        }
        
        // Night to Dawn
        if (tick_dawn - tick_dawn_start < 0
            && ((tick >= tick_dawn_start && tick <= tick_per_day) || tick <= tick_dawn)) {
            if (tick > 0 && 0 < tick_dawn) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                       tick_dawn + tick_per_day
            );
            return glm::mix(night_light_dir_intensity, dawn_dusk_light_dir_intensity, value);
        }
        if (tick >= tick_dawn_start && tick <= tick_dawn) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start, tick_dawn);
            return glm::mix(night_light_dir_intensity, dawn_dusk_light_dir_intensity, value);
        }
        
        // Dawn to Day
        if (tick_dawn_end - tick_dawn < 0
            && ((tick >= tick_dawn && tick <= tick_per_day) || tick <= tick_dawn_end)) {
            if (tick > 0 && 0 < tick_dawn_end) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn,
                                       tick_dawn_end + tick_per_day
            );
            return glm::mix(dawn_dusk_light_dir_intensity, day_light_dir_intensity, value);
        }
        else {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn, tick_dawn_end);
            return glm::mix(dawn_dusk_light_dir_intensity, day_light_dir_intensity, value);
        }
    }
    
    
    [[maybe_unused]] GLfloat Config::getLightAmbIntensity(GLfloat tick) const {
        GLfloat value;
        
        // Day
        if (tick_dusk_start - tick_dawn_end < 0
            && ((tick >= tick_dawn_end && tick <= tick_per_day) || tick <= tick_dusk_start)) {
            return day_light_amb_intensity;
        }
        if (tick >= tick_dawn_end && tick <= tick_dusk_start) {
            return day_light_amb_intensity;
        }
        
        // Night
        if (tick_dawn_start - tick_dusk_end < 0
            && ((tick >= tick_dusk_end && tick <= tick_per_day) || tick <= tick_dawn_start)) {
            return night_light_amb_intensity;
        }
        if (tick >= tick_dusk_end && tick <= tick_dawn_start) {
            return night_light_amb_intensity;
        }
        
        // Day to Dusk
        if (tick_dusk - tick_dusk_start < 0
            && ((tick >= tick_dusk_start && tick <= tick_per_day) || tick <= tick_dusk)) {
            if (tick > 0 && 0 < tick_dusk) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                       tick_dusk + tick_per_day
            );
            return glm::mix(day_light_amb_intensity, dawn_dusk_light_amb_intensity, value);
        }
        if (tick >= tick_dusk_start && tick <= tick_dusk) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dusk_start, tick_dusk);
            return glm::mix(day_light_amb_intensity, dawn_dusk_light_amb_intensity, value);
        }
        
        // Dusk to Night
        if (tick_dusk_end - tick_dusk < 0
            && ((tick >= tick_dusk && tick <= tick_per_day) || tick <= tick_dusk_end)) {
            if (tick > 0 && 0 < tick_dusk_end) {
                tick += tick_per_day;
            }
            
            value =
                changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                   tick_dusk_end + tick_per_day
                );
            return glm::mix(dawn_dusk_light_amb_intensity, night_light_amb_intensity, value);
        }
        if (tick >= tick_dusk && tick <= tick_dusk_end) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dusk, tick_dusk_end);
            return glm::mix(dawn_dusk_light_amb_intensity, night_light_amb_intensity, value);
        }
        
        // Night to Dawn
        if (tick_dawn - tick_dawn_start < 0
            && ((tick >= tick_dawn_start && tick <= tick_per_day) || tick <= tick_dawn)) {
            if (tick > 0 && 0 < tick_dawn) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start,
                                       tick_dawn + tick_per_day
            );
            return glm::mix(night_light_amb_intensity, dawn_dusk_light_amb_intensity, value);
        }
        if (tick >= tick_dawn_start && tick <= tick_dawn) {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn_start, tick_dawn);
            return glm::mix(night_light_amb_intensity, dawn_dusk_light_amb_intensity, value);
        }
        
        // Dawn to Day
        if (tick_dawn_end - tick_dawn < 0
            && ((tick >= tick_dawn && tick <= tick_per_day) || tick <= tick_dawn_end)) {
            if (tick > 0 && 0 < tick_dawn_end) {
                tick += tick_per_day;
            }
            
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn,
                                       tick_dawn_end + tick_per_day
            );
            return glm::mix(dawn_dusk_light_amb_intensity, day_light_amb_intensity, value);
        }
        else {
            value = changeIntervalTo01(static_cast<GLfloat>(tick), tick_dawn, tick_dawn_end);
            return glm::mix(dawn_dusk_light_amb_intensity, day_light_amb_intensity, value);
        }
    }
    
    
    [[maybe_unused]] void Config::setSecondsPerDay(GLint seconds) {
        this->seconds_per_day = seconds;
        this->tick_per_day = static_cast<GLfloat>(seconds * TICK_PER_SEC);
        this->tick_dawn_start = tick_per_day / 360 * 0;
        this->tick_dawn = tick_per_day / 360 * 15;
        this->tick_dawn_end = tick_per_day / 360 * 30;
        this->tick_dusk_start = tick_per_day / 360 * 190;
        this->tick_dusk = tick_per_day / 360 * 205;
        this->tick_dusk_end = tick_per_day / 360 * 220;
    }
    
    
    [[maybe_unused]] GLint Config::getSecondsPerDay() const {
        return this->seconds_per_day;
    }
    
    
    [[maybe_unused]] GLfloat Config::getTickPerDay() const {
        return this->tick_per_day;
    }
    
    
    [[maybe_unused]] GLfloat Config::getTickDawnStart() const {
        return this->tick_dawn_start;
    }
    
    
    [[maybe_unused]] GLfloat Config::getTickDawn() const {
        return this->tick_dawn;
    }
    
    
    [[maybe_unused]] GLfloat Config::getTickDawnEnd() const {
        return this->tick_dawn_end;
    }
    
    
    [[maybe_unused]] GLfloat Config::getTickDuskStart() const {
        return this->tick_dusk_start;
    }
    
    
    [[maybe_unused]] GLfloat Config::getTickDusk() const {
        return this->tick_dusk;
    }
    
    
    [[maybe_unused]] GLfloat Config::getTickDuskEnd() const {
        return this->tick_dusk_end;
    }
    
    
    [[maybe_unused]] glm::vec3 Config::getDawnDuskSkyboxCol() const {
        return this->dawn_dusk_skybox_col;
    }
    
    
    [[maybe_unused]] glm::vec3 Config::getDaySkyboxCol() const {
        return this->day_skybox_col;
    }
    
    
    [[maybe_unused]] glm::vec3 Config::getNightSkyboxCol() const {
        return this->night_skybox_col;
    }
    
    
    [[maybe_unused]] glm::vec3 Config::getDawnDuskLightCol() const {
        return this->dawn_dusk_light_col;
    }
    
    
    [[maybe_unused]] glm::vec3 Config::getDayLightCol() const {
        return this->day_light_col;
    }
    
    
    [[maybe_unused]] glm::vec3 Config::getNightLightCol() const {
        return this->night_light_col;
    }
    
    
    [[maybe_unused]] GLfloat Config::getDawnDuskLightDirIntensity() const {
        return this->dawn_dusk_light_dir_intensity;
    }
    
    
    [[maybe_unused]] GLfloat Config::getDayLightDirIntensity() const {
        return this->day_light_dir_intensity;
    }
    
    
    [[maybe_unused]] GLfloat Config::getNightLightDirIntensity() const {
        return this->night_light_dir_intensity;
    }
    
    
    [[maybe_unused]] GLfloat Config::getDawnDuskLightAmbIntensity() const {
        return this->dawn_dusk_light_amb_intensity;
    }
    
    
    [[maybe_unused]] GLfloat Config::getDayLightAmbIntensity() const {
        return this->day_light_amb_intensity;
    }
    
    
    [[maybe_unused]] GLfloat Config::getNightLightAmbIntensity() const {
        return this->night_light_amb_intensity;
    }
    
    
    [[maybe_unused]] void Config::setDawnDuskSkyboxCol(const glm::vec3 &dawnDuskSkyboxCol) {
        this->dawn_dusk_skybox_col = dawnDuskSkyboxCol;
    }
    
    
    [[maybe_unused]] void Config::setDaySkyboxCol(const glm::vec3 &daySkyboxCol) {
        this->day_skybox_col = daySkyboxCol;
    }
    
    
    [[maybe_unused]] void Config::setNightSkyboxCol(const glm::vec3 &nightSkyboxCol) {
        this->night_skybox_col = nightSkyboxCol;
    }
    
    
    [[maybe_unused]] void Config::setDawnDuskLightCol(const glm::vec3 &dawnDuskLightCol) {
        this->dawn_dusk_light_col = dawnDuskLightCol;
    }
    
    
    [[maybe_unused]] void Config::setDayLightCol(const glm::vec3 &dayLightCol) {
        this->day_light_col = dayLightCol;
    }
    
    
    [[maybe_unused]] void Config::setNightLightCol(const glm::vec3 &nightLightCol) {
        this->night_light_col = nightLightCol;
    }
    
    
    [[maybe_unused]] void Config::setDawnDuskLightDirIntensity(GLfloat dawnDuskLightDirIntensity) {
        this->dawn_dusk_light_dir_intensity = dawnDuskLightDirIntensity;
    }
    
    
    [[maybe_unused]] void Config::setDayLightDirIntensity(GLfloat dayLightDirIntensity) {
        this->day_light_dir_intensity = dayLightDirIntensity;
    }
    
    
    [[maybe_unused]] void Config::setNightLightDirIntensity(GLfloat nightLightDirIntensity) {
        this->night_light_dir_intensity = nightLightDirIntensity;
    }
    
    
    [[maybe_unused]] void Config::setDawnDuskLightAmbIntensity(GLfloat dawnDuskLightAmbIntensity) {
        this->dawn_dusk_light_amb_intensity = dawnDuskLightAmbIntensity;
    }
    
    
    [[maybe_unused]] void Config::setDayLightAmbIntensity(GLfloat dayLightAmbIntensity) {
        this->day_light_amb_intensity = dayLightAmbIntensity;
    }
    
    
    [[maybe_unused]] void Config::setNightLightAmbIntensity(GLfloat nightLightAmbIntensity) {
        this->night_light_amb_intensity = nightLightAmbIntensity;
    }
}

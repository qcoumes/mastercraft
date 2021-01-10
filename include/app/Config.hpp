#ifndef OPENGL_CONFIG_HPP
#define OPENGL_CONFIG_HPP

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <misc/INonCopyable.hpp>
#include <tool/Window.hpp>
#include <tool/Camera.hpp>


namespace app {
    
    enum Framerate {
        FRAMERATE_30,
        FRAMERATE_60,
        FRAMERATE_75,
        FRAMERATE_120,
        FRAMERATE_144,
        FRAMERATE_180,
        FRAMERATE_240,
        FRAMERATE_VSYNC,
        FRAMERATE_UNCAPPED,
        FRAMERATE_LAST = FRAMERATE_UNCAPPED
    };
    
    
    
    class Config : public misc::ISingleton {
        
        public:
            
            // Time
            static constexpr GLint64 TICK_PER_SEC = 60;
            static constexpr GLint64 MS_PER_TICK = static_cast<GLint64>(1. / TICK_PER_SEC * 1000.);
            
            // Terrain generation
            /** Minimum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_MIN_H = 128;
            /** Maximum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_MAX_H = 192;
            static constexpr GLubyte GEN_CARVING_H = GEN_MIN_H + 30;
            static constexpr GLubyte GEN_INTERVAL_H = GEN_MAX_H - GEN_MIN_H;
            static constexpr GLubyte GEN_WATER_LEVEL = GEN_MIN_H + 22;
            
            static_assert(GEN_MIN_H < GEN_MAX_H);
        
        private:
            // Time
            GLint seconds_per_day = 40;
            GLfloat tick_per_day = static_cast<GLfloat>(seconds_per_day * TICK_PER_SEC);
            GLfloat tick_dawn_start = tick_per_day / 360 * 0;
            GLfloat tick_dawn = tick_per_day / 360 * 15;
            GLfloat tick_dawn_end = tick_per_day / 360 * 30;
            GLfloat tick_dusk_start = tick_per_day / 360 * 190;
            GLfloat tick_dusk = tick_per_day / 360 * 205;
            GLfloat tick_dusk_end = tick_per_day / 360 * 220;
            GLuint framerate = 0;      /**< Framerate value. */
            GLuint vSyncFramerate = 0; /**< Framerate when VSYNC is enable. */
            GLuint usPerFrame = 0;     /**< Number of microseconds between frame. */
            Framerate framerateOpt = Framerate::FRAMERATE_VSYNC;  /**< Chosen Framerate. */
            
            // Skybox and lighting
            glm::vec3 dawn_dusk_skybox_col = glm::vec3(255.f, 188.f, 60.f) / 255.f;
            glm::vec3 day_skybox_col = glm::vec3(42.f, 102.f, 175.f) / 255.f;
            glm::vec3 night_skybox_col = glm::vec3(0.f, 0.f, 0.f) / 255.f;
            
            glm::vec3 dawn_dusk_light_col = glm::vec3(255.f, 60.f, 60.f) / 255.f;
            glm::vec3 day_light_col = glm::vec3(255.f, 255.f, 220.f) / 255.f;
            glm::vec3 night_light_col = glm::vec3(20.f, 60.f, 180.f) / 255.f;
            
            GLfloat dawn_dusk_light_dir_intensity = .4f;
            GLfloat day_light_dir_intensity = 1.f;
            GLfloat night_light_dir_intensity = 0.f;
            
            GLfloat dawn_dusk_light_amb_intensity = .35f;
            GLfloat day_light_amb_intensity = .5f;
            GLfloat night_light_amb_intensity = .25f;
            
            
            // Hardware
            std::string GPUInfo;     /**< GPU brand information. */
            std::string GPUDriver;   /**< Version of the GPU's driver. */
            std::vector<std::string> GPUExtensions; /**< Extensions of the GPU's driver. */
            std::string GLEWVersion; /**< Version of GLEW. */
            std::string CPUInfo;     /**< CPU brand and core information. */
            
            // Screen
            GLint width = 800;      /**< Width of the window. */
            GLint height = 600;     /**< Height of the window. */
            GLfloat fov = 70;       /**< Field of view, default to 70. */
            GLint distanceView = 2; /**< Draw distance as the radius of SuperChunk rendered. */
            GLboolean debug = true; /**< Display debug or not. */
            
            // Control
            GLboolean freeMouse = false;    /**< Allow to freely move the mouse. */
            GLfloat mouseSensitivity = 1.f; /**< Sensitivity of the mouse. */
            GLfloat speed = 0.8f;           /**< Speed of the camera. */
            
            // Optimization
            GLboolean faceCulling = true;      /**< Whether face culling is enabled. */
            GLboolean occlusionCulling = true; /**< Whether occlusion culling is enabled. */
            GLboolean frustumCulling = true;   /**< Whether frustum culling is enabled. */
            
            Config() = default;
        
        public:
            
            static Config *getInstance();
            
            void init(const tool::Window &window, tool::Camera &camera);
            
            [[maybe_unused]] void setSecondsPerDay(GLint seconds);
            
            [[maybe_unused]] void setMouseSensitivity(GLfloat mouseSensitivity);
            
            [[maybe_unused]] void setSpeed(GLfloat speed);
            
            [[maybe_unused]] void setWidth(GLint width);
            
            [[maybe_unused]] void setHeight(GLint height);
            
            [[maybe_unused]] void setFramerate(Framerate framerate);
            
            [[maybe_unused]] void cycleFramerate();
            
            [[maybe_unused]] void setFov(GLfloat fov, const tool::Window &window,
                                         tool::Camera &camera);
            
            [[maybe_unused]] void setDistanceView(GLint distanceView);
            
            [[maybe_unused]] void setFreeMouse(GLboolean freeMouse);
            
            [[maybe_unused]] void switchFreeMouse();
            
            [[maybe_unused]] void setFaceCulling(GLboolean faceCulling);
            
            [[maybe_unused]] void switchFaceCulling();
            
            [[maybe_unused]] void setOcclusionCulling(GLboolean occlusionCulling);
            
            [[maybe_unused]] void switchOcclusionCulling();
            
            [[maybe_unused]] void setFrustumCulling(GLboolean frustumCulling);
            
            [[maybe_unused]] void switchFrustumCulling();
            
            [[maybe_unused]] void setDebug(GLboolean debug);
            
            [[maybe_unused]] void switchDebug();
            
            [[maybe_unused]] void setDawnDuskSkyboxCol(const glm::vec3 &dawnDuskSkyboxCol);
            
            [[maybe_unused]] void setDaySkyboxCol(const glm::vec3 &daySkyboxCol);
            
            [[maybe_unused]] void setNightSkyboxCol(const glm::vec3 &nightSkyboxCol);
            
            [[maybe_unused]] void setDawnDuskLightCol(const glm::vec3 &dawnDuskLightCol);
            
            [[maybe_unused]] void setDayLightCol(const glm::vec3 &dayLightCol);
            
            [[maybe_unused]] void setNightLightCol(const glm::vec3 &nightLightCol);
            
            [[maybe_unused]] void setDawnDuskLightDirIntensity(GLfloat dawnDuskLightDirIntensity);
            
            [[maybe_unused]] void setDayLightDirIntensity(GLfloat dayLightDirIntensity);
            
            [[maybe_unused]] void setNightLightDirIntensity(GLfloat nightLightDirIntensity);
            
            [[maybe_unused]] void setDawnDuskLightAmbIntensity(GLfloat dawnDuskLightAmbIntensity);
            
            [[maybe_unused]] void setDayLightAmbIntensity(GLfloat dayLightAmbIntensity);
            
            [[maybe_unused]] void setNightLightAmbIntensity(GLfloat nightLightAmbIntensity);
            
            [[nodiscard, maybe_unused]] std::string getGPUInfo() const;
            
            [[nodiscard, maybe_unused]] GLint getSecondsPerDay() const;
            
            [[nodiscard, maybe_unused]] GLfloat getTickPerDay() const;
            
            [[nodiscard, maybe_unused]] std::string getGPUDriver() const;
            
            [[nodiscard, maybe_unused]] std::vector<std::string> getGPUExtensions() const;
            
            [[nodiscard, maybe_unused]] std::string getGlewVersion() const;
            
            [[nodiscard, maybe_unused]] std::string getCpuInfo() const;
            
            [[nodiscard, maybe_unused]] GLfloat getMouseSensitivity() const;
            
            [[nodiscard, maybe_unused]] GLfloat getSpeed() const;
            
            [[nodiscard, maybe_unused]] GLint getWidth() const;
            
            [[nodiscard, maybe_unused]] GLint getHeight() const;
            
            [[nodiscard, maybe_unused]] GLuint getFramerate() const;
            
            [[nodiscard, maybe_unused]] GLuint getFramerateInv() const;
            
            [[nodiscard, maybe_unused]] Framerate getFramerateOpt() const;
            
            [[nodiscard, maybe_unused]] std::string getFramerateString(GLint fps = -1) const;
            
            [[nodiscard, maybe_unused]] GLfloat getFov() const;
            
            [[nodiscard, maybe_unused]] GLint getDistanceView() const;
            
            [[nodiscard, maybe_unused]] GLboolean getFreeMouse() const;
            
            [[nodiscard, maybe_unused]] GLboolean getFaceCulling() const;
            
            [[nodiscard, maybe_unused]] GLboolean getOcclusionCulling() const;
            
            [[nodiscard, maybe_unused]] GLboolean getFrustumCulling() const;
            
            [[nodiscard, maybe_unused]] GLboolean getDebug() const;
            
            [[nodiscard, maybe_unused]] glm::vec3 getSkyboxColor(GLfloat tick);
            
            [[nodiscard, maybe_unused]] glm::vec3 getLightColor(GLfloat tick);
            
            [[nodiscard, maybe_unused]] GLfloat getLightDirIntensity(GLfloat tick) const;
            
            [[nodiscard, maybe_unused]] GLfloat getLightAmbIntensity(GLfloat tick) const;
            
            [[nodiscard, maybe_unused]] GLfloat getTickDawnStart() const;
            
            [[nodiscard, maybe_unused]] GLfloat getTickDawn() const;
            
            [[nodiscard, maybe_unused]] GLfloat getTickDawnEnd() const;
            
            [[nodiscard, maybe_unused]] GLfloat getTickDuskStart() const;
            
            [[nodiscard, maybe_unused]] GLfloat getTickDusk() const;
            
            [[nodiscard, maybe_unused]] GLfloat getTickDuskEnd() const;
            
            [[nodiscard, maybe_unused]] glm::vec3 getDawnDuskSkyboxCol() const;
            
            [[nodiscard, maybe_unused]] glm::vec3 getDaySkyboxCol() const;
            
            [[nodiscard, maybe_unused]] glm::vec3 getNightSkyboxCol() const;
            
            [[nodiscard, maybe_unused]] glm::vec3 getDawnDuskLightCol() const;
            
            [[nodiscard, maybe_unused]] glm::vec3 getDayLightCol() const;
            
            [[nodiscard, maybe_unused]] glm::vec3 getNightLightCol() const;
            
            [[nodiscard, maybe_unused]] GLfloat getDawnDuskLightDirIntensity() const;
            
            [[nodiscard, maybe_unused]] GLfloat getDayLightDirIntensity() const;
            
            [[nodiscard, maybe_unused]] GLfloat getNightLightDirIntensity() const;
            
            [[nodiscard, maybe_unused]] GLfloat getDawnDuskLightAmbIntensity() const;
            
            [[nodiscard, maybe_unused]] GLfloat getDayLightAmbIntensity() const;
            
            [[nodiscard, maybe_unused]] GLfloat getNightLightAmbIntensity() const;
    };
}

#endif // OPENGL_CONFIG_HPP

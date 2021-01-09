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
            static constexpr GLint SECONDS_DAY_NIGHT_CYCLE = 40;
            static constexpr GLint TICK_DAY_NIGHT_CYCLE = SECONDS_DAY_NIGHT_CYCLE * TICK_PER_SEC;
            static constexpr GLint64 MS_PER_TICK = static_cast<GLint64>(1. / TICK_PER_SEC * 1000.);
            
            // Terrain generation
            /** Minimum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_MIN_HEIGHT = 128;
            /** Maximum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_MAX_HEIGHT = 192;
            static constexpr GLubyte GEN_CARVING_HEIGHT = GEN_MIN_HEIGHT + 30;
            static constexpr GLubyte GEN_INTERVAL_HEIGHT = GEN_MAX_HEIGHT - GEN_MIN_HEIGHT;
            static constexpr GLubyte GEN_WATER_LEVEL = GEN_MIN_HEIGHT + 22;
            
            // Skybox and lighting
            static constexpr GLint DAWN_START = TICK_DAY_NIGHT_CYCLE / 360 * 0;
            static constexpr GLint DAWN = TICK_DAY_NIGHT_CYCLE / 360 * 15;
            static constexpr GLint DAWN_END = TICK_DAY_NIGHT_CYCLE / 360 * 30;
            
            static constexpr GLint DUSK_START = TICK_DAY_NIGHT_CYCLE / 360 * 190;
            static constexpr GLint DUSK = TICK_DAY_NIGHT_CYCLE / 360 * 205;
            static constexpr GLint DUSK_END = TICK_DAY_NIGHT_CYCLE / 360 * 220;
            
            static constexpr glm::vec3 DAWN_DUSK_SKYBOX_COL = glm::vec3(255.f, 188.f, 60.f) / 255.f;
            static constexpr glm::vec3 DAY_SKYBOX_COL = glm::vec3(42.f, 102.f, 175.f) / 255.f;
            static constexpr glm::vec3 NIGHT_SKYBOX_COL = glm::vec3(0.f, 0.f, 0.f) / 255.f;
            
            static constexpr glm::vec3 DAWN_DUSK_LIGHT_COL = glm::vec3(255.f, 60.f, 60.f) / 255.f;
            static constexpr glm::vec3 DAY_LIGHT_COL = glm::vec3(255.f, 255.f, 220.f) / 255.f;
            static constexpr glm::vec3 NIGHT_LIGHT_COl = glm::vec3(20.f, 60.f, 180.f) / 255.f;
            
            static constexpr GLfloat DAWN_DUSK_LIGHT_DIR_INTENSITY = .4f;
            static constexpr GLfloat DAY_LIGHT_DIR_INTENSITY = 1.f;
            static constexpr GLfloat NIGHT_LIGHT_DIR_INTENSITY = 0.f;
            
            static constexpr GLfloat DAWN_DUSK_LIGHT_AMB_INTENSITY = .3f;
            static constexpr GLfloat DAY_LIGHT_AMB_INTENSITY = .4f;
            static constexpr GLfloat NIGHT_LIGHT_AMB_INTENSITY = .15f;
            
            static_assert(GEN_MIN_HEIGHT < GEN_MAX_HEIGHT);
        
        private:
            
            // Hardware
            std::string GPUInfo;     /**< GPU brand information. */
            std::string GPUDriver;   /**< Version of the GPU's driver. */
            std::vector<std::string> GPUExtensions; /**< Version of the GPU's driver. */
            std::string GLEWVersion; /**< Version of GLEW. */
            std::string CPUInfo;     /**< CPU brand and core information. */
            
            // Screen
            GLint width = 800;       /**< Width of the window. */
            GLint height = 600;      /**< Height of the window. */
            GLfloat fov = 70;        /**< Field of view, default to 70. */
            GLboolean debug = true;  /**< Display debug or not. */
            
            // Control
            GLboolean freeMouse = false;    /**< Allow to freely move the mouse. */
            GLfloat mouseSensitivity = 1.f; /**< Sensitivity of the mouse. */
            GLfloat speed = 0.2f;           /**< Speed of the camera. */
            
            // Time
            GLuint framerate = 0;      /**< Framerate value. */
            GLuint vSyncFramerate = 0; /**< Framerate when VSYNC is enable. */
            GLuint usPerFrame = 0;     /**< Number of microseconds between frame. */
            Framerate framerateOpt = Framerate::FRAMERATE_VSYNC;  /**< Chosen Framerate. */
            
            // Optimization
            GLboolean faceCulling = true;      /**< Whether face culling is enabled. */
            GLboolean occlusionCulling = true; /**< Whether occlusion culling is enabled. */
            GLboolean frustumCulling = true;   /**< Whether frustum culling is enabled. */
            
            
            Config() = default;
        
        public:
            
            static Config *getInstance();
            
            void init(const tool::Window &window, tool::Camera &camera);
            
            void setMouseSensitivity(GLfloat mouseSensitivity);
            
            void setSpeed(GLfloat speed);
            
            void setWidth(GLint width);
            
            void setHeight(GLint height);
            
            void setFramerate(Framerate framerate);
            
            void cycleFramerate();
            
            void setFov(GLfloat fov, const tool::Window &window, tool::Camera &camera);
            
            void setFreeMouse(GLboolean freeMouse);
            
            void switchFreeMouse();
            
            void setFaceCulling(GLboolean faceCulling);
            
            void switchFaceCulling();
            
            void setOcclusionCulling(GLboolean occlusionCulling);
            
            void switchOcclusionCulling();
            
            void setFrustumCulling(GLboolean frustumCulling);
            
            void switchFrustumCulling();
            
            void setDebug(GLboolean debug);
            
            void switchDebug();
            
            [[nodiscard]] std::string getGPUInfo() const;
            
            [[nodiscard]] std::string getGPUDriver() const;
            
            [[nodiscard]] std::vector<std::string> getGPUExtensions() const;
            
            [[nodiscard]] std::string getGlewVersion() const;
            
            [[nodiscard]] std::string getCpuInfo() const;
            
            [[nodiscard]] GLfloat getMouseSensitivity() const;
            
            [[nodiscard]] GLfloat getSpeed() const;
            
            [[nodiscard]] GLint getWidth() const;
            
            [[nodiscard]] GLint getHeight() const;
            
            [[nodiscard]] GLuint getFramerate() const;
            
            [[nodiscard]] GLuint getFramerateInv() const;
            
            [[nodiscard]] Framerate getFramerateOpt() const;
            
            [[nodiscard]] std::string getFramerateString(GLint fps = -1) const;
            
            [[nodiscard]] GLfloat getFov() const;
            
            [[nodiscard]] GLboolean getFreeMouse() const;
            
            [[nodiscard]] GLboolean getFaceCulling() const;
            
            [[nodiscard]] GLboolean getOcclusionCulling() const;
            
            [[nodiscard]] GLboolean getFrustumCulling() const;
            
            [[nodiscard]] GLboolean getDebug() const;
    };
}

#endif // OPENGL_CONFIG_HPP

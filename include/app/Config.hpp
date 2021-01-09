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
            static constexpr GLubyte GEN_MIN_H = 128;
            /** Maximum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_MAX_H = 192;
            static constexpr GLubyte GEN_CARVING_H = GEN_MIN_H + 30;
            static constexpr GLubyte GEN_INTERVAL_H = GEN_MAX_H - GEN_MIN_H;
            static constexpr GLubyte GEN_WATER_LEVEL = GEN_MIN_H + 22;
            
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
            static constexpr glm::vec3 NIGHT_LIGHT_COL = glm::vec3(20.f, 60.f, 180.f) / 255.f;
            
            static constexpr GLfloat DAWN_DUSK_LIGHT_DIR_INTENSITY = .4f;
            static constexpr GLfloat DAY_LIGHT_DIR_INTENSITY = 1.f;
            static constexpr GLfloat NIGHT_LIGHT_DIR_INTENSITY = 0.f;
            
            static constexpr GLfloat DAWN_DUSK_LIGHT_AMB_INTENSITY = .3f;
            static constexpr GLfloat DAY_LIGHT_AMB_INTENSITY = .4f;
            static constexpr GLfloat NIGHT_LIGHT_AMB_INTENSITY = .15f;
            
            static_assert(GEN_MIN_H < GEN_MAX_H);
            
            // Stats
            GLuint superchunk = 0;          /**< Number of SuperChunk loaded. */
            GLuint chunk = 0;               /**< Number of Chunk loaded. */
            GLuint cube = 0;                /**< Number of cube loaded. */
            GLuint face = 0;                /**< Number of face loaded. */
            GLuint rendered_face = 0;       /**< Number of face rendered. */
            GLuint64 occludedFace = 0;      /**< Number of face occluded. */
            GLuint64 frustumCulledFace = 0; /**< Number of face culled. */
        
        private:
            
            // Hardware
            std::string GPUInfo;     /**< GPU brand information. */
            std::string GPUDriver;   /**< Version of the GPU's driver. */
            std::vector<std::string> GPUExtensions; /**< Version of the GPU's driver. */
            std::string GLEWVersion; /**< Version of GLEW. */
            std::string CPUInfo;     /**< CPU brand and core information. */
            
            // Screen
            GLint width = 800;      /**< Width of the window. */
            GLint height = 600;     /**< Height of the window. */
            GLfloat fov = 70;       /**< Field of view, default to 70. */
            GLint distanceView = 6; /**< Draw distance as the radius of SuperChunk rendered. */
            GLboolean debug = true; /**< Display debug or not. */
            
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
            
            [[nodiscard, maybe_unused]] std::string getGPUInfo() const;
            
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
            
            [[nodiscard, maybe_unused]] static glm::vec3 getLightColor(GLint tick);
            
            [[nodiscard, maybe_unused]] static GLfloat getLightDirIntensity(GLint tick);
            
            [[nodiscard, maybe_unused]] static GLfloat getLightAmbIntensity(GLint tick);
    };
}

#endif // OPENGL_CONFIG_HPP

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
            static constexpr GLint64 TICK_PER_SEC = 60;
            static constexpr GLint64 MS_PER_TICK = static_cast<GLint64>(1. / TICK_PER_SEC * 1000.);
        
        private:
            std::string GPUInfo;     /**< GPU brand information. */
            std::string GPUDriver;   /**< Version of the GPU's driver. */
            std::vector<std::string> GPUExtensions; /**< Version of the GPU's driver. */
            std::string GLEWVersion; /**< Version of GLEW. */
            std::string CPUInfo;     /**< CPU brand and core information. */
            
            GLint width = 800;  /**< Width of the window. */
            GLint height = 600; /**< Height of the window. */
            
            GLfloat mouseSensitivity = 1.f; /**< Sensitivity of the mouse. */
            GLfloat speed = 0.2f;           /**< Speed of the camera. */
            GLfloat fov = 70;               /**< Field of view, default to 70. */
            
            GLuint framerate = 0;      /**< Framerate value. */
            GLuint vSyncFramerate = 0; /**< Framerate when VSYNC is enable. */
            GLuint usPerFrame = 0;     /**< Number of microseconds between frame. */
            Framerate framerateOpt = Framerate::FRAMERATE_VSYNC;  /**< Chosen Framerate. */
            
            GLboolean freeMouse = false;       /**< Allow to freely move the mouse. */
            GLboolean faceCulling = true;      /**< Whether face culling is enabled. */
            GLboolean occlusionCulling = true; /**< Whether occlusion culling is enabled. */
            GLboolean frustumCulling = true;   /**< Whether frustum culling is enabled. */
            GLboolean debug = true;            /**< Whether debug display. */
            
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

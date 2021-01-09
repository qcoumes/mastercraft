#include <lodepng/lodepng.hpp>

#include <misc/Image.hpp>
#include <iostream>


namespace misc {
    
    Image::Image(unsigned int t_width, unsigned int t_height, std::vector<glm::vec4> t_pixels) :
            width(t_width), height(t_height), pixels(std::move(t_pixels)) {
    }
    
    
    Image *Image::loadPNG(const std::string &path) {
        static constexpr float SCALE = 1.f / 255.f;
        
        std::vector<glm::vec4> pixels;
        std::vector<GLubyte> raw;
        GLuint width, height;
        
        GLuint error = lodepng::decode(raw, width, height, path);
        if (error) {
            std::string msg = "Error: Could not load image '" + path + "': " + lodepng_error_text(error);
            throw std::runtime_error(msg);
        }
        
        pixels.resize(raw.size() / 4);
        for (GLuint64 i = 0; i < pixels.size(); i++) {
            pixels[i] = { raw[i * 4] * SCALE, raw[i * 4 + 1] * SCALE, raw[i * 4 + 2] * SCALE, raw[i * 4 + 3] * SCALE };
        }
        
        return new Image(width, height, pixels);
    }
    
    
    GLuint Image::getWidth() const {
        return width;
    }
    
    
    GLuint Image::getHeight() const {
        return height;
    }
    
    
    const glm::vec4 *Image::getPixels() const {
        return pixels.data();
    }
    
    
    glm::vec4 *Image::getPixels() {
        return pixels.data();
    }
}

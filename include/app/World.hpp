#ifndef OPENGL_WORLD_HPP
#define OPENGL_WORLD_HPP

#include <tool/Rendered.hpp>
#include <misc/ISingleton.hpp>
#include <cube/ChunkManager.hpp>
#include <entity/Skybox.hpp>
#include <entity/Sun.hpp>


namespace app {
    class World : public misc::ISingleton, public tool::Rendered {
    
        public:
            std::unique_ptr<cube::ChunkManager> chunkManager = nullptr;
            std::unique_ptr<entity::Skybox> skybox;
            std::unique_ptr<entity::Sun> sun = nullptr;
            GLboolean underwater = false;
            GLint tickCycle = 0;

            World();
        
            void update() override;
        
            void render() const override;
    };
}


#endif //OPENGL_WORLD_HPP

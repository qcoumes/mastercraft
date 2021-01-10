
#include <app/World.hpp>
#include <app/Engine.hpp>


namespace app {
    
    World::World()  {
        misc::Image *atlas = misc::Image::loadPNG("../assets/block/atlas.png");
        
        this->chunkManager = std::make_unique<cube::ChunkManager>(atlas);
        this->skybox = std::make_unique<entity::Skybox>();
        this->sun = std::make_unique<entity::Sun>();
        this->chunkManager->init();
    }
    
    
    void World::update() {
        app::Engine *engine = app::Engine::getInstance();
    
        this->chunkManager->update();
        this->sun->update();
    
        this->underwater = (
            chunkManager->get(engine->camera->getPosition()) == cube::CubeData::WATER
        );
    }
    
    
    void World::render() const {
        this->chunkManager->render();
        this->skybox->render();
        this->sun->render();
    }
}

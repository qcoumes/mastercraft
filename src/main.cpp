#include <app/Engine.hpp>


using namespace app;


int main(int argc, char **argv) {
    Engine *engine = Engine::getInstance();
    
    engine->init();
    
    while (engine->isRunning()) {
        
        if (engine->tick()) {
            engine->update();
        }
        
        engine->render();
    }
    
    engine->cleanup();
    
    return EXIT_SUCCESS;
}


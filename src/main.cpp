#include <app/Engine.hpp>


using namespace app;


int main(int argc, char **argv) {
    Engine *game = Engine::getInstance();
    
    game->init();
    
    while (game->isRunning()) {
        
        if (game->tick()) {
            game->update();
        }
        
        game->render();
    }
    
    game->cleanup();
    
    return EXIT_SUCCESS;
}


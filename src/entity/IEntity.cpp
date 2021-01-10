#include <entity/IEntity.hpp>


namespace entity {
    
    IEntity::IEntity(const glm::vec3 &pos): position(pos) {
    }
    
    
    glm::vec3 IEntity::getPosition() {
        return this->position;
    }
}

#include <iostream>

#include <tool/Input.hpp>


namespace tool {
    
    void InputState::reset() {
        this->released = false;
        this->pressed = false;
    }
    
    
    std::ostream &operator<<(std::ostream &os, const InputState &inputState) {
        os << "Pressed:  " << (inputState.pressed ? "true" : "false") << std::endl;
        os << "Released: " << (inputState.released ? "true" : "false") << std::endl;
        os << "Held:     " << (inputState.held ? "true" : "false") << std::endl;
        return os;
    }
    
    
    void InputState::update(uint8_t state) {
        if (state == SDL_PRESSED) {
            this->pressed = true;
            this->held = true;
        }
        
        else if (state == SDL_RELEASED) {
            this->released = true;
            this->held = false;
        }
    }
    
    
    void Input::handleMouseMotion(const SDL_MouseMotionEvent &event) {
        this->mouseMotion = { event.xrel, event.yrel };
    }
    
    
    void Input::handleMouseButton(const SDL_MouseButtonEvent &event) {
        if (!this->buttons.count(event.button)) {
            this->buttons.emplace(event.button, InputState());
        }
        
        this->buttons[event.button].update(event.state);
    }
    
    
    void Input::handleMouseWheel(const SDL_MouseWheelEvent &event) {
        if (event.direction == SDL_MOUSEWHEEL_NORMAL) {
            this->wheelMotion = { event.x, event.y };
        }
        else {
            this->wheelMotion = { -event.x, -event.y };
        }
    }
    
    
    void Input::handleKeyboard(const SDL_KeyboardEvent &event) {
        if (!this->keys.count(event.keysym.scancode)) {
            this->keys.emplace(event.keysym.scancode, InputState());
        }
        
        this->keys[event.keysym.scancode].update(event.state);
    }
    
    
    void Input::handleWindowEvent(SDL_WindowEvent event) {
        this->end = event.event == SDL_WINDOWEVENT_CLOSE;
    }
    
    
    void Input::reset() {
        for (auto entry: this->buttons) {
            entry.second.reset();
        }
        for (auto &entry: this->keys) {
            entry.second.reset();
        }
        this->mouseMotion = { 0, 0 };
        this->wheelMotion = { 0, 0 };
    }
    
    
    void Input::handleInput(const SDL_Event &event) {
        switch (event.type) {
            case SDL_MOUSEMOTION:
                this->handleMouseMotion(event.motion);
                break;
            
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                this->handleMouseButton(event.button);
                break;
            
            case SDL_MOUSEWHEEL:
                this->handleMouseWheel(event.wheel);
                break;
            
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                this->handleKeyboard(event.key);
                break;
            
            case SDL_WINDOWEVENT:
                this->handleWindowEvent(event.window);
                break;
            
            case SDL_QUIT:
                this->end = true;
                break;
                
            default:
                break;
        }
    }
    
    
    GLboolean Input::isPressedButton(uint8_t button) const {
        return this->buttons.count(button) && this->buttons.at(button).pressed;
    }
    
    
    GLboolean Input::isPressedKey(SDL_Scancode key) const {
        return this->keys.count(key) && this->keys.at(key).pressed;
    }
    
    
    GLboolean Input::isReleasedButton(uint8_t button) const {
        return this->buttons.count(button) && this->buttons.at(button).released;
    }
    
    
    GLboolean Input::isReleasedKey(SDL_Scancode key) const {
        return this->keys.count(key) && this->keys.at(key).released;
    }
    
    
    GLboolean Input::isHeldButton(uint8_t button) const {
        return this->buttons.count(button) && this->buttons.at(button).held;
    }
    
    
    GLboolean Input::isHeldKey(SDL_Scancode key) const {
        return this->keys.count(key) && this->keys.at(key).held;
    }
    
    
    InputState Input::getInputStateButton(uint8_t button) const {
        if (!this->buttons.count(button)) {
            return InputState();
        }
        
        return this->buttons.at(button);
    }
    
    
    InputState Input::getInputStateKey(SDL_Scancode key) const {
        if (!this->keys.count(key)) {
            return InputState();
        }
        
        return this->keys.at(key);
    }
    
    
    GLboolean Input::ended() const {
        return this->end;
    }
    
    
    glm::vec2 Input::getRelativeMotion() const {
        return this->mouseMotion;
    }
    
    
    glm::vec2 Input::getWheelMotion() const {
        return this->wheelMotion;
    }
}

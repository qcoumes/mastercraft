#ifndef OPENGL_INPUTMANAGER_HPP
#define OPENGL_INPUTMANAGER_HPP

#include <SDL2/SDL_events.h>

#include <misc/INonCopyable.hpp>
#include <glm/vec2.hpp>
#include <unordered_map>
#include <GL/glew.h>


namespace tool {
    
    /**
     * Struct used to store the state of an key / mouse button.
     *
     * A button/key 'pressed' boolean is true if it has been pressed while hovering the element. Setting 'pressed' set
     * 'pressedPoint'. It stay true only for one loop.
     *
     * A button/key 'held' boolean is true if it has been pressed while hovering the element. It stay true as long as the
     * button/key is held.
     *
     * A button/key 'released' boolean is true if it has been released while hovering the element, whether its 'pressed'
     * boolean is true or not. It stay true only for one loop.
     */
    struct InputState {
        GLboolean released = false; /**< Whether the key/button has been released this loop. */
        GLboolean pressed = false;  /**< Whether the key/button has been pressed this loop. */
        GLboolean held = false;     /**< Whether the key/button is currently held. */
        
        InputState() = default;
        
        friend std::ostream &operator<<(std::ostream &os, const InputState &inputState);
        
        /**
         * Reset this InputState by setting 'released', 'pressed' and 'clicked' to false.
         */
        void reset();
        
        /**
         * Update the Input State according to the Event's state.
         *
         * @param state State of the SDL Event.
         */
        void update(uint8_t state);
    };
    
    
    
    class Input : public misc::INonCopyable {
        
        private:
            std::unordered_map<SDL_Scancode, InputState> keys; /** InputState of every keyboard's keys. */
            std::unordered_map<uint8_t, InputState> buttons;   /** InputState of every mouse's buttons. */
            glm::vec2 mouseMotion = { 0, 0 }; /** Relative motion of the mouse. */
            glm::vec2 wheelMotion = { 0, 0 }; /** Relative motion of the wheel. */
            GLboolean end = false; /** Whether SDL_QUIT has occured. */
            
            
            void handleMouseMotion(const SDL_MouseMotionEvent &event);
            
            void handleMouseButton(const SDL_MouseButtonEvent &event);
            
            void handleMouseWheel(const SDL_MouseWheelEvent &event);
            
            void handleKeyboard(const SDL_KeyboardEvent &event);
            
            void handleWindowEvent(SDL_WindowEvent event);
        
        public:
            
            Input() = default;
            
            void reset();
            
            void handleInput(const SDL_Event &event);
            
            [[nodiscard]] GLboolean isPressedButton(uint8_t button) const;
            
            [[nodiscard]] GLboolean isPressedKey(SDL_Scancode key) const;
            
            [[nodiscard]] GLboolean isReleasedButton(uint8_t button) const;
            
            [[nodiscard]] GLboolean isReleasedKey(SDL_Scancode key) const;
            
            [[nodiscard]] GLboolean isHeldButton(uint8_t button) const;
            
            [[nodiscard]] GLboolean isHeldKey(SDL_Scancode key) const;
            
            [[nodiscard]] InputState getInputStateButton(uint8_t button) const;
            
            [[nodiscard]] InputState getInputStateKey(SDL_Scancode key) const;
            
            [[nodiscard]] GLboolean ended() const;
            
            [[nodiscard]] glm::vec2 getRelativeMotion() const;
            
            [[nodiscard]] glm::vec2 getWheelMotion() const;
    };
}

#endif // OPENGL_INPUTMANAGER_HPP

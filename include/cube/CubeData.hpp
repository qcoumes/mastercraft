#ifndef OPENGL_CUBETYPE_HPP
#define OPENGL_CUBETYPE_HPP

#include <GL/glew.h>


namespace cube {
    
    /** Tell if the bloc use alpha channel (eg. water). */
    static constexpr GLushort ALPHA = 1u << 11u;
    /** Tell if the block is animated (eg. water). */
    static constexpr GLushort ANIMATED = 1u << 12u;
    /** Tell if the block has a top overlay (eg. snow-topped dirt). */
    static constexpr GLushort TOP_OVERLAY = 1u << 13u;
    /**
     * Tell if the block is not a floor, meaning the bottom face must be
     * rendered (eg. leaves).
     */
    static constexpr GLushort NOT_FLOOR = 1u << 14u;
    
    /**
     * Offset for the the face direction bits.
     */
    static constexpr GLubyte BIT_FACE_OFFSET = 8;
    
    /**
     * Location of the texture in the atlas.
     *
     * @param x Horizontal position in the atlas.
     * @param y Vertical position in the atlas.
     *
     * @return An short where the 4 rightmost bits give the X position and
     * the 4 following bit the Y position.
     */
    static constexpr GLushort textureLoc(GLushort x, GLushort y) {
        return static_cast<GLushort>(x | (y << 4u));
    }
    
    
    enum CubeData : GLushort {
        // Block types
        AIR = 0u | ALPHA | NOT_FLOOR, // Empty block, not present in the texture atlas.
        WATER = textureLoc(0, 0) | ALPHA | ANIMATED,
        SAND_BEACH = textureLoc(2, 0),
        ICE = textureLoc(3, 0),
        SNOW = textureLoc(4, 0),
        STONE = textureLoc(5, 0),
        STONE_SNOW = textureLoc(6, 0) | TOP_OVERLAY,
        FLOWERS = textureLoc(7, 0) | ALPHA,
        DIRT_PLAIN = textureLoc(2, 1) | TOP_OVERLAY,
        DIRT_JUNGLE = textureLoc(3, 1) | TOP_OVERLAY,
        DIRT_SNOW = textureLoc(4, 1) | TOP_OVERLAY,
        SAND_DESERT = textureLoc(5, 1),
        WOOD_PLAIN = textureLoc(2, 2),
        WOOD_JUNGLE = textureLoc(3, 2),
        WOOD_SNOW = textureLoc(4, 2),
        CACTUS = textureLoc(5, 2),
        LEAVES_PLAIN = textureLoc(2, 3) | ALPHA | NOT_FLOOR,
        LEAVES_JUNGLE = textureLoc(3, 3) | ALPHA | NOT_FLOOR,
        LEAVES_SNOW = textureLoc(4, 3) | ALPHA | NOT_FLOOR,
        
        
        // Face directions
        TOP = 0u << BIT_FACE_OFFSET,
        FACE = 1u << BIT_FACE_OFFSET,
        RIGHT = 2u << BIT_FACE_OFFSET,
        BACK = 3u << BIT_FACE_OFFSET,
        LEFT = 4u << BIT_FACE_OFFSET,
        BOTTOM = 5u << BIT_FACE_OFFSET
    };
}

#endif //OPENGL_CUBETYPE_HPP

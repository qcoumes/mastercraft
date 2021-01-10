#include <stdexcept>

#include <cube/ColumnGenerator.hpp>


namespace cube {
    
    ColumnGenerator::Column ColumnGenerator::waterColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= app::Config::GEN_WATER_LEVEL + 1; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeData::STONE;
            }
            else if (y < height) {
                column[y] = cube::CubeData::SAND_BEACH;
            }
            else {
                column[y] = cube::CubeData::WATER;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::iceColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= app::Config::GEN_WATER_LEVEL + 1; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeData::STONE;
            }
            else if (y < height) {
                column[y] = cube::CubeData::SNOW;
            }
            else if (y == app::Config::GEN_WATER_LEVEL + 1) {
                column[y] = cube::CubeData::ICE;
            }
            else {
                column[y] = cube::CubeData::WATER;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::sandBeachColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 2) {
                column[y] = cube::CubeData::STONE;
            }
            else {
                column[y] = cube::CubeData::SAND_BEACH;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::sandDesertColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 5) {
                column[y] = cube::CubeData::STONE;
            }
            else {
                column[y] = cube::CubeData::SAND_DESERT;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::snowColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeData::STONE;
            }
            else {
                column[y] = cube::CubeData::SNOW;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::stoneColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            column[y] = cube::CubeData::STONE;
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::stoneSnowColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 2) {
                column[y] = cube::CubeData::STONE;
            }
            else {
                column[y] = cube::CubeData::STONE_SNOW;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::dirtPlainColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeData::STONE;
            }
            else {
                column[y] = cube::CubeData::DIRT_PLAIN;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::dirtJungleColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeData::STONE;
            }
            else {
                column[y] = cube::CubeData::DIRT_JUNGLE;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::dirtSnowColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeData::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeData::STONE;
            }
            else {
                column[y] = cube::CubeData::DIRT_SNOW;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::generate(GLuint height, cube::CubeData type) {
        switch (type) {
            case WATER:
                return waterColumn(height);
            case ICE:
                return iceColumn(height);
            case SAND_BEACH:
                return sandBeachColumn(height);
            case SAND_DESERT:
                return sandDesertColumn(height);
            case SNOW:
                return snowColumn(height);
            case STONE:
                return stoneColumn(height);
            case STONE_SNOW:
                return stoneSnowColumn(height);
            case DIRT_PLAIN:
                return dirtPlainColumn(height);
            case DIRT_JUNGLE:
                return dirtJungleColumn(height);
            case DIRT_SNOW:
                return dirtSnowColumn(height);
            case AIR:
            case WOOD_PLAIN:
            case FLOWERS:
            case WOOD_JUNGLE:
            case WOOD_SNOW:
            case CACTUS:
            case LEAVES_PLAIN:
            case LEAVES_JUNGLE:
            case LEAVES_SNOW:
                throw std::runtime_error(
                    "Cannot generate column for biome of type '" + std::to_string(type) + "'."
                );
            default:
                throw std::runtime_error("Invalid block type.");
        }
    }
}

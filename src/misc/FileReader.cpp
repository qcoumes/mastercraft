#include <fstream>
#include <iostream>

#include <misc/FileReader.hpp>


namespace misc {
    
    std::string FileReader::read(const std::string &path) {
        std::ifstream input = std::ifstream(path.c_str());
        if (!input) {
            throw std::runtime_error(std::string("Error: Unable to load the file '" + path + "'"));
        }
        
        std::string content = std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
        input.close();
        
        return content;
    }
}

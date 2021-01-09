#ifndef OPENGL_FILEREADER_HPP
#define OPENGL_FILEREADER_HPP

#include <string>


namespace misc {
    
    class FileReader {
        
        public:
            
            FileReader() = delete;
            
            static std::string read(const std::string &path);
    };
}

#endif // OPENGL_FILEREADER_HPP

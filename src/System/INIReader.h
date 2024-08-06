//
// Created by super on 06.08.2024.
//

#ifndef ENGINE_INIREADER_H
#define ENGINE_INIREADER_H


#include <string>
#include <map>

typedef std::map<std::string, std::string> Section;

class INIReader {
    std::map<std::string, Section> file{};
public:
    const std::map<std::string, Section> &getFile() const {
        return file;
    }
    Section operator[](const std::string& s){
        return file[s];
    }

    explicit INIReader(const std::string& filename);

    constexpr explicit INIReader() noexcept = default;
};


#endif //ENGINE_INIREADER_H

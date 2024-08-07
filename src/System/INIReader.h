//
// Created by super on 06.08.2024.
//

#ifndef ENGINE_INIREADER_H
#define ENGINE_INIREADER_H


#include <string>
#include <map>

typedef std::map<std::string, std::string> Section;

class INIReader {
public:
    std::map<std::string, Section> file{};
    Section& operator[](const std::string& s){
        return file[s];
    }
    void read(const std::string&);

    void write(const std::string&);

    explicit INIReader(const std::string& filename);

    constexpr explicit INIReader() noexcept = default;
};


#endif //ENGINE_INIREADER_H

//
// Created by super on 06.08.2024.
//

#include <fstream>
#include "INIReader.h"
#include "TextUtils.h"
#include "debug.h"

INIReader::INIReader(const std::string &filename) {
    std::ifstream ifs {filename, std::ifstream::in};
    SPDLOG_INFO("opening {} file", filename);
    if (!ifs){
        SPDLOG_ERROR("!ifs");
        throw std::ios::failure{"!ifs"};
    }
    ifs.exceptions(std::ios_base::badbit);

    std::string line;
    std::string currSectionName;
    while (std::getline(ifs, line))
    {
        removeComments(line, ';');
        removeComments(line, '#');
        if (line.empty()){
            continue;
        }
        if (line[0] == '['){
            currSectionName = line.substr(1, line.size() - 2);
            file[currSectionName] = {};
        } else if (!currSectionName.empty()){
            file[currSectionName][line.substr(0, line.find('='))] = line.substr(line.find('=') + 1, line.size());
        }
    }
    ifs.close();
}

void INIReader::write(const std::string& filename) {
    std::ofstream ofs {filename};
    SPDLOG_INFO("saving to {} file", filename);
    if (!ofs){
        SPDLOG_ERROR("!ofs");
        throw std::ios::failure{"!ofs"};
    }
    ofs.exceptions(std::ios_base::badbit);
    for (auto& sec : file) {
        ofs << "[" + sec.first + "]\n";
        for (auto& pair : sec.second) {
            ofs << pair.first + "=" + pair.second << "\n";
        }
    }
}

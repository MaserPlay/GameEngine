﻿//
// Created by super on 22.06.2024.
//

#include "SystemAdapter.h"
#ifdef _WINDOWS
#include <windows.h>
#include <shellapi.h>

#endif

namespace SystemAdapter{
    void Init(){
        NFD_Init();
    }
    std::string OpenFileDialog(const FileFilter& filter, const std::string& defaultpath){
        nfdchar_t *outPath = NULL;
        const nfdu8char_t* input = NULL;
        if (defaultpath.empty())
        {
            input = NULL;
        } else {
            input = defaultpath.c_str();
        }
        nfdresult_t result = NFD_OpenDialog(&outPath, &filter[0], filter.size(), input);
        if (result == NFD_OKAY)
        {
            return std::string(outPath);
            NFD_FreePath(outPath);
        }
        return "";
    }
    std::string GetGameFolderName(std::string name){
        if (!name.empty()) {
            try {
                std::filesystem::create_directory(name);
            } catch (std::filesystem::filesystem_error e) {
                spdlog::error(e.what());
            }
            return std::filesystem::current_path().string() + "\\" + name + "\\";
        } else {
            return std::filesystem::current_path().string() + "\\";
        }
    }
    void OpenLink(std::string link)
    {
#ifdef _WINDOWS
        ShellExecute(0, 0, link.c_str(), 0, 0 , SW_SHOW );
#endif
    }
    std::string ReadAll(std::ifstream &stream){
        constexpr auto read_size = std::size_t(4096);
        stream.exceptions(std::ios_base::badbit);

        if (!stream) {
            SPDLOG_ERROR("file does not exist");
            return "";
            throw std::ios_base::failure("file does not exist");
        }

        auto out = std::string();
        auto buf = std::string(read_size, '\0');
        while (stream.read(& buf[0], read_size)) {
            out.append(buf, 0, stream.gcount());
        }
        out.append(buf, 0, stream.gcount());
        return out;
    }

    void Destroy(){
        NFD_Quit();
    }
}
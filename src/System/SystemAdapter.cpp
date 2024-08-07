//
// Created by super on 22.06.2024.
//

#include "SystemAdapter.h"
#ifdef _WINDOWS
#include <windows.h>
#include <shellapi.h>
#include "libloaderapi.h"
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
            return std::string{outPath};
            NFD_FreePath(outPath);
        }
        return "";
    }
    void OpenLink(const std::string& link)
    {
#ifdef _WINDOWS
        ShellExecute(0, 0, link.c_str(), 0, 0 , SW_SHOW );
#endif
    }
    std::string ExePath(){
#ifdef _WINDOWS
        char szPath[MAX_PATH] = {}; // тут все ясно
        GetModuleFileNameA(NULL, szPath, MAX_PATH); // получаем путь
        char *lstChr = strrchr(szPath, '\\') + 1; // указатель на последнее вхождение "\"
        *lstChr = '\0'; // заменяем на ноль (обрезаем строку)
        return szPath;
#endif
        return "";
    }
    std::string ReadAll(std::ifstream &stream){
        constexpr auto read_size = std::size_t(4096);
        stream.exceptions(std::ios_base::badbit);

        if (!stream) {
            SPDLOG_ERROR("file does not exist");
            throw std::ifstream::failure("file does not exist");
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
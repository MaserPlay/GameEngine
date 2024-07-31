//
// Created by super on 12.07.2024.
//

#include "Localization.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include "map"
#include "System/SystemAdapter.h"

nlohmann::json local {};
std::string lang = "en";
#ifdef _DEBUG
bool write = false;
#endif

namespace Localization{
    void init(const std::string& fileName){
        lang = std::setlocale(0, "");
        std::setlocale(LC_NUMERIC, "C");
        std::ifstream f(fileName);
        if (f.is_open()) {
            try{
                local = nlohmann::json::parse(f);
            } catch (const std::exception& e)
            {
                SPDLOG_WARN(e.what());
            }
        } else {
            SPDLOG_WARN("cannot open SystemAdapter::GetGameFolderName(\"Localization\") + \"lang.lang\"");
        }
    }
    std::string getTrans(std::string en){
#ifdef _DEBUG
        if (write) {
            local[en]["en"] = en;
        }
#endif
        if (local[en][lang].empty())
        {
            return en;
        } else {
            return local[en][lang];
        }
    }
    void setLang(std::string code){
        lang = code;
    }
#ifdef _DEBUG
    void genfile(const std::string& fileName){
// write prettified JSON to another file
        std::ofstream o(fileName);
        o << local;
    }
    void writefile(){
        write = true;
    }
#endif
}
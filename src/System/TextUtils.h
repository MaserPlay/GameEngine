//
// Created by super on 06.08.2024.
//

#ifndef ENGINE_TEXTUTILS_H
#define ENGINE_TEXTUTILS_H

#include <string>

inline
std::string strip(const std::string& in) {
    char final[2000];
    char* cursor = final;
    for(char cc : in) {
        if ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z') || (cc >= '0' && cc <= '9'))
        {
            *cursor = cc;
            ++cursor;
        }
    }
    *cursor = 0;
    return final;
}
inline void removeComments(std::string& s, char comment = '#'){
    if (s.find(comment) > s.size()) {
        return;
    }
    s.erase(s.find(comment));//TODO: Bugged
}
inline bool isInteger(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

#endif //ENGINE_TEXTUTILS_H

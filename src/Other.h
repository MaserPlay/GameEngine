//
// Created by super on 30.07.2024.
//

#ifndef PLATFORMER_OTHER_H
#define PLATFORMER_OTHER_H

#include "glm/glm.hpp"

enum Directions{
    Up,
    Left,
    Down,
    Right
};
#define DIRECTION_LAST 5

template<typename T=unsigned short>
using Coords = glm::vec<2, T>;
typedef glm::vec2 ExtendedCoords;
typedef glm::vec4 Color;

#endif //PLATFORMER_OTHER_H

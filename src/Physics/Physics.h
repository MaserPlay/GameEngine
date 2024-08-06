//
// Created by super on 30.07.2024.
//

#ifndef ENGINE_PHYSICS_H
#define ENGINE_PHYSICS_H
#include "Engine.h"

COORDS_TEMPLATE
bool AABB(const Quard<T>& f,const Quard<T>& s){
    auto ax2 = f.coords.x + f.width;
    auto ay2 = f.coords.y + f.height;
    auto bx2 = s.coords.x + s.width;
    auto by2 = s.coords.y + s.height;
    if ((f.coords.y < by2) && (ay2 > s.coords.y) && (f.coords.x < bx2) && (ax2 > s.coords.x))
        return true;
    return false;
}
/**
 *
 * @return Will they collide?
 */
COORDS_TEMPLATE
auto Collision = AABB<T>;
//auto ExtendedCollision = Collision<float>;

#endif //ENGINE_PHYSICS_H

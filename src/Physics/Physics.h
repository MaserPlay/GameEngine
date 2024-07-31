//
// Created by super on 30.07.2024.
//

#ifndef ENGINE_PHYSICS_H
#define ENGINE_PHYSICS_H
#include "Engine.h"

COORDS_TEMPLATE
bool AABB(const Quard<T>& f,const Quard<T>& s){
    auto ax2 = f.ld.x + f.width;
    auto ay2 = f.ld.y + f.height;
    auto bx2 = s.ld.x + s.width;
    auto by2 = s.ld.y + s.height;
    if ((f.ld.y < by2) && (ay2 > s.ld.y) && (f.ld.x < bx2) && (ax2 > s.ld.x))
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

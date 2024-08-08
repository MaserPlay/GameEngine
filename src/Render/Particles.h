//
// Created by super on 07.08.2024.
//

#ifndef ENGINE_PARTICLES_H
#define ENGINE_PARTICLES_H

#include "Engine.h"

struct CircleParticlesData{
    ExtendedCoords position {};
    float size{1};
    std::shared_ptr<Texture> texture {new Texture()};
    float lifetime {1};
    float distdifference {1};
    unsigned long count{10};
};
std::shared_ptr<MergedRender> CreateCircleParticles(const CircleParticlesData& pd);
void UseCircleParticles(std::shared_ptr<MergedRender>& r, const CircleParticlesData& pd, glm::mat4 mat);

#endif //ENGINE_PARTICLES_H

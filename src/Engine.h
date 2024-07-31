//
// Created by super on 30.07.2024.
//

#ifndef PLATFORMER_OTHER_H
#define PLATFORMER_OTHER_H

#include "glm/glm.hpp"
#include "Texture.h"
#include "ZipArchive.h"
#include "Sound.h"

enum Directions{
    Up,
    Left,
    Down,
    Right
};
#define DIRECTION_LAST 5
#define COORDS_TEMPLATE template<typename T=unsigned short>
COORDS_TEMPLATE
using Coords = glm::vec<2, T>;
typedef glm::vec2 ExtendedCoords;
typedef glm::vec4 Color;

COORDS_TEMPLATE
struct Quard{
    Quard(Coords<T> ld, T width, T height, std::shared_ptr<Texture> texture = NULL) : texture(std::move(texture)), ld(ld), width(width), height(height) {}
    Quard() = default;
    Coords<T> ld {};
    T width {}, height{};
    std::shared_ptr<Texture> texture {};
    Color color {1.,1.,1.,1.};

#define OPERATOR(t) \
    operator Quard<t>() const { \
        Quard<t> to {(Coords<t>) ld, (t) width, (t) height, texture}; \
        to.color = color; \
        return to; \
    }
    OPERATOR(float)
    OPERATOR(double)
    OPERATOR(int)
    OPERATOR(long)
    OPERATOR(long long)
    OPERATOR(unsigned int)
    OPERATOR(unsigned long)
    OPERATOR(unsigned long long)
    OPERATOR(long double)
#undef OPERATOR

    inline
    std::array<Coords<T>, 4> getVertices(){
        return {Coords<T>{ld.x + width, ld.y}, {ld.x + width, ld.y + height}, {ld.x, ld.y + height}, ld};
    }
};

class MergedRender;

typedef Quard<float> ExtendedQuard;
void initEngine();
#define START_LOOP glfwPollEvents(); \
                    glClearColor(0.f, 0.f, 0.f, 1.0f); \
                    glClear(GL_COLOR_BUFFER_BIT); \

#define END_LOOP(w) glfwSwapBuffers(w);

namespace LoadResources{
    void loadImage(ZipArchive& archive, const std::string& name, std::shared_ptr<Texture>& texture);
    void loadAudio(ZipArchive& archive, const std::string& name, std::unique_ptr<Sound>& buffer);
    void loadVertexShader(ZipArchive& archive, const std::string& name, std::unique_ptr<MergedRender>& render);
    void loadFragmentShader(ZipArchive& archive, const std::string& name, std::unique_ptr<MergedRender>& render);
}

#endif //PLATFORMER_OTHER_H

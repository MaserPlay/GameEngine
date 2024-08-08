//
// Created by super on 16.07.2024.
//

#ifndef ARCADEGAMES_MERGEDRENDER_H
#define ARCADEGAMES_MERGEDRENDER_H

#include "Render.h"
#include "glm/mat4x4.hpp"
#include "Engine.h"
namespace Shaders{
    constexpr const GLchar* const TextureFragmentShader = "#version 330 core\nin vec2 TexCoord;uniform sampler2D ourTexture;void main(){gl_FragColor = texture(ourTexture, TexCoord);}\0";
    constexpr const GLchar* const vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 position;layout (location = 1) in vec4 color;layout (location = 2) in vec2 texCoord;uniform mat4 projection;out vec2 TexCoord;out vec4 Color;void main(){gl_Position = projection * vec4(position, 1);TexCoord = texCoord;Color = color;}\0";
    constexpr const GLchar* const fragmentShaderSource = "#version 330 core\nin vec4 Color;void main(){gl_FragColor = Color;}\0";
}

class Shader final{
public:
    Shader() = default;

    virtual ~Shader();

    Shader(const GLchar *vertexShaderSource, const GLchar *fragmentShaderSource) : vertexShaderSource(
            vertexShaderSource), fragmentShaderSource(fragmentShaderSource) {}

    Shader(const Shader &p) = delete;   // удаляем конструктор
    void setVertexShader(const GLchar *shaderSource) {
        Shader::vertexShaderSource = shaderSource;
    }

    void setFragmentShader(const GLchar *shaderSource) {
        Shader::fragmentShaderSource = shaderSource;
    }
    void use();

    [[nodiscard]] GLuint getShaderProgram() const {
        return shaderProgram;
    }
    void load();
    void SetUniform(float attr, const std::string& name);
    void SetUniform(glm::vec2 attr, const std::string& name);
    void SetUniform(glm::mat4 attr, const std::string& name);
    void SetUniform(glm::vec3 attr, const std::string& name);
    void SetUniform(glm::vec4 attr, const std::string& name);
private:
    const GLchar* vertexShaderSource = Shaders::vertexShaderSource;
    const GLchar* fragmentShaderSource = Shaders::fragmentShaderSource;
    GLuint shaderProgram = 0;
};

namespace Shaders{
    std::shared_ptr<Shader> StandartShader();
    std::shared_ptr<Shader> TextureShader();
    std::shared_ptr<Shader> CreateShader();
//    std::shared_ptr<Shader> StandartShader {new Shader(Shaders::vertexShaderSource, Shaders::fragmentShaderSource)};
//    std::shared_ptr<Shader> TextureShader {new Shader(Shaders::vertexShaderSource, Shaders::TextureFragmentShader)};
}

class MergedRender final {
    //SHADER
public:
    void setInstancing(unsigned long count){
        useinstancing = true;
        instancingcount = count;
    }
    MergedRender() = default;
    MergedRender(const MergedRender &p) = delete;   // удаляем конструктор
    void load();
    void use(glm::mat4 matrix);
    void useClear();
    void useTextureShader(){shader = Shaders::TextureShader();}

    [[nodiscard]] GLuint getShaderProgram() const {
        return shader->getShaderProgram();
    }
    std::shared_ptr<Shader> shader {Shaders::StandartShader()};
    //BUFFER
public:
    enum class SpeedContent{
        STATIC,
        DYNAMIC,
        STREAM
    };

    virtual ~MergedRender();
    void setSpeed(SpeedContent speed) {
        MergedRender::speed = speed;
    }

    std::shared_ptr<ExtendedQuard> quard {new ExtendedQuard()};
    void VerticesChanged();
private:
    SpeedContent speed = SpeedContent::DYNAMIC;

    GLuint VBO{}, VAO{}, EBO{};
    std::vector<GLuint> indices;
    bool useinstancing{false};
    unsigned long instancingcount{1};
};
typedef MergedRender Render;

#endif //ARCADEGAMES_MERGEDRENDER_H
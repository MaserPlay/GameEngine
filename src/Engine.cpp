//
// Created by super on 30.07.2024.
//
#include "Engine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "MergedRender.h"

void initEngine() {
    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_ALPHA_TEST);
//    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
Shaders::TextureShader()->load();
Shaders::StandartShader()->load();
}

namespace LoadResources
{
    void loadImage(ZipArchive& archive, const std::string &name, std::shared_ptr<Texture>& texture) {
        char *content = NULL; zip_uint64_t size;
        unsigned char *image = NULL; int width, height, nrChannels;
        archive.get(name, content, size);
        if (content == NULL)
        {
            SPDLOG_WARN("{} not found", name);
        } else {
            image = stbi_load_from_memory(reinterpret_cast<const unsigned char *const>(content), size, &width, &height,
                                          &nrChannels, 0);
            if (nrChannels == 4)
            {
                texture = std::make_unique<Texture>(image, width, height);
                texture->Load();
            } else if (nrChannels == 3)
            {
                texture = std::make_unique<Texture>(image, width, height, Texture::Colors::RGB);
                texture->Load();
            } else {
                SPDLOG_WARN("{} have {} channels. What is undefined", name, nrChannels);
            }
            stbi_image_free(content);
            SPDLOG_INFO("{} loaded", name);
        }
    }

    void loadAudio(ZipArchive& archive, const std::string& name, std::unique_ptr<Sound>& buffer){
        char *content = NULL; zip_uint64_t size;
        archive.get(name, content, size);
        if (content == NULL) {
            SPDLOG_WARN("{} not found", name);
        } else {
            buffer = std::make_unique<Sound>(content, size);
            buffer->Load();
            SPDLOG_INFO("{} loaded", name);
        }
    }

    void loadFragmentShader(ZipArchive &archive, const std::string &name, std::unique_ptr<MergedRender>& render) {
        if (render == NULL)
        {
            SPDLOG_ERROR("render == NULL");
            return;
        }
        char *content = NULL; zip_uint64_t size;
        archive.get(name, content, size);
        if (content == NULL)
        {
            SPDLOG_WARN("{} not found", name);
        } else {
            content[size] = '\0';
            render->shader->setFragmentShader(content);
            SPDLOG_INFO("{} loaded", name);
        }
    }
    void loadVertexShader(ZipArchive &archive, const std::string &name, std::unique_ptr<MergedRender>& render) {
        if (render == NULL)
        {
            SPDLOG_ERROR("render == NULL");
            return;
        }
        char *content = NULL; zip_uint64_t size;
        archive.get(name, content, size);
        if (content == NULL)
        {
            SPDLOG_WARN("{} not found", name);
        } else {
            content[size] = '\0';
            render->shader->setVertexShader(content);
            SPDLOG_INFO("{} loaded", name);
        }
    }
}
//
// Created by super on 30.07.2024.
//

#include <iostream>
#include "Render.h"
#include "Audio.h"
#include "LOG.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "debug.h"
#include "Font.h"
#include "SystemAdapter.h"

void window_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void error_callback(int code, const char *description);

GLuint WIDTH = 800, HEIGHT = 600;
GLFWwindow* window;
ALCdevice *Aldevice;
ALCcontext *AlContext;
int main(){
    try
    {
        // create a color multi-threaded logger
        auto console = spdlog::stdout_color_mt("console");
        auto err_logger = spdlog::stderr_color_mt("stderr");
        spdlog::set_level(spdlog::level::trace);
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }

    spdlog::set_pattern("%s:%# [%^%l%$] %v");
    SPDLOG_INFO("Starting...");
    SPDLOG_INFO("{} by {} v.{}", APPNAME, APPAUTHOR, APPVERSION);
    // Init GLFW
    glfwInit();

    // Create a GLFWwindow object that we can use for GLFW's functions
    window = glfwCreateWindow(WIDTH, HEIGHT, APPNAME, nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        ErrorAbort("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    //ERROR
    glfwSetErrorCallback(error_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
    {
        ErrorAbort("Failed to initialize GLEW");
    }

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowSizeLimits(window, 400,400, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetKeyCallback(window, key_callback);

    //Init
    SystemAdapter::Init();
    //INIT FONT LIB
    Font::InitLib();
    // Init OpenAl
    Aldevice = alcOpenDevice(nullptr);
    AlContext = alcCreateContext(Aldevice, nullptr);
    alcMakeContextCurrent(AlContext);
    initEngine();
    while (!glfwWindowShouldClose(window)) {
        START_LOOP



        END_LOOP(window)
    }
    SPDLOG_DEBUG("Closing...");
    //OPENAL
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(AlContext);
    alcCloseDevice(Aldevice);
    // O
    SystemAdapter::Destroy();
    glfwTerminate();
    return 0;
}
void error_callback(int code, const char *description)
{
    SPDLOG_ERROR("GLFW error was occuruped" + std::string(description) + " with code" + std::to_string(code));
}
void window_size_callback(GLFWwindow* window, int width, int height){
    WIDTH = width; HEIGHT = height;
//    currentContext->size_callback(width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
        }
    }
}
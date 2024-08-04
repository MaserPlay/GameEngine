// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// OPENAL
#include <alc.h>

//LOG
#include "LOG.h"
#ifdef _DEBUG
#include "spdlog/sinks/stdout_color_sinks.h"
#else
#include "spdlog/sinks/basic_file_sink.h"
#endif
//STB
#include <stb_image.h>
//MEMORY
#include "memory"
//OTHER
#include "System/SystemAdapter.h"
//ARCHIVE
#include "System/ZipArchive.h"
//OTHER
#include "debug.h"
#include "System/Localization.h"
#include "Font.h"
#include "MergedRender.h"

#ifdef _WINDOWS
#include <windows.h>
#endif
#include <memory>
std::unique_ptr<Font::Font> baseFont = nullptr;
const std::unique_ptr<Font::Font>& getFont(){return baseFont;}
#ifndef DO_WINMAIN
bool skipintro = false;
bool genlangfile = false;
#endif
//GAME
std::unique_ptr<MergedRender> r {new MergedRender()};


void window_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void error_callback(int code, const char *description);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// Window dimensions
GLuint WIDTH = 800, HEIGHT = 600;
const GLuint& getWidth()
{
    return WIDTH;
}
const GLuint& getHeight()
{
    return HEIGHT;
}
GLFWwindow* window;
ALCdevice *Aldevice;
ALCcontext *AlContext;
const GLFWwindow* const getwindow()
{
    return window;
}
void Init()
{
    SPDLOG_DEBUG("loading Assets.zip && font.ttf");
    auto zzz = "res.zip";
    if (std::filesystem::is_regular_file(zzz)) {
        ZipArchive zip{zzz};
        char *content = NULL; zip_uint64_t size = 0;
        zip.get("font.ttf", content, size);
        if (content != NULL) {
            baseFont = std::make_unique<Font::Font>(reinterpret_cast<const FT_Byte *>(content), size);
            SPDLOG_INFO("font.ttf loaded && applied");
        } else {
            SPDLOG_WARN("font.ttf not found");
        }
    } else {
        SPDLOG_WARN("res.zip not found");
    }
}
void Domain(){
    //Create Log
#ifdef _DEBUG
// NO abort() message in windows
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
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
#else
    auto logger = spdlog::basic_logger_mt("logger", "logs/latest.log");
    spdlog::set_level(spdlog::level::info); // Set global log level to debug3
    spdlog::set_default_logger(logger);
#endif
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
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    //Init
    SystemAdapter::Init();
    Localization::init("lang.lang");
#ifdef _DEBUG
    if (genlangfile) {
        Localization::writefile();
    }
#endif
    //INIT FONT LIB
    Font::InitLib();
    // Init OpenAl
    Aldevice = alcOpenDevice(nullptr);
    AlContext = alcCreateContext(Aldevice, nullptr);
    alcMakeContextCurrent(AlContext);
    Init();
#if defined(_DEBUG) && !defined(DO_WINMAIN)
    if (skipintro) {
//        std::thread t{Init};
//        if (t.joinable()) {
//            t.join();
//        }
        SPDLOG_DEBUG("intro_skipped");
    } else {
    }
#else
//    setContext(new IntroContext());
#endif
    initEngine();
    // INIT GAME

    r->setSpeed(MergedRender::SpeedContent::STATIC);
    r->quard.reset(new ExtendedQuard({-.5,-.5},1,1));

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        START_LOOP

        r->use({1});

        END_LOOP(window)
    }
    SPDLOG_DEBUG("Closing...");
#ifdef _DEBUG
    if (genlangfile) {
        Localization::genfile("lang.lang");
    }
#endif
    //OPENAL
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(AlContext);
    alcCloseDevice(Aldevice);
    // O
    SystemAdapter::Destroy();
    glfwTerminate();
}
// The MAIN function, from here we start the application and run the game loop
#ifdef DO_WINMAIN
int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
#else
int main(int argc, char** argv)
#endif
{
#ifndef DO_WINMAIN
    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "skipintro")
        {
            skipintro = true;
        } else if (std::string(argv[i]) == "genlangfile") {
            genlangfile = true;
        }
    }
    delete argv;
#endif
    try {
        Domain();
    } catch (const std::exception& e)
    {
        SPDLOG_CRITICAL("GLOBAL CRITICAL ERROR!!!! {}", e.what());
        return -1;
    } catch (...)
    {
        SPDLOG_CRITICAL("GLOBAL CRITICAL ERROR!!!!");
        return -2;
    }
    return 0;
}
void window_size_callback(GLFWwindow* window, int width, int height){
    WIDTH = width; HEIGHT = height;
    glViewport(0,0,width,height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}
void error_callback(int code, const char *description)
{
    SPDLOG_ERROR("GLFW error was occurred {} with code {}", description, code);
}
bool fullscreen = false;
void SwitchFullscreen(){
    if (fullscreen)
    {
        glfwSetWindowMonitor(window, NULL, 100, 100, 800, 600, NULL);
        fullscreen = false;
    } else {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
        fullscreen = true;
    }
}
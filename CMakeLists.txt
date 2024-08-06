cmake_minimum_required(VERSION 3.28)
project(Engine VERSION 0.2 LANGUAGES CXX)

if (ENGINE_BUILD_TESTS)
enable_testing()
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/arc/${CMAKE_BUILD_TYPE})

add_compile_definitions(ENGINEVERSION="${CMAKE_PROJECT_VERSION}")
add_compile_definitions(ENGINEVERSIONCODE=0)
add_compile_definitions(ENGINENAME="${PROJECT_NAME}")
add_compile_definitions(ENGINEAUTHOR="MaserPlay")

list(APPEND cpps src/*.cpp src/System/*.cpp src/Physics/*.cpp src/Audio/*.cpp src/Render/*.cpp src/Render/UI/*.cpp)
list(APPEND dirs src/ src/System/ src/Physics/ src/Audio/ src/Render/ src/Render/UI/)

add_subdirectory(third_party/Boxer)
add_subdirectory(third_party/nativefiledialog-extended)

if (WIN32)
    target_compile_definitions(Boxer PRIVATE UNICODE)
endif (WIN32)

file(GLOB cpps ${cpps})

add_library(${PROJECT_NAME} STATIC ${cpps})

target_include_directories(${PROJECT_NAME} PUBLIC ${dirs})

include_directories(${dirs})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(libzip CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


# LIBRARIES

target_link_libraries(${PROJECT_NAME} PUBLIC Freetype::Freetype nlohmann_json::nlohmann_json glfw glm::glm GLEW::GLEW Boxer spdlog::spdlog nfd OpenAL::OpenAL ${Stb_INCLUDE_DIR} libzip::zip)

option(ENGINE_BUILD_EXAMPLES "Build example programs" OFF)
if (ENGINE_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

option(ENGINE_BUILD_TESTS "Build GTests" OFF)
if (ENGINE_BUILD_TESTS)
    add_subdirectory(GTest)
endif()
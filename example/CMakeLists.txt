cmake_minimum_required(VERSION 3.28)
project(ExampleApp)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

add_compile_definitions(APPVERSION="0.1b")
add_compile_definitions(APPVERSIONCODE=0)
add_compile_definitions(APPNAME="${PROJECT_NAME}")
add_compile_definitions(APPAUTHOR="MaserPlay")

list(APPEND cpps src/*.cpp #[[ico.rc]])
list(APPEND hs src/)

include_directories(${PROJECT_NAME} ${hs})
file(GLOB cpps ${cpps})

#add_subdirectory(GameEngine)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release" AND WIN32)
    add_compile_definitions(DO_WINMAIN)
    add_executable(${PROJECT_NAME} WIN32 ${cpps})
else ()
    add_executable(${PROJECT_NAME} ${cpps})
endif()

target_link_libraries(${PROJECT_NAME} Engine)

#copy assets
add_custom_target(assets)
add_dependencies(${PROJECT_NAME} assets)
add_custom_command(TARGET assets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/example/Assets/test_wav.wav ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_wav.wav
        COMMENT "Copy Assets")
# 'Google_test' is the subproject name

project(Google_tests)
# 'Google_Tests_run' is the target name
# 'test1.cpp test2.cpp' are source files with tests
find_package(GTest CONFIG REQUIRED)

list(APPEND cpps *.cpp)
list(APPEND hs /)

include_directories(${PROJECT_NAME} ${hs})
file(GLOB cpps ${cpps})


add_executable(${PROJECT_NAME} ${cpps})

target_link_libraries(${PROJECT_NAME} Engine GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

#copy assets
add_custom_target(assets)
add_dependencies(${PROJECT_NAME} assets)
add_custom_command(TARGET assets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/GTest/Assets/test_wav.wav ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_wav.wav
        COMMENT "Copy Assets")
cmake_minimum_required(VERSION 3.20)
project(CandyTicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(CandyTicTacToe src/main.cpp)
target_link_libraries(CandyTicTacToe PRIVATE SFML::Graphics SFML::Window SFML::System)

# Copy assets beside the executable when the project is built.
add_custom_command(TARGET CandyTicTacToe POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:CandyTicTacToe>/assets"
)

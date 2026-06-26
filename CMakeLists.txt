cmake_minimum_required(VERSION 3.15)
project(RaylibChess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)

file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(chess ${SOURCES})
target_include_directories(chess PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(chess PRIVATE raylib)

# Copy the assets next to the executable so the sprites load at runtime.
add_custom_command(TARGET chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:chess>/assets")

cmake_minimum_required(VERSION 3.29.0)
project(gdpadtool VERSION 0.1.0 LANGUAGES C CXX)

include(./vcpkg/scripts/buildsystems/vcpkg.cmake)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)


file(GLOB_RECURSE PROJ_SRC src/*.cpp)


add_executable(gdpadtool ${PROJ_SRC})


target_include_directories(gdpadtool PUBLIC 
    include 
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(gdpadtool PRIVATE
    imgui::imgui 
    glfw
    fmt
    ${OPENGL_LIBRARIES}
)

add_custom_command(TARGET gdpadtool 
    PRE_LINK
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/"
        "$<TARGET_FILE_DIR:gdpadtool>/resources")
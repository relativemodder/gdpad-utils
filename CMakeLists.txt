cmake_minimum_required(VERSION 3.29.0)
project(gdpadtool VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

set(VCPKG_TARGET_TRIPLET x64-linux-release)

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE static)
set(VCPKG_LIBRARY_LINKAGE static)

set(VCPKG_CMAKE_SYSTEM_NAME Linux)
set(VCPKG_BUILD_TYPE release)

set(USE_STATIC_LIBS ON)


include(./vcpkg/scripts/buildsystems/vcpkg.cmake)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)


file(GLOB_RECURSE PROJ_SRC src/*.cpp)


add_executable(gdpadtool ${PROJ_SRC})


target_link_options(gdpadtool PRIVATE -static-libgcc -static-libstdc++)


target_include_directories(gdpadtool PUBLIC 
    include
    include/fontawesome
    include/stb
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(gdpadtool
    gcc
    stdc++
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
cmake_minimum_required(VERSION 3.29.0)
project(gdpadtool VERSION 0.1.0 LANGUAGES C CXX)

if (LINUX)
    set(VCPKG_TARGET_TRIPLET x64-linux-release)

    set(VCPKG_TARGET_ARCHITECTURE x64)
    set(VCPKG_CRT_LINKAGE static)
    set(VCPKG_LIBRARY_LINKAGE static)

    set(VCPKG_CMAKE_SYSTEM_NAME Linux)
    set(VCPKG_BUILD_TYPE release)

    set(USE_STATIC_LIBS ON)

elseif (WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows-static)
    set(USE_STATIC_LIBS ON)
    set(VCPKG_BUILD_TYPE release)
    set(VCPKG_LIBRARY_LINKAGE static)

else ()
    message(FATAL_ERROR "Unsupported platform")
endif()


include(./vcpkg/scripts/buildsystems/vcpkg.cmake)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE PROJ_SRC src/*.cpp)

add_executable(gdpadtool ${PROJ_SRC})

target_link_options(gdpadtool PRIVATE -static-libgcc -static-libstdc++)

if (NOT "$ENV{FLATPAK_PATH}" STREQUAL "")
    set(FLATPAK_PATH $ENV{FLATPAK_PATH})
endif()

if (NOT "${FLATPAK_PATH}" STREQUAL "") 
    message(STATUS "Using Flatpak this time by path ${FLATPAK_PATH}")
    add_compile_definitions(FOR_FLATPAK)
    add_compile_definitions(RESOURCES_PREROOT="/app/share/")
    target_link_directories(gdpadtool PRIVATE "${FLATPAK_PATH}/runtime/org.freedesktop.Sdk/x86_64/23.08/active/files/lib")
    # set(PLATFORM_GL_LIBS 
    #     "libOpenGL.so"
    #     "libGLX.so"
    # ) # holy fucking shit
    # set(PLATFORM_GL_LIBS OpenGL::GL) # embed
else()
    add_compile_definitions(RESOURCES_PREROOT="./")
endif()


set(PLATFORM_GL_LIBS OpenGL::GL) # embed


target_include_directories(gdpadtool PUBLIC 
    include
    include/fontawesome
    include/stb
)

target_link_libraries(gdpadtool
    imgui::imgui 
    glfw
    fmt::fmt
    ${PLATFORM_GL_LIBS}
)

add_custom_command(TARGET gdpadtool 
    PRE_LINK
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/"
        "$<TARGET_FILE_DIR:gdpadtool>/resources")
cmake_minimum_required(VERSION 3.5.0)
project(DDPERExternal VERSION 0.1.0 LANGUAGES C CXX)

# set(ImGui_FIND_QUIETLY FALSE)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
# find_package(ImGui REQUIRED)
# message(STATUS "IMGUI_INCLUDE_DIR: ${IMGUI_INCLUDE_DIR}")

include_directories(include)

# Add imgui sources
file(GLOB IMGUI_SOURCES include/imgui/*.cpp)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(imgui STATIC ${IMGUI_SOURCES})

add_executable(DDPERExternal main.cpp ${SOURCES})

target_link_libraries(DDPERExternal imgui d3d9 d3d11 d3dcompiler dwmapi)

target_compile_features(DDPERExternal PRIVATE cxx_std_20)
target_include_directories(DDPERExternal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif ()

add_custom_command(
    TARGET DDPERExternal POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/libwinpthread-1.dll"
        $<TARGET_FILE_DIR:DDPERExternal>
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
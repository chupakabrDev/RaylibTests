cmake_minimum_required(VERSION 4.2)
project(RaylibTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- raylib ---
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 6.0
            GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# --- raylib-cpp ---
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    set(RAYLIB_CPP_VERSION v6.0.0)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# --- nlohmann_json ---
find_package(nlohmann_json QUIET)
if (NOT nlohmann_json_FOUND)
    set(NLOHMANN_JSON_VERSION v3.12.0)
    include(FetchContent)
    FetchContent_Declare(
            nlohmann_json
            GIT_REPOSITORY https://github.com/nlohmann/json.git
            GIT_TAG ${NLOHMANN_JSON_VERSION}
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

# --- raygui ---
set(RAYGUI_DIR "${CMAKE_BINARY_DIR}/raygui")
set(RAYGUI_HEADER "${RAYGUI_DIR}/raygui.h")

if (NOT EXISTS "${RAYGUI_HEADER}")
    file(MAKE_DIRECTORY "${RAYGUI_DIR}")

    file(DOWNLOAD
            "https://raw.githubusercontent.com/raysan5/raygui/5.0/src/raygui.h"
            "${RAYGUI_HEADER}"
            SHOW_PROGRESS
    )
endif()

add_library(raygui INTERFACE)

target_include_directories(raygui INTERFACE
        "${RAYGUI_DIR}"
)


# --- main target ---
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/InputMap.cpp
        src/helper/TextHelper.cpp
        src/helper/TextureHelper.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/">
        $<$<CONFIG:Release>:ASSETS_PATH="./assets/">
)

target_include_directories(${PROJECT_NAME} PRIVATE
        src
        include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        raylib_cpp
        nlohmann_json
        raygui
)

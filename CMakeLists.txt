cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(capstone_node_editor)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#add_subdirectory(src/vendor/imgui)
set(LIB_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src/external/) # Lib folder
## Imgui lib
set(imgui_Includes "${LIB_FOLDER}/imgui/"
        ${LIB_FOLDER}/imgui/backends)

        add_library(imgui STATIC
        ${LIB_FOLDER}/imgui/imconfig.h
        ${LIB_FOLDER}/imgui/imgui.cpp
        ${LIB_FOLDER}/imgui/imgui.h
        ${LIB_FOLDER}/imgui/imgui_demo.cpp
        ${LIB_FOLDER}/imgui/imgui_draw.cpp
        ${LIB_FOLDER}/imgui/backends/imgui_impl_opengl3.cpp
        ${LIB_FOLDER}/imgui/backends/imgui_impl_opengl3.h
        ${LIB_FOLDER}/imgui/backends/imgui_impl_opengl3_loader.h
        ${LIB_FOLDER}/imgui/backends/imgui_impl_sdl.cpp
        ${LIB_FOLDER}/imgui/backends/imgui_impl_sdl.h
        ${LIB_FOLDER}/imgui/imgui_internal.h
        ${LIB_FOLDER}/imgui/imgui_tables.cpp
        ${LIB_FOLDER}/imgui/imgui_widgets.cpp
        ${LIB_FOLDER}/imgui/imstb_rectpack.h
        ${LIB_FOLDER}/imgui/imstb_textedit.h
        ${LIB_FOLDER}/imgui/imstb_truetype.h
        )


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${INCLUDE_FOLDER} ${imgui_Includes} src)

add_executable(capstone_node_editor src/Capstone_node_editor.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(capstone_node_editor ${SDL2_LIBRARIES})
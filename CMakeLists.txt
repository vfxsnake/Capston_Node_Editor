cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17 )

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(capstone_node_editor)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

## Lib folder
set(LIB_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src/external)
## Imgui lib
set(imgui_Includes ${LIB_FOLDER}/imgui
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
        ${LIB_FOLDER}/imgui/backends/imgui_impl_glfw.cpp
        ${LIB_FOLDER}/imgui/backends/imgui_impl_glfw.h
        ${LIB_FOLDER}/imgui/imgui_internal.h
        ${LIB_FOLDER}/imgui/imgui_tables.cpp
        ${LIB_FOLDER}/imgui/imgui_widgets.cpp
        ${LIB_FOLDER}/imgui/imstb_rectpack.h
        ${LIB_FOLDER}/imgui/imstb_textedit.h
        ${LIB_FOLDER}/imgui/imstb_truetype.h
        )

set(imnodes_Includes ${LIB_FOLDER}/im_nodes)
add_library(imnodes STATIC 
        ${LIB_FOLDER}/im_nodes/imnodes_internal.h
        ${LIB_FOLDER}/im_nodes/imnodes.cpp
        ${LIB_FOLDER}/im_nodes/imnodes.h
        )



set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
include_directories(${imgui_Includes})
include_directories(${imnodes_Includes})


add_executable(capstone_node_editor
               src/node_editor.cpp
               src/glfw_app_base.hpp
               src/app.cpp
               src/capstone_node_editor.cpp
              )

add_executable(test_nodes
               src/plug.hpp
               src/abstract_node.cpp
               src/nodes.cpp
               src/test/test_nodes.cpp  
              )

target_link_libraries(capstone_node_editor GL glfw imgui imnodes dl)
target_link_libraries(test_nodes)
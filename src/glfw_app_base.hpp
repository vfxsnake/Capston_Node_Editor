// this file is an hpp because of the nature of the template
// if it is separated into .h and cpp the base function 
// fail as they should expect to use the Derived cast.
#pragma once
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


/*
    template class.
    is the base of a generic GLFW3 application, 
    it provides the basic functionality "App Loop":
    * Constructor to acquire all necessary resources.
    * Destructor to clear all resource during closing.
    * Run to call the app loop.
    * StartUp function to initialize the sdl context.
    * Update function to perform the logic.
    * Render function to render the frame content.
    This class can be used as a base of other sdl classes.
*/
template<typename Derived> 
class GLFWAppBase
{
public:
    GLFWAppBase(int screen_width=1280, int screen_height=720)
    {
        std::cout << "std_app_base constructor"<< std::endl;
        
        // Setup window
        if (!glfwInit())
        {
            std::cerr << "GLFW_Error: " << "GLFW could not initialize." << "\n";
        }
        
        // boiler plate code to declare the OpeGl version context
        // Decide GL+GLSL versions
    #if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
        // GL 3.0 + GLSL 130
        glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

        // Create window with graphics context
        window = glfwCreateWindow(screen_width, screen_height, //window width and height
                                  "Dear ImGui GLFW+OpenGL3 example", // window title
                                   NULL, // glfw monitor 
                                   NULL  // window to share resources. 
                                 );
        if (window == NULL)
        {
            std::cerr << "GLFW_Error: " << "GLFW could not initialize window." << "\n";
        }


    }


    ~GLFWAppBase()
    {
        std::cout << "std_app_base destructor"<< std::endl;
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }


    void StartUp()
    {
        std::cout << "std_app_base startUp"<< std::endl;
        
        // start up window
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }


    void Update()
    {
        std::cout << "std_app_base Update"<< std::endl;
        static_cast<Derived*>(this)->Update();
        
    }


    void Render()
    {
        std::cout << "std_app_base Render"<< std::endl;
        
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }


    void Run()
    {
        std::cout << "std_app_base Run"<< std::endl;


        StartUp();

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Update();
            
            Render();
        }
    }

private:
    GLFWwindow* window;
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
    const char* glsl_version;
};
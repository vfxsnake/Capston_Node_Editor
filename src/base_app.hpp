#pragma once

#include <iostream>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif


// class template
template<typename Derived> 
class BaseApp
{
public:
    BaseApp()
    {
        std::cout << "constructor"<< std::endl;
    }

    ~BaseApp()
    {
        std::cout << "destructor"<< std::endl;
    }

    void Run()
    {
        StartUp();
        while(true)
        {
            Update();
        }
    }

private:
    void StartUp()
    {
        static_cast<Derived*>(this)->StartUp();
    }
    void Update()
    {
        static_cast<Derived*>(this)->Update();
    }

};
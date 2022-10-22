// this file is an hpp because of the nature of the template
// if it is separated into .h and cpp the base function 
// fail as they should expect to use the Derived cast.
#pragma once

#include <iostream>
#include <SDL.h>


/*
    Sdl template class.
    is the generator for a sdl application, it provides the
    basic functionality:
    * Constructor to acquire all necessary resources.
    * Destructor to clear all resource during closing.
    * Run to call the app loop.
    * StartUp function to initialize the sdl context.
    * Update function to perform the logic.
    * Render function to render the frame content.
    This class can be used as a base of other sdl classes.
*/
template<typename Derived> 
class SdlAppBase
{
public:
    SdlAppBase(int screen_width=1280, int screen_height=720)
    {
        std::cout << "std_app_base constructor"<< std::endl;
        // Setup SDL
        // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
        // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to the latest version of SDL is recommended!)
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            printf("Error: %s\n", SDL_GetError());
            std::cerr << "SDL could not initialize.\n";
            std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        }
          // Create Window
        sdl_window = SDL_CreateWindow("Node Editor", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, screen_width,
                                        screen_height, SDL_WINDOW_SHOWN);

        if (nullptr == sdl_window) {
            std::cerr << "Window could not be created.\n";
            std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
        }

        // Create renderer
        // sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
        // if (nullptr == sdl_renderer) {
        //     std::cerr << "Renderer could not be created.\n";
        //     std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        // }
    }


    ~SdlAppBase()
    {
        std::cout << "std_app_base destructor"<< std::endl;
        SDL_DestroyWindow(sdl_window);
        SDL_DestroyRenderer(sdl_renderer);
        SDL_Quit();
    }


    void Run()
    {
        std::cout << "std_app_base Run"<< std::endl;
        StartUp();
        bool quit_application = false;
        while (!quit_application)
        {
            SDL_Event e;
            while(SDL_PollEvent(&e) > 0)
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    quit_application = true;
                    break;
                }
            }
            
            Update();
        }
    }


    void StartUp()
    {
        std::cout << "std_app_base startUp"<< std::endl;
        static_cast<Derived*>(this)->StartUp();
    }


    void Update()
    {
        std::cout << "std_app_base Update"<< std::endl;
        static_cast<Derived*>(this)->Update();
    }


    void Render()
    {
        std::cout << "std_app_base Render"<< std::endl;
    }

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
};
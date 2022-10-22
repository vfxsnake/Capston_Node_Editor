#pragma once

#include "sdl_app_base.hpp"

class App : public SdlAppBase<App>
{
public:
    void StartUp();
    void Update();
};
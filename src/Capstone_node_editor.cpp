#include <iostream>
#include <memory>

// project includes
#include "base_app.hpp"

class App : public BaseApp<App>
{
public:
    void StartUp()
    {
        std::cout << "derived startup" << std::endl;
    }
    
    void Update()
    {
        std::cout << "derived update" << std::endl;
    }
};


int main(int, char**) 
{
    std::cout << "main function start!" << "\n";
    App* app;
    app->Run();
    std::cout << "app shut down" <<std::endl;
    return 0;
}
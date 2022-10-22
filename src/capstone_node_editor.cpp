#include <iostream>
#include <memory>
#include "app.h"

int main(int, char**) 
{
    std::cout << "main function start!" << "\n";
    
    App app;
    app.Run();
    std::cout << "app shut down" <<std::endl;
    return 0;
}
#include <iostream>
#include "../plug.hpp"
#include <vector>

int main()
{
    std::cout << "testing plug base"<< std::endl;
    // plug float
    Plug<float> plug_float;
    float temp_float = 5.23;
    plug_float.SetValue(&temp_float);
    plug_float.PrintValue();

    // plug int
    Plug<int> plug_int;
    int temp_int = 60;
    plug_int.SetValue(&temp_int);
    plug_int.PrintValue();

}
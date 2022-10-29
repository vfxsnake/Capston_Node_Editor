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
    plug_float.SetId(0);

    // plug int
    Plug<int> plug_int;
    int temp_int = 60;
    plug_int.SetValue(&temp_int);
    plug_int.PrintValue();
    plug_int.SetId(1);

    std::vector<AbstractPlug*> plug_list;
    plug_list.emplace_back(&plug_float);
    plug_list.emplace_back(&plug_int);

    for(auto x : plug_list)
    {
        std::cout << "iterating list" << std::endl;
        x->PrintValue();
    }
}


#include <iostream>
#include "../plug.hpp"
#include "../nodes.h"
#include <vector>

int main()
{
    std::cout << "-----------------testing plug base-------------"<< std::endl;
    
    // PlugOut float
    PlugOut<float> plug_out_float;
    float temp_float = 5.23;
    plug_out_float.SetReferenceToValue(&temp_float);
    plug_out_float.PrintValue();

    // PlugIn float
    PlugIn<float> plug_in_float;
    plug_in_float.SetSourcePlug(&plug_out_float);


    // test Nodes
    std::cout << "-----------------testing nodes--------------------------";
    FloatNode float_node_test1{};

    float_node_test1.SetDefaultValue(4.321);
    std::cout << "node is dirty ? " << float_node_test1.IsDirty() << std::endl;
    std::cout << "plugsIns ? " << float_node_test1.GetPlugIns().size() << std::endl;
    std::cout << "plugsIns ? " << float_node_test1.GetPlugOuts().size() << std::endl;
    std::cout << "compute ? " << float_node_test1.Compute() << std::endl;
    
    PlugIn<float> node_in_plug;
    node_in_plug.SetSourcePlug(float_node_test1.GetOutPlug());
    node_in_plug.PrintValue();
}


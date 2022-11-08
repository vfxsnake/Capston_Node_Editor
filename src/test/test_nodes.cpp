#include <iostream>
#include "../plug.hpp"
#include "../nodes.h"
#include <vector>

int main()
{
    std::cout << "-----------------testing plug base-------------"<< std::endl;
    // int globalId = 0;
    // // PlugOut float
    // PlugOut<float> plug_out_float(globalId);
    // float temp_float = 5.23;
    // plug_out_float.SetReferenceToValue(&temp_float);
    // plug_out_float.PrintValue();

    // // PlugIn float
    // PlugIn<float> plug_in_float(globalId);
    // plug_in_float.SetSourcePlug(&plug_out_float);


    // // test Nodes
    // std::cout << "-----------------testing nodes--------------------------";
    // FloatNode float_node_test1(globalId);

    // float_node_test1.SetDefaultValue(4.321);
    // std::cout << "node is dirty ? " << float_node_test1.IsDirty() << std::endl;
    // std::cout << "plugsIns ? " << float_node_test1.GetPlugIns().size() << std::endl;
    // std::cout << "plugsIns ? " << float_node_test1.GetPlugOuts().size() << std::endl;
    // std::cout << "compute ? " << float_node_test1.Compute() << std::endl;
    
    // PlugIn<float> node_in_plug(globalId);
    // node_in_plug.SetSourcePlug(float_node_test1.GetOutPlug());
    // node_in_plug.PrintValue();

    // std::cout << "-----------------testing addition--------------------------";
    // FloatNode n1(globalId);
    // n1.SetDefaultValue(-10);
    // n1.Compute();
    
    // FloatNode n2(globalId);
    // n2.SetDefaultValue(-20);
    // n2.Compute();


    // FloatAdditionNode add_1(globalId);
    // add_1.SetDefaultValue_0(7.5);
    // add_1.SetDefaultValue_1(3.5);
    // add_1.Compute();
    // std::cout << "add default values in add node" << std::endl;
    // add_1.GetOutPlug()->PrintValue();
    // if (add_1.GetOutPlug()->GetReferenceValue() == 11)
    //     std::cout << "add default values passed" << std::endl;
    // else
    //     std::cout << "add default values fail" << std::endl;
    // std::cout << "..................................." << std::endl;

    // add_1.GetPlugIn_0()->SetSourcePlug(n1.GetOutPlug());
    // add_1.GetPlugIn_1()->SetSourcePlug(n2.GetOutPlug());
    // add_1.Compute();
    // std::cout << "add two float nodes" << std::endl; 
    // add_1.GetOutPlug()->PrintValue();
    // if (add_1.GetOutPlug()->GetReferenceValue()== -30)
    //     std::cout << "add 2 nodes together passed" << std::endl;
    // else
    //     std::cout << "add 2 nodes together fail" << std::endl;
    // std::cout << "..................................." << std::endl;

    // // disconnecting plug 0 
    // n1.SetDefaultValue(-5.5f);
    // n1.Compute();
    // add_1.GetPlugIn_0()->SetSourcePlug(n1.GetOutPlug());
    // add_1.GetPlugIn_1()->SetSourcePlug(nullptr);
    // add_1.SetDefaultValue_1(1.0f);
    // add_1.Compute();
    // std::cout << "remove plug 1 source value to use default" << std::endl; 
    // add_1.GetOutPlug()->PrintValue();
    // if (add_1.GetOutPlug()->GetReferenceValue()== -4.5)
    //     std::cout << "add plug_0 + defaut_1 nodes together passed" << std::endl;
    // else
    //     std::cout << "add 2 nodes together fail" << std::endl;
    // std::cout << "..................................." << std::endl;
    // n2.SetDefaultValue(-33);
    // n2.Compute();
    // add_1.GetPlugIn_0()->SetSourcePlug(nullptr);
    // add_1.SetDefaultValue_0(2);
    // add_1.GetPlugIn_1()->SetSourcePlug(n2.GetOutPlug());
    // add_1.Compute();
    // std::cout << "remove plug 1 source value to use default" << std::endl; 
    // add_1.GetOutPlug()->PrintValue();
    
    // if (add_1.GetOutPlug()->GetReferenceValue()== -31)
    //     std::cout << "add plug_0 + defaut_1 nodes together passed" << std::endl;
    // else
    //     std::cout << "add 2 nodes together fail" << std::endl;
    // std::cout << "..................................." << std::endl;

    // std::cout << "------------------- evaluation node ---------------------------" << std::endl;
    // FloatNode node1(globalId), node2(globalId), node3(globalId), node4(globalId);
    // FloatAdditionNode add1(globalId), add2(globalId), add3(globalId);
    // EvaluationNode evaluate1(globalId);

    // // set default values to float nodes
    // node1.SetDefaultValue(1.0f);
    // node2.SetDefaultValue(2.0f);
    // node3.SetDefaultValue(3.0f);
    // node4.SetDefaultValue(4.0f);

    // add1.GetPlugIn_0()->SetSourcePlug(node1.GetOutPlug());
    // add1.GetPlugIn_1()->SetSourcePlug(node2.GetOutPlug());
    // add2.GetPlugIn_0()->SetSourcePlug(node3.GetOutPlug());
    // add2.GetPlugIn_1()->SetSourcePlug(node4.GetOutPlug());
    // add3.GetPlugIn_0()->SetSourcePlug(add1.GetOutPlug());
    // add3.GetPlugIn_1()->SetSourcePlug(add2.GetOutPlug());
    
    // evaluate1.GetPlugIn_0()->SetSourcePlug(add3.GetOutPlug());
    // evaluate1.Compute();

    // std::cout << "no changes compute: ====================================" << std::endl;
    // evaluate1.Compute();

    // std::cout << "node changed : ------------------------------------" << std::endl;
    // node4.SetDefaultValue(3.5);
    // std::cout << "node1 is dirty?" << node1.IsDirty() << std::endl;
    // evaluate1.Compute();
    // std::cout << "----------------------" << std::endl;
    
    // std::cout <<"global id : " << globalId << std::endl;
}


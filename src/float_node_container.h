#include <memory>
#include <vector>
#include "abstract_node_container.h"

// forward declaration
class FloatNode;

template<typename>
class PlugIn;

template<typename>
class PlugOut;

class FloatNodeContainer : public AbstractNodeContainer
{
public:
    FloatNodeContainer(int &global_id);
    ~FloatNodeContainer();
    
    virtual void DrawNode() const override;
    virtual std::vector<int> GetInputsId() const override;
    virtual std::vector<int> GetOutputsId() const override;

    virtual std::vector<PlugIn<float>*> GetPlugIns() const;
    virtual std::vector<PlugOut<float>*> GetPlugOuts() const;

private:
     std::unique_ptr<FloatNode> _logic;
};
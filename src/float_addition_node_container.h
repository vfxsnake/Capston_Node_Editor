#include <memory>
#include "abstract_node_container.h"

// forward declaration
class FloatAdditionNode;

template<typename>
class PlugIn;

template<typename>
class PlugOut;

class FloatAdditionNodeContainer : public AbstractNodeContainer
{
public:
    FloatAdditionNodeContainer(int &global_id);
    ~FloatAdditionNodeContainer();
    virtual void DrawNode() const override;
    std::vector<PlugIn<float>*> GetPlugIns() const;
    std::vector<PlugOut<float>*> GetPlugOuts() const;

private:
     std::unique_ptr<FloatAdditionNode> _logic;
     
};
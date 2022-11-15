#include <memory>
#include "abstract_node_container.h"

// forward declaration
class FloatAdditionNode;

class FloatAdditionNodeContainer : public AbstractNodeContainer
{
public:
    FloatAdditionNodeContainer(int &global_id);
    ~FloatAdditionNodeContainer();
    virtual void DrawNode() const override;

private:
     std::unique_ptr<FloatAdditionNode> _logic;
     
};
#include <memory>
#include "abstract_node_container.h"

// forward declaration
class FloatNode;

class FloatNodeContainer : public AbstractNodeContainer
{
public:
    FloatNodeContainer(int &global_id);
    ~FloatNodeContainer();
    virtual void DrawNode() const override;

private:
     std::unique_ptr<FloatNode> _logic;
     float* _value;
};
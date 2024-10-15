#pragma once

#include "../AbstractValueNode.cpp"

class AbstractConstValueNode : public AbstractValueNode
{
   public:
    AbstractConstValueNode() : AbstractValueNode() {}

    virtual bool RequiresAXRegister() override { return false; }
};
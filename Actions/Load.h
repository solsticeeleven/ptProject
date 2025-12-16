#pragma once
#include "Action.h"
#include <string>

class Load : public Action
{
public:
    Load(ApplicationManager* pApp);

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};

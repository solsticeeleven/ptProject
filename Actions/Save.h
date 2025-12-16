#pragma once
#include "Action.h"

class Save : public Action
{
public:
    Save(ApplicationManager* pApp);

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};


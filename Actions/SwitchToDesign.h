#pragma once

#include "Action.h" /

class SwitchToDesign : public Action
{
public:
    
    SwitchToDesign(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

    virtual void Redo();

    virtual ~SwitchToDesign();
};
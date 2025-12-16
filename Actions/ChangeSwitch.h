#pragma once
#include "Action.h"

class ApplicationManager;
class Switch;

class ChangeSwitch : public Action
{
public:
    ChangeSwitch(ApplicationManager* pApp);

    virtual void Execute();

    virtual ~ChangeSwitch() {}
};
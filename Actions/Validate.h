#pragma once
#include "Action.h"
class ApplicationManager;

class Validate : public Action
{
public:
    Validate(ApplicationManager* pApp);

    virtual void Execute();
};
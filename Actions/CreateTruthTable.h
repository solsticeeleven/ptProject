#pragma once
#include "Action.h"
class ApplicationManager;

class CreateTruthTable : public Action
{
public:
    CreateTruthTable(ApplicationManager* pApp);

    virtual void Execute();
};
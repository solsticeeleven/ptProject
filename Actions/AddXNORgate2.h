#ifndef _ADD_XNOR_GATE_H
#define _ADD_XNOR_GATE_H

#include "Action.h"
#include "..\Components\XNOR2.h"
#include "..\ApplicationManager.h"

class AddXNORgate2 : public Action
{
private:
    int Cx, Cy;
public:
    AddXNORgate2(ApplicationManager* pApp);
    virtual ~AddXNORgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
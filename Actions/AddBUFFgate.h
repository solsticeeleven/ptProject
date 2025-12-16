#ifndef _ADD_BUFF_GATE_H
#define _ADD_BUFF_GATE_H

#include "Action.h"
#include "..\Components\BUFF.h"
#include "..\ApplicationManager.h"

class AddBUFFgate : public Action
{
private:
    int Cx, Cy;
public:
    AddBUFFgate(ApplicationManager* pApp);
    virtual ~AddBUFFgate(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
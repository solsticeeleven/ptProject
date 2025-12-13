#ifndef _LOAD_ACTION_H
#define _LOAD_ACTION_H

#include "Action.h"
#include <string>

class ApplicationManager;

class Load : public Action
{
private:
    std::string filename;
public:
    Load(ApplicationManager* pApp);
    virtual ~Load();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif // _LOAD_ACTION_H
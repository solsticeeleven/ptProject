#ifndef _SELECT_H
#define _SELECT_H

#include <vector>

#include "Action.h"
#include "../Components/Component.h"
#include "..\ApplicationManager.h"

class Select : public Action
{
private:
	int x, y;
public:
	Select(ApplicationManager* pApp);
	virtual ~Select();

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
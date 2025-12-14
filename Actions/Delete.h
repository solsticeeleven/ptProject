#pragma once

#ifndef _DELETE_H_
#define _DELETE_H_

#include "Action.h"
#include "../Components/Component.h"
#include "../ApplicationManager.h"

class Delete : public Action
{
private:
	Component* selectedComponent;
public:
	Delete(ApplicationManager* pApp);
	virtual ~Delete();

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
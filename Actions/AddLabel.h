#pragma once

#ifndef _ADD_LABEL_H
#define _ADD_LABEL_H

#include <vector>

#include "Action.h"
#include "../Components/Component.h"
#include "..\ApplicationManager.h"

class AddLabel : public Action {
private:
	vector<Component*> selectedComponent;
	string labelText;
public:
	AddLabel(ApplicationManager* pApp);
	virtual ~AddLabel();

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
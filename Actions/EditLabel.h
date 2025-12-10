#ifndef _EDIT_LABEL_H
#define _EDIT_LABEL_H

#include "Action.h"
#include "../Components/Component.h"
#include "..\ApplicationManager.h"

class EditLabel : public Action {
private:
	Component* selectedComponent;
	string labelText;
public:
	EditLabel(ApplicationManager* pApp);
	virtual ~EditLabel();

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
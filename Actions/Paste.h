#ifndef _PASTE_H_
#define _PASTE_H_

#include <vector>
#include "..\Components\Component.h"
#include "Action.h"
#include "../ApplicationManager.h"

class Paste : public Action {
private:
	Component* clipboardComponent;
	int x, y;
public:
	Paste(ApplicationManager* pApp);
	~Paste();

	void ReadActionParameters();

	void Execute();

	void Undo();
	void Redo();
};

#endif

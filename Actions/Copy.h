#pragma once
#ifndef _COPY_H_
#define _COPY_H_

#include <vector>
#include "..\Components\Component.h"
#include "Action.h"
#include "../ApplicationManager.h"

class Copy : public Action {
private:
	vector<Component*> selectedComponents;
public:
	Copy(ApplicationManager* pApp);
	~Copy();

	void ReadActionParameters();

	void Execute();

	void Undo();
	void Redo();
};

#endif
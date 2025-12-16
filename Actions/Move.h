#pragma once

#ifndef _MOVE_H_
#define _MOVE_H_

#include <vector>

#include "..\Components\Component.h"
#include "Action.h"
#include "../ApplicationManager.h"

class Move : public Action {
private:
	vector<Component*> selectedComponent;
	vector<GraphicsInfo> oldGfxInfo;
	vector<GraphicsInfo> newGfxInfo;
public:
	Move(ApplicationManager* pApp);
	~Move();

	void ReadActionParameters();

	void Execute();

	void Undo();
	void Redo();
};

#endif
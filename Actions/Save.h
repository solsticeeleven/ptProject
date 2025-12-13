#ifndef _SAVE_ACTION_H
#define _SAVE_ACTION_H

#include "Action.h"
#include <string>

class Save : public Action
{
private:
	std::string filename;
public:
	Save(ApplicationManager* pApp);
	virtual ~Save();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif
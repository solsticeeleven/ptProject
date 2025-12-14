#ifndef _SAVE_ACTION_H
#define _SAVE_ACTION_H

#include "Action.h"
#include <string>


#include <fstream>
#include <vector>
#include <unordered_map>

#include "..\Components\Connection.h"
#include "..\Components\AND2.h"
#include "..\Components\AND3.h"
#include "..\Components\OR2.h"
#include "..\Components\NOR2.h"
#include "..\Components\NOR3.h"
#include "..\Components\XOR2.h"
#include "..\Components\XOR3.h"
#include "..\Components\XNOR2.h"
#include "..\Components\NAND2.h"
#include "..\Components\BUFF.h"
#include "..\Components\INV.h"

class ApplicationManager;

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

#endif // _SAVE_ACTION_H
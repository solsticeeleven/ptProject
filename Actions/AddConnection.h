#pragma once
#include <vector>
#include "Action.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

class AddConnection : public Action
{
private: 
	int x1, y1, x2, y2;
	Connection* pConn;
	vector <Component*> comp;
public:
	AddConnection(ApplicationManager *pApp);
	virtual ~AddConnection(void);
	void ReadActionParameters() override;
	
	void Execute () override;

	void Undo() override;
	void Redo() override;
};


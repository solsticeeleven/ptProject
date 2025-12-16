#pragma once

#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <iostream>
#include <vector>

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include "Components\Connection.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddBUFFgate.h"
#include "Actions\AddINVgate.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddXNORgate2.h"

#include "Actions\Save.h"        
#include "Actions\Load.h"       
#include "Actions\Select.h"
#include "Actions\AddLabel.h"
#include "Actions\EditLabel.h"
#include "Actions\Delete.h"	
#include "Actions\Move.h"
#include "Actions\Copy.h"
#include "Actions\Paste.h"


//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	vector<Component*> selectedComponents; //vector of selected components
	Component* clipboardComponent; //pointer to the copied/cut component

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface

public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);
	void RemoveComponent(Component* pComp);

	vector<Component*> GetSelectedComponents() const;
	vector<Component*> AddSelectedComponent(Component* pComp);

	void RemoveSelectedComponent(Component* pComp);
	void ClearSelectedComponents();

	Component* GetClipboardComponent() const;
	void SetClipboardComponent(Component* pComp);

	int GetComponentCount(); //get the number of components
	Component* GetComponent(int n) const;

	// delete all components (connections first, then others) and reset selection
	void ClearAllComponents(); 

	//destructor
	~ApplicationManager();
};

#endif
#pragma once

#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <iostream>

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
#include "Actions\Save.h"        // added Save action
#include "Actions\Load.h"        // added Load action
#include "Actions\Select.h"
#include "Actions\AddLabel.h"
#include "Actions\EditLabel.h"


//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Component* selectedComponent; //pointer to the selected component

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

	Component* GetSelectedComponent() const;
		Component* SetSelectedComponent(Component* pComp);

	int GetComponentCount(); //get the number of components
	Component* GetComponent(int n) const;

	// delete all components (connections first, then others) and reset selection
	void ClearAllComponents(); 

	//destructor
	~ApplicationManager();
};

#endif
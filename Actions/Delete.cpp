#include "Delete.h"
#include "../ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp) : Action(pApp)
{
}

Delete::~Delete()
{
}

void Delete::ReadActionParameters()
{
	selectedComponent = pManager->GetSelectedComponents();
}

void Delete::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	if (selectedComponent.empty()) {
		pOut->PrintMsg("No component selected to delete.");
		return;
	}

	for (Component* comp : selectedComponent) {
		pManager->RemoveComponent(comp);
	}

	pManager->ClearSelectedComponents();
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}
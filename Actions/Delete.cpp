#include "Delete.h"
#include "../ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp) : Action(pApp)
{
	selectedComponent = nullptr;
}

Delete::~Delete()
{
}

void Delete::ReadActionParameters()
{
	selectedComponent = pManager->GetSelectedComponent();
}

void Delete::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	if (selectedComponent == nullptr) {
		pOut->PrintMsg("No component selected. Invalid delete.");
		return;
	}
	pManager->RemoveComponent(selectedComponent);
	pManager->SetSelectedComponent(nullptr);
	pOut->PrintMsg("Component deleted successfully.");
}

void Delete::Undo()
{
	pManager->AddComponent(selectedComponent);
	pManager->UpdateInterface();
}

void Delete::Redo()
{
	pManager->RemoveComponent(selectedComponent);
	pManager->UpdateInterface();
}
#include "Copy.h"

Copy::Copy(ApplicationManager* pApp) : Action(pApp)
{
}

Copy::~Copy()
{
}

void Copy::ReadActionParameters()
{
	selectedComponents = pManager->GetSelectedComponents();
}

void Copy::Execute()
{
	ReadActionParameters();

	if (selectedComponents.empty()) {
		pManager->GetOutput()->PrintMsg("No component selected to copy.");
		return;
	} else if (selectedComponents.size() > 1) {
		pManager->GetOutput()->PrintMsg("Multiple components selected. Only one component can be copied at a time.");
		return;
	}

	pManager->SetClipboardComponent(selectedComponents[0]);

	pManager->GetOutput()->PrintMsg("Component(s) copied to clipboard.");
}

void Copy::Undo()
{
}

void Copy::Redo()
{
}
#include "Select.h"

#include <iostream>

Select::Select(ApplicationManager* pApp) : Action(pApp)
{
}

Select::~Select()
{
}

void Select::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pIn->GetCurrentPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Select::Execute() {
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	Component* selectedComp = nullptr;
	for (int i = 0; i < pManager->GetComponentCount(); i++) {
		Component* comp = pManager->GetComponent(i);
		GraphicsInfo gfx = comp->GetGraphicsInfo();
		if (x >= gfx.x1 && x <= gfx.x2 && y >= gfx.y1 && y <= gfx.y2) {
			selectedComp = comp;
			cout << "found the component" << endl;
			break;
		}
	}

	if (selectedComp == nullptr) {
		pManager->ClearSelectedComponents();
		pOut->PrintMsg("No Component Selected");
		return;
	}

	vector<Component*> selectedComps = pManager->GetSelectedComponents();
	for (Component* comp : selectedComps) {
		if (comp == selectedComp) {
			comp->setSelected(false);
			pManager->RemoveSelectedComponent(selectedComp);
			cout << "Size: " << selectedComps.size() << endl;
			cout << "deselected the component" << endl;
			pOut->PrintMsg("Component Deselected");
			return;
		}
	}
	selectedComp->setSelected(true);
	pManager->AddSelectedComponent(selectedComp);
	if (selectedComp->getLabel().empty()) {
		pOut->PrintMsg("Component Selected Label: N/A" );
		return;
	}
	pOut->PrintMsg("Component Selected Label: " + selectedComp->getLabel());
}

void Select::Undo()
{
}

void Select::Redo()
{
}
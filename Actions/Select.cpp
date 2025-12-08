#include "Select.h"

Select::Select(ApplicationManager* pApp) : Action(pApp)
{
	selectedComponent = nullptr;
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

	selectedComponent = nullptr;
	for (int i = 0; i < pManager->GetComponentCount(); i++) {
		Component* currentComp = pManager->GetComponent(i);
		GraphicsInfo gfxInfo = currentComp->GetGraphicsInfo();
		if (x >= gfxInfo.x1 && x <= gfxInfo.x2 && y >= gfxInfo.y1 && y <= gfxInfo.y2) {
			selectedComponent = currentComp;
		} else {
			currentComp->setSelected(false);
		}
	}
	if (selectedComponent) {
		pManager->SetSelectedComponent(selectedComponent);
		selectedComponent->setSelected(true);
		pOut->PrintMsg("Component selected");
		return;
	}
	pManager->SetSelectedComponent(nullptr);
	pOut->PrintMsg("No component selected");
}

void Select::Undo()
{
}

void Select::Redo()
{
}
#include "Select.h"

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

	pManager->SetSelectedComponent(nullptr);
	for (int i = 0; i < pManager->GetComponentCount(); i++) {
		Component* currentComp = pManager->GetComponent(i);
		GraphicsInfo gfxInfo = currentComp->GetGraphicsInfo();
		if (x >= gfxInfo.x1 && x <= gfxInfo.x2 && y >= gfxInfo.y1 && y <= gfxInfo.y2) {
			pManager->SetSelectedComponent(currentComp);
		} else {
			currentComp->setSelected(false);
		}
	}
	if (pManager->GetSelectedComponent()) {
		pManager->GetSelectedComponent()->setSelected(true);

		if (pManager->GetSelectedComponent()->getLabel().empty()) {
			pOut->PrintMsg("Component selected with no label");
			return;
		}
		pOut->PrintMsg(pManager->GetSelectedComponent()->getLabel());
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
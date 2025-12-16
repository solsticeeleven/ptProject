#include "Move.h"

Move::Move(ApplicationManager* pApp) : Action(pApp)
{
}

Move::~Move()
{
}

void Move::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	selectedComponent = pManager->GetSelectedComponents();

	for (Component* comp : selectedComponent) {
		oldGfxInfo.push_back(comp->GetGraphicsInfo());
	}
}

void Move::Execute()
{
	int index = 0;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	
	if (selectedComponent.empty()) {
		pOut->PrintMsg("No component selected to move.");
		return;
	}

	for (Component* comp : selectedComponent) {
		pOut->PrintMsg("Click on the new location to move the component.");

		int x, y;
		pIn->GetPointClicked(x, y);

		while (y < UI.ToolBarHeight || y > UI.height - UI.StatusBarHeight || x < 0 || x > UI.width)
		{
			pOut->PrintMsg("Invalid Location! Click to move the component within the drawing area");
			pIn->GetPointClicked(x, y);
		}
		int width = oldGfxInfo.at(index).x2 - oldGfxInfo.at(index).x1;
		int height = oldGfxInfo.at(index).y2 - oldGfxInfo.at(index).y1;

		GraphicsInfo temp;
		temp.x1 = x - width / 2;
		temp.y1 = y - height / 2;
		temp.x2 = temp.x1 + width;
		temp.y2 = temp.y1 + height;

		for (int i = 0; i < pManager->GetComponentCount(); i++) {
			Component* compCheck = pManager->GetComponent(i);
			if (compCheck == comp) continue;
			GraphicsInfo gfxInfo = compCheck->GetGraphicsInfo();
			if (!(temp.x2 < gfxInfo.x1 || temp.x1 > gfxInfo.x2 || temp.y2 < gfxInfo.y1 || temp.y1 > gfxInfo.y2)) {
				pOut->PrintMsg("Error: Cannot move component to an existing component's location");
				return;
			}
		}

		pOut->ClearComponentArea((oldGfxInfo.at(index)));
		comp->UpdateGraphicsInfo(temp);
		pManager->UpdateInterface();
		newGfxInfo.push_back(temp);
		index++;
	}

	pOut->PrintMsg("Components moved successfully.");
}

void Move::Undo()
{
	Output* pOut = pManager->GetOutput();
	int index = 0;
	for (Component* comp : selectedComponent) {
		comp->UpdateGraphicsInfo(oldGfxInfo.at(index));
		pOut->ClearComponentArea((newGfxInfo.at(index)));
		index++;
	}
	pManager->UpdateInterface();
}

void Move::Redo() {
	Output* pOut = pManager->GetOutput();
	int index = 0;
	for (Component* comp : selectedComponent) {
		comp->UpdateGraphicsInfo(newGfxInfo.at(index));
		pOut->ClearComponentArea((oldGfxInfo.at(index)));
		index++;
	}
	pManager->UpdateInterface();
}
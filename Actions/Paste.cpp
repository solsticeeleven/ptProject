#include "Paste.h"

Paste::Paste(ApplicationManager* pApp) : Action(pApp)
{
}

Paste::~Paste()
{
}

void Paste::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	clipboardComponent = pManager->GetClipboardComponent();

	if (clipboardComponent == nullptr) {
		pOut->PrintMsg("Clipboard is empty");
		return;
	}

	pOut->PrintMsg("Click on the location to paste the component.");
	pIn->GetPointClicked(x, y);
	while (y < UI.ToolBarHeight || y > UI.height - UI.StatusBarHeight || x < 0 || x > UI.width)
	{
		pOut->PrintMsg("Invalid Location! Click to paste the component within the drawing area");
		pIn->GetPointClicked(x, y);
	}

	for (int i = 0; i < pManager->GetComponentCount(); i++) {
		Component* compCheck = pManager->GetComponent(i);
		GraphicsInfo gfxInfo = compCheck->GetGraphicsInfo();

		int width = clipboardComponent->GetGraphicsInfo().x2 - clipboardComponent->GetGraphicsInfo().x1;
		int height = clipboardComponent->GetGraphicsInfo().y2 - clipboardComponent->GetGraphicsInfo().y1;

		GraphicsInfo temp;
		temp.x1 = x - width / 2;
		temp.y1 = y - height / 2;
		temp.x2 = temp.x1 + width;
		temp.y2 = temp.y1 + height;

		if (!(temp.x2 < gfxInfo.x1 || temp.x1 > gfxInfo.x2 || temp.y2 < gfxInfo.y1 || temp.y1 > gfxInfo.y2)) {
			pOut->PrintMsg("Error: Cannot paste component to an existing component's location");
			return;
		}
	}
}

void Paste::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();

	if (clipboardComponent == nullptr)
		return;

	GraphicsInfo newGfxInfo;
	int width = clipboardComponent->GetGraphicsInfo().x2 - clipboardComponent->GetGraphicsInfo().x1;
	int height = clipboardComponent->GetGraphicsInfo().y2 - clipboardComponent->GetGraphicsInfo().y1;
	newGfxInfo.x1 = x - width / 2;
	newGfxInfo.y1 = y - height / 2;
	newGfxInfo.x2 = newGfxInfo.x1 + width;
	newGfxInfo.y2 = newGfxInfo.y1 + height;

	Component* newComponent = nullptr;
	if (dynamic_cast<AND2*>(clipboardComponent)) {
		newComponent = new AND2(newGfxInfo, AND2_FANOUT);
	}
	else if (dynamic_cast<OR2*>(clipboardComponent)) {
		newComponent = new OR2(newGfxInfo, OR2_FANOUT);
	}
	else if (dynamic_cast<NOR2*>(clipboardComponent)) {
		newComponent = new NOR2(newGfxInfo, NOR2_FANOUT);
	}
	else if (dynamic_cast<NAND2*>(clipboardComponent)) {
		newComponent = new NAND2(newGfxInfo, NAND2_FANOUT);
	} 
	else if (dynamic_cast<XOR2*>(clipboardComponent)) {
		newComponent = new XOR2(newGfxInfo, XOR2_FANOUT);
	}
	else if (dynamic_cast<XNOR2*>(clipboardComponent)) {
		newComponent = new XNOR2(newGfxInfo, XNOR2_FANOUT);
	}
	else if (dynamic_cast<INV*>(clipboardComponent)) {
		newComponent = new INV(newGfxInfo, INV_FANOUT);
	}
	else if (dynamic_cast<BUFF*>(clipboardComponent)) {
		newComponent = new BUFF(newGfxInfo, BUFF_FANOUT);
	}
	else if (dynamic_cast<AND3*>(clipboardComponent)) {
		newComponent = new AND3(newGfxInfo, AND3_FANOUT);
	}
	else if (dynamic_cast<NOR3*>(clipboardComponent)) {
		newComponent = new NOR3(newGfxInfo, NOR3_FANOUT);
	}
	else if (dynamic_cast<XOR3*>(clipboardComponent)) {
		newComponent = new XOR3(newGfxInfo, XOR3_FANOUT);
	}

	pManager->AddComponent(newComponent);
	newComponent->setSelected(false);
	pManager->SetClipboardComponent(newComponent);
	pOut->PrintMsg("Sucessfully pasted clipboard component");
}

void Paste::Undo() {
}

void Paste::Redo() {
}
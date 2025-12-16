#include "AddANDgate3.h"

AddANDgate3::AddANDgate3(ApplicationManager *pApp) : Action(pApp)
{
}

AddANDgate3::~AddANDgate3(void)
{
}

void AddANDgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input AND Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Validate the Clicked Point
	while (Cy < UI.ToolBarHeight || Cy > UI.height - UI.StatusBarHeight || Cx < 0 || Cx > UI.width)
	{
		pOut->PrintMsg("Invalid Location! Click to add the gate within the drawing area");
		pIn->GetPointClicked(Cx, Cy);
	}

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void AddANDgate3::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND3_Width;
	int Wdth = UI.AND3_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND3 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	for (int i = 0; i < pManager->GetComponentCount(); i++) {
		GraphicsInfo gfxInfo = pManager->GetComponent(i)->GetGraphicsInfo();

		if (!(GInfo.x2 < gfxInfo.x1 || GInfo.x1 > gfxInfo.x2 || GInfo.y2 < gfxInfo.y1 || GInfo.y1 > gfxInfo.y2)) {
			Output* pOut = pManager->GetOutput();
			pOut->PrintMsg("Error: Cannot place a gate in an existing gate's location");
			return;
		}
	}

	AND3 *pA = new AND3(GInfo, AND3_FANOUT);
	pA->setSelected(false);
	pManager->AddComponent(pA);
}

void AddANDgate3::Undo()
{}

void AddANDgate3::Redo()
{}
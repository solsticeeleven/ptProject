#include "AddNORgate2.h"

AddNORgate2::AddNORgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddNORgate2::~AddNORgate2(void)
{
}

void AddNORgate2::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("2-Input NOR Gate: Click to add the gate");

	pIn->GetPointClicked(Cx, Cy);
	while (Cy < UI.ToolBarHeight || Cy > UI.height - UI.StatusBarHeight || Cx < 0 || Cx > UI.width)
	{
		pOut->PrintMsg("Invalid Location! Click to add the gate within the drawing area");
		pIn->GetPointClicked(Cx, Cy);
	}
	pOut->ClearStatusBar();
}

void AddNORgate2::Execute() {
	ReadActionParameters();

	int len = UI.NOR2_Width;
	int wdth = UI.NOR2_Height;

	GraphicsInfo GInfo;
	GInfo.x1 = Cx - len / 2;
	GInfo.x2 = Cx + len / 2;
	GInfo.y1 = Cy - wdth / 2;
	GInfo.y2 = Cy + wdth / 2;

	for (int i = 0; i < pManager->GetComponentCount(); i++) {
		GraphicsInfo gfxInfo = pManager->GetComponent(i)->GetGraphicsInfo();

		if (!(GInfo.x2 < gfxInfo.x1 || GInfo.x1 > gfxInfo.x2 || GInfo.y2 < gfxInfo.y1 || GInfo.y1 > gfxInfo.y2)) {
			Output* pOut = pManager->GetOutput();
			pOut->PrintMsg("Error: Cannot place a gate in an existing gate's location");
			return;
		}
	}

	NOR2* pA = new NOR2(GInfo, NOR2_FANOUT);
	pA->setSelected(false);
	pManager->AddComponent(pA);
}

void AddNORgate2::Undo()
{
}

void AddNORgate2::Redo()
{
}
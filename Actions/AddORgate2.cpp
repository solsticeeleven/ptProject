#pragma once

#include "AddORgate2.h"
#include "..\ApplicationManager.h"

AddORgate2::AddORgate2(ApplicationManager* pApp) : Action(pApp)
{
}

AddORgate2::~AddORgate2(void)
{
}

void AddORgate2::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("2-Input OR Gate: Click to add the gate");

	pIn->GetPointClicked(Cx, Cy);
	pOut->ClearStatusBar();
}

void AddORgate2::Execute() {
	ReadActionParameters();

	int len = UI.OR2_Width;
	int wdth = UI.OR2_Height;

	GraphicsInfo GInfo;
	GInfo.x1 = Cx - len / 2;
	GInfo.x2 = Cx + len / 2;
	GInfo.y1 = Cy - wdth / 2;
	GInfo.y2 = Cy + wdth / 2;

	OR2* pA = new OR2(GInfo, OR2_FANOUT);
	pManager->AddComponent(pA);
}

void AddORgate2::Undo()
{
}
void AddORgate2::Redo()
{
}
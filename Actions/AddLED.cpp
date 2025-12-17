#include "AddLED.h"
#include "..\ApplicationManager.h"
#include "..\Components\LED.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"

AddLED::AddLED(ApplicationManager* pApp) : Action(pApp)
{
}
void AddLED::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("LED: Click to add the LED");
	pIn->GetPointClicked(Cx, Cy);
	while (Cy < UI.ToolBarHeight || Cy > UI.LED_Height - UI.StatusBarHeight || Cx < 0 || Cx > UI.LED_Width)
	{
		pOut->PrintMsg("Invalid Location! Click to add the LED within the drawing area");
		pIn->GetPointClicked(Cx, Cy);
	}
	pOut->ClearStatusBar();




}
void AddLED::Execute() {
	ReadActionParameters();
	int len = UI.LED_Width;
	int wdth = UI.LED_Height;
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
	LED* pA = new LED(&GInfo, 1);
	pA->setSelected(false);
	pManager->AddComponent(pA);
}
void AddLED::Undo()
{
}
void AddLED::Redo()
{
}
AddLED::~AddLED()
{
}

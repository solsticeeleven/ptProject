#include "SwitchToDesign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h" 

SwitchToDesign::SwitchToDesign(ApplicationManager* pApp) : Action(pApp)
{
}

SwitchToDesign::~SwitchToDesign()
{
}

void SwitchToDesign::ReadActionParameters()
{
}

void SwitchToDesign::Execute()
{
	Output* pOut = pManager->GetOutput();

	pOut->CreateDesignToolBar();

	pOut->ClearStatusBar();

	pManager->UpdateInterface();

	pOut->PrintMsg("Switched to Design Mode.");
}

void SwitchToDesign::Undo()
{
}

void SwitchToDesign::Redo()
{
}
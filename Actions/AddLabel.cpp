#include "AddLabel.h"

AddLabel::AddLabel(ApplicationManager* pApp) : Action(pApp)
{
}

AddLabel::~AddLabel()
{
}

void AddLabel::ReadActionParameters() {
	selectedComponent = pManager->GetSelectedComponents();
}

void AddLabel::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();

	if (selectedComponent.size() != 1) {
		pOut->PrintMsg("Error: Please select exactly one component to add a label.");
		return;
	}
	else if (!selectedComponent[0]->getLabel().empty()) {
		pOut->PrintMsg("Error: The selected component already has a label.");
		return;
	} else if (selectedComponent.empty()) {
		pOut->PrintMsg("Error: No component selected.");
		return;
	}

	pOut->PrintMsg("Enter label text: ");
	labelText = pIn->GetString(pOut);

	while (labelText.empty()) {
		pOut->PrintMsg("Label cannot be empty. Please enter valid label text: ");
		labelText = pIn->GetString(pOut);
	}

	selectedComponent[0]->setLabel(labelText);
	pManager->UpdateInterface();

	pOut->PrintMsg("Successfully added the label: " + labelText);
}

void AddLabel::Undo()
{
}

void AddLabel::Redo()
{
}
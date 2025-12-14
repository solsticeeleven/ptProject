#include "EditLabel.h"

EditLabel::EditLabel(ApplicationManager* pApp) : Action(pApp)
{
}

EditLabel::~EditLabel()
{
}

void EditLabel::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	selectedComponent = pManager->GetSelectedComponents();
}

void EditLabel::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	ReadActionParameters();

	if (selectedComponent.size() != 1) {
		pOut->PrintMsg("Error: Please select exactly one component to edit its label.");
		return;
	}
	else if (selectedComponent.empty()) {
		pOut->PrintMsg("Error: No component selected.");
		return;
	}
	else if (selectedComponent[0]->getLabel().empty()) {
		pOut->PrintMsg("Error: The selected component has no label to edit.");
		return;
	}

	pOut->PrintMsg("Current label: " + labelText);

	labelText = pIn->GetString(pOut);
	while (labelText.empty()) {
		pOut->PrintMsg("Label cannot be empty. Please enter valid label text: ");
		labelText = pIn->GetString(pOut);
	}

	selectedComponent[0]->setLabel(labelText);
	pOut->PrintMsg("Label updated successfully to: " + labelText);
}

void EditLabel::Undo()
{
}

void EditLabel::Redo()
{
}
#include "EditLabel.h"

EditLabel::EditLabel(ApplicationManager* pApp) : Action(pApp)
{
	selectedComponent = nullptr;
}

EditLabel::~EditLabel()
{
}

void EditLabel::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	selectedComponent = pManager->GetSelectedComponent();
	labelText = (selectedComponent != nullptr) ? selectedComponent->getLabel() : "";
}

void EditLabel::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	ReadActionParameters();

	if (selectedComponent == nullptr) {
		pOut->PrintMsg("No component selected. Invalid label edit");
		return;
	}
	else if (selectedComponent->getLabel().empty()) {
		pOut->PrintMsg("No label has been added please add one");
		return;
	}

	pOut->PrintMsg("Current label: " + labelText);
	labelText = pIn->GetString(pOut);
	while (labelText.empty()) {
		pOut->PrintMsg("Label cannot be empty. Please enter valid label text: ");
		labelText = pIn->GetString(pOut);
	}
	selectedComponent->setLabel(labelText);
	pOut->PrintMsg("Label updated successfully to: " + labelText);
}

void EditLabel::Undo()
{
}

void EditLabel::Redo()
{
}
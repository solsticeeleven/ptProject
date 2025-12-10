#include "AddLabel.h"

AddLabel::AddLabel(ApplicationManager* pApp) : Action(pApp)
{
	selectedComponent = nullptr;
}

AddLabel::~AddLabel()
{
}

void AddLabel::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	selectedComponent = pManager->GetSelectedComponent();
}

void AddLabel::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();

	if (selectedComponent == nullptr) {
		pOut->PrintMsg("No component selected. Invalid label");
		return;
	}
	pOut->PrintMsg("Enter label text: ");
	labelText = pIn->GetString(pOut);

	while (labelText.empty()) {
		pOut->PrintMsg("Label cannot be empty. Please enter valid label text: ");
		labelText = pIn->GetString(pOut);
	}

	selectedComponent->setLabel(labelText);
	pManager->UpdateInterface();

	pOut->PrintMsg("Successfully added the label: " + labelText);
}

void AddLabel::Undo()
{
}

void AddLabel::Redo()
{
}
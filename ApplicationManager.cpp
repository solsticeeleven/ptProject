#include "ApplicationManager.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = nullptr;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	if (CompCount < MaxCompCount)
		CompList[CompCount++] = pComp;		
}
/////////////////////////////////////////////////////////////////////
void ApplicationManager::RemoveComponent(Component* pComp) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i] == pComp) {
			Component* temp = CompList[CompCount - 1];
			delete CompList[i];
			CompList[i] = temp;
			CompList[CompCount - 1] = nullptr;
			CompCount--;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////

Component* ApplicationManager::GetSelectedComponent() const
{
	return selectedComponent;
}

////////////////////////////////////////////////////////////////////

Component* ApplicationManager::SetSelectedComponent(Component* pComp)
{
	selectedComponent = pComp;
	return selectedComponent;
}

////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

int ApplicationManager::GetComponentCount()
{
	return CompCount;
}
////////////////////////////////////////////////////////////////////
Component* ApplicationManager::GetComponent(int n) const
{
	if (n < 0 || n >= CompCount)
		return NULL;
	return CompList[n];
}

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);	
			break;
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;
		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			break;
		case ADD_INV:
			pAct = new AddINVgate(this);
			break;
		case ADD_Buff:
			pAct = new AddBUFFgate(this);
			break;
		//case ADD_AND_GATE_3:
		//	pAct = new AddANDgate3(this);
		//	break;
		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(this);
			break;
		case DEL:
			pAct = new Delete(this);
			break;
		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			break;
		case ADD_Label:
			pAct = new AddLabel(this);
			break;
		case EDIT_Label:
			pAct = new EditLabel(this);
			break;
		case SELECT:
			pAct = new Select(this);
			break;
		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(OutputInterface);

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++) {
		delete CompList[i];
		CompList[i] = nullptr;
	}
	delete OutputInterface;
	delete InputInterface;
	
}
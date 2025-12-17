#include "Validate.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\Connection.h"

Validate::Validate(ApplicationManager* pApp) : Action(pApp)
{
}

Validate::~Validate()
{
}

void Validate::ReadActionParameters()
{
}

void Validate::Execute()
{
	Output* pOut = pManager->GetOutput();

	// CHECK IF CIRCUIT IS EMPTY
	if (pManager->GetComponentCount() == 0)
	{
		pOut->PrintMsg("Operation Failed: The circuit is empty. Add components first.");
		return;
	}

	pOut->PrintMsg("Validating Circuit Logic...");

	bool circuitIsValid = true;
	// Clear selection so we only highlight the problematic components
	pManager->ClearSelectedComponents();

	int count = pManager->GetComponentCount();

	// VALIDATION LOOP
	for (int i = 0; i < count; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		bool isCompValid = true;

		// CHECK GATES
		Gate* pGate = dynamic_cast<Gate*>(pComp);
		if (pGate)
		{
			// Loop through all input pins of this gate
			// NOTE: Ensure you added GetNumInputs() to Gate.h as requested
			for (int j = 0; j < pGate->GetNumInputs(); ++j)
			{
				InputPin* pGateInput = pGate->GetInputPin(j);
				bool pinConnected = false;

				// Search through components to find a Connection that goes to this pin
				for (int k = 0; k < count; ++k)
				{
					Connection* pConn = dynamic_cast<Connection*>(pManager->GetComponent(k));
					if (pConn)
					{
						// Check if this connection's destination is our current input pin
						if (pConn->getDestPin() == pGateInput)
						{
							pinConnected = true;
							break; 
						}
					}
				}

				if (!pinConnected)
				{
					isCompValid = false;
					break; 
				}
			}
		}

		// CHECK LEDs
		LED* pLED = dynamic_cast<LED*>(pComp);
		if (pLED)
		{
			// Assuming LED has GetInputPin() with no index or index 0
			// Adjust based on your LED class definition
			InputPin* pLedInput = pLED->GetInputPin(0);
			bool pinConnected = false;

			for (int k = 0; k < count; ++k)
			{
				Connection* pConn = dynamic_cast<Connection*>(pManager->GetComponent(k));
				if (pConn)
				{
					if (pConn->getDestPin() == pLedInput)
					{
						pinConnected = true;
						break;
					}
				}
			}

			if (!pinConnected)
			{
				isCompValid = false;
			}
		}

		// HIGHLIGHT INVALID COMPONENT
		if (!isCompValid)
		{
			pComp->setSelected(true); 
			circuitIsValid = false;
		}
	}

	if (circuitIsValid)
	{
		pOut->PrintMsg("Validation Successful, Circuit is ready for simulation.");
	}
	else
	{
		pOut->PrintMsg("Validation Error, Selected components have unconnected inputs.");
	}
}

void Validate::Undo() {}
void Validate::Redo() {}
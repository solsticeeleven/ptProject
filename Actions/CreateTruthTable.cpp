#include "CreateTruthTable.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include "..\Components\Connection.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <iomanip>
#include <iostream>

using namespace std;

CreateTruthTable::CreateTruthTable(ApplicationManager* pApp) : Action(pApp)
{
	m_SwitchList = NULL;
	m_LEDList = NULL;
	m_NumSwitches = 0;
	m_NumLEDs = 0;
}

CreateTruthTable::~CreateTruthTable()
{
	if (m_SwitchList) delete[] m_SwitchList;
	if (m_LEDList) delete[] m_LEDList;
}

void CreateTruthTable::ReadActionParameters()
{
}

void CreateTruthTable::Execute()
{
	Output* pOut = pManager->GetOutput();

	

	if (m_SwitchList) { delete[] m_SwitchList; m_SwitchList = NULL; }
	if (m_LEDList) { delete[] m_LEDList; m_LEDList = NULL; }
	m_NumSwitches = 0;
	m_NumLEDs = 0;

	int compCount = pManager->GetComponentCount();

	// Count Switches and LEDs
	for (int i = 0; i < compCount; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		if (!pComp) continue;

		if (dynamic_cast<Switch*>(pComp))
			m_NumSwitches++;
		else if (dynamic_cast<LED*>(pComp))
			m_NumLEDs++;
	}

	if (m_NumSwitches == 0)
	{
		pOut->PrintMsg("Error. No Switches ");
		return;
	}
	if (m_NumSwitches > 5) 
	{
		pOut->PrintMsg("Error. Too many switches. ");
		return;
	}

	
	m_SwitchList = new Component * [m_NumSwitches];
	m_LEDList = new Component * [m_NumLEDs];

	int sIdx = 0, lIdx = 0;
	for (int i = 0; i < compCount; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		if (!pComp) continue;

		if (dynamic_cast<Switch*>(pComp))
			m_SwitchList[sIdx++] = pComp;
		else if (dynamic_cast<LED*>(pComp))
			m_LEDList[lIdx++] = pComp;
	}

	
	for (int i = 0; i < m_NumSwitches - 1; i++)
	{
		for (int j = 0; j < m_NumSwitches - i - 1; j++)
		{
			if (m_SwitchList[j]->GetGraphicsInfo().x1 > m_SwitchList[j + 1]->GetGraphicsInfo().x1)
			{
				Component* temp = m_SwitchList[j];
				m_SwitchList[j] = m_SwitchList[j + 1];
				m_SwitchList[j + 1] = temp;
			}
		}
	}

	
	// Calculate Dimensions
	int numRows = 1 << m_NumSwitches; 
	int numCols = m_NumSwitches + m_NumLEDs;

	int colWidth = 50;
	int rowHeight = 25;
	int headerHeight = 30;

	int winWidth = (numCols * colWidth) + 20;
	int winHeight = (numRows * rowHeight) + headerHeight + 20;

	if (winWidth < 200) winWidth = 200; // Min

	window* pTTWind = new window(winWidth, winHeight, 200, 100);
	pTTWind->ChangeTitle("Truth Table");

	// Draw Headers
	int currentX = 10;
	int currentY = 5;

	pTTWind->SetPen(BLACK, 2);
	pTTWind->SetFont(20, BOLD, BY_NAME, "Arial");

	// Draw Switch Headers (S0, S1...)
	for (int i = 0; i < m_NumSwitches; ++i)
	{
		string label = "S" + to_string(i);
		pTTWind->DrawString(currentX, currentY, label);
		currentX += colWidth;
	}

	// Draw Separator
	pTTWind->DrawLine(currentX - 10, 0, currentX - 10, winHeight);

	// Draw LED Headers (L0, L1...)
	for (int i = 0; i < m_NumLEDs; ++i)
	{
		string label = "L" + to_string(i);
		pTTWind->DrawString(currentX, currentY, label);
		currentX += colWidth;
	}

	pTTWind->DrawLine(0, headerHeight, winWidth, headerHeight);


	currentY = headerHeight + 5;

	for (int i = 0; i < numRows; ++i)
	{
		currentX = 10;

		//  INPUT
		for (int j = 0; j < m_NumSwitches; ++j)
		{
			int bit = (i >> (m_NumSwitches - 1 - j)) & 1;

			Switch* pSwitch = (Switch*)m_SwitchList[j];

			pSwitch->GetOutputPin()->setStatus(bit ? HIGH : LOW);

			//  Input Value (0 or 1)
			pTTWind->DrawString(currentX, currentY, to_string(bit));
			currentX += colWidth;
		}

		// run the circuit logic MULTIPLE TIMES to ensure signals flow 
		// from Switches -> Gates -> Connections -> Gates -> LEDs

		int maxPropagations = compCount * 2; 
		for (int iter = 0; iter < maxPropagations; ++iter)
		{
			for (int k = 0; k < compCount; ++k)
			{
				Component* pComp = pManager->GetComponent(k);
				if (!pComp) continue;

				if (dynamic_cast<Switch*>(pComp) == NULL)
				{
					pComp->Operate();
				}
			}
		}

		//  OUTPUT
		for (int k = 0; k < m_NumLEDs; ++k)
		{
			LED* pLED = (LED*)m_LEDList[k];

			int status = LOW;
			if (pLED->GetInputPin(0))
				status = pLED->GetInputPin(0)->getStatus();

			//  Output Value (0 or 1)
			pTTWind->DrawString(currentX, currentY, to_string(status == HIGH ? 1 : 0));
			currentX += colWidth;
		}

		currentY += rowHeight;
	}

	pTTWind->WaitMouseClick(currentX, currentY);
	delete pTTWind;
}

void CreateTruthTable::Undo()
{
}

void CreateTruthTable::Redo()
{
}
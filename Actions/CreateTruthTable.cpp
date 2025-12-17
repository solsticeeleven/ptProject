#include "CreateTruthTable.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include "..\Components\Connection.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <iomanip>
#include <iostream>
#include <string>

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

	// Initialize and count components
	if (m_SwitchList) { delete[] m_SwitchList; m_SwitchList = NULL; }
	if (m_LEDList) { delete[] m_LEDList; m_LEDList = NULL; }
	m_NumSwitches = 0;
	m_NumLEDs = 0;

	int totalComps = pManager->GetComponentCount();

	for (int i = 0; i < totalComps; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		if (!pComp) continue;

		if (dynamic_cast<Switch*>(pComp))
			m_NumSwitches++;
		else if (dynamic_cast<LED*>(pComp))
			m_NumLEDs++;
	}

	// Basic validation
	if (m_NumSwitches == 0)
	{
		pOut->PrintMsg("Operation Aborted: The circuit must contain at least one Switch.");
		return;
	}

	if (m_NumSwitches > 5)
	{
		pOut->PrintMsg("Complexity Alert: Cannot generate table for >5 switches.");
		return;
	}

	// Populate lists
	m_SwitchList = new Component * [m_NumSwitches];
	m_LEDList = new Component * [m_NumLEDs];

	int swCount = 0;
	int ledCount = 0;

	for (int i = 0; i < totalComps; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		if (!pComp) continue;

		if (dynamic_cast<Switch*>(pComp))
			m_SwitchList[swCount++] = pComp;
		else if (dynamic_cast<LED*>(pComp))
			m_LEDList[ledCount++] = pComp;
	}

	// Sort switches (Left -> Right)
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

	// Create Window
	int numRows = 1 << m_NumSwitches;
	int numCols = m_NumSwitches + m_NumLEDs;

	int colW = 50;
	int rowH = 25;
	int headH = 30;

	int wW = (numCols * colW) + 20;
	int wH = (numRows * rowH) + headH + 20;

	if (wW < 250) wW = 250;

	window* pTTWin = new window(wW, wH, 200, 100);
	pTTWin->ChangeTitle("Truth Table");

	int curX = 10;
	int curY = 5;

	pTTWin->SetPen(BLACK, 2);
	pTTWin->SetFont(20, BOLD, BY_NAME, "Arial");

	// Draw headers for Switches
	for (int i = 0; i < m_NumSwitches; ++i)
	{
		string lbl = m_SwitchList[i]->getLabel();
		if (lbl == "" || lbl == "Switch") lbl = "S" + to_string(i);

		pTTWin->DrawString(curX, curY, lbl);
		curX += colW;
	}

	pTTWin->DrawLine(curX - 10, 0, curX - 10, wH);

	// Draw headers for LEDs
	for (int i = 0; i < m_NumLEDs; ++i)
	{
		string lbl = m_LEDList[i]->getLabel();
		if (lbl == "" || lbl == "LED") lbl = "L" + to_string(i);

		pTTWin->DrawString(curX, curY, lbl);
		curX += colW;
	}

	pTTWin->DrawLine(0, headH, wW, headH);

	// Simulate and fill table
	curY = headH + 5;

	for (int r = 0; r < numRows; ++r)
	{
		curX = 10;

		// Set inputs based on row bits
		for (int s = 0; s < m_NumSwitches; ++s)
		{
			int val = (r >> (m_NumSwitches - 1 - s)) & 1;
			Switch* pSw = (Switch*)m_SwitchList[s];

			pSw->GetOutputPin()->setStatus(val ? HIGH : LOW);

			pTTWin->DrawString(curX, curY, to_string(val));
			curX += colW;
		}

		// Propagate logic
		int maxIter = totalComps + 10;
		for (int k = 0; k < maxIter; ++k)
		{
			for (int c = 0; c < totalComps; ++c)
			{
				Component* pComp = pManager->GetComponent(c);
				if (!pComp) continue;

				if (!dynamic_cast<Switch*>(pComp))
				{
					pComp->Operate();
				}
			}
		}

		// Read and draw outputs
		for (int l = 0; l < m_NumLEDs; ++l)
		{
			LED* pLed = (LED*)m_LEDList[l];

			// Use 1-based index (standard for this project)
			int status = pLed->GetInputPinStatus(1);

			pTTWin->DrawString(curX, curY, to_string(status == HIGH ? 1 : 0));
			curX += colW;
		}

		curY += rowH;
	}

	pTTWin->WaitMouseClick(curX, curY);
	delete pTTWin;
}

void CreateTruthTable::Undo() {}
void CreateTruthTable::Redo() {}
#include "AddConnection.h"
#include "ApplicationManager.h"
#include "Components/Gate.h"

AddConnection::AddConnection(ApplicationManager* pApp) : Action(pApp)
{
}

void AddConnection::ReadActionParameters()
{
    // 1. Get a pointer to Input and Output Interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

	comp = pManager->GetSelectedComponents();
    
    pOut->ClearStatusBar();
}

void AddConnection::Execute()
{
    ReadActionParameters();
    // Find the source and destination pins based on (x1, y1) and (x2, y2)
    OutputPin* pSrcPin = nullptr;
    InputPin* pDstPin = nullptr;

    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    if (comp.size() < 2)
    {
        pOut->PrintMsg("Less than two components are selected. Please select two components ");
        return;
    }
    else if (comp.size() > 2)
    {
        pOut->PrintMsg("More than two components are selected. Please select two components only");
        return;
    }

	// Assuming the first selected component is the source and the second is the destination
    GraphicsInfo srcgate= comp[0]->GetGraphicsInfo();
    GraphicsInfo dstgate = comp[1]->GetGraphicsInfo();
	  
	Gate* src = dynamic_cast<Gate*>(comp[0]);
    Gate* dst = dynamic_cast<Gate*>(comp[1]);
    if (src && dst)
    {
        pSrcPin = src->GetOutputPin();
        pDstPin = dst->GetInputPin(1); // Assuming we connect to the first input pin
    }
    else
    {
        pOut->PrintMsg("Selected components are not valid gates for connection.");
        return;
    }
    // Create GraphicsInfo for the connection
    GraphicsInfo gfxInfo;
    gfxInfo.x1 = (srcgate.x1 + srcgate.x2) / 2;
    gfxInfo.y1 = (srcgate.y1 + srcgate.y2) / 2;
    gfxInfo.x2 = (dstgate.x1 + dstgate.x2) / 2;
    gfxInfo.y2 = (dstgate.y1 + dstgate.y2) / 2;
    // Create the connection
    pConn = new Connection(gfxInfo, pSrcPin, pDstPin);
    // Add the connection to the application manager
	pManager->AddComponent(pConn);
}

void AddConnection::Undo()
{
    // To undo, we tell the manager to remove this specific connection
    pManager->RemoveComponent(pConn);
}

void AddConnection::Redo()
{
    // To redo, we simply add it back
    pManager->AddComponent(pConn);
}

AddConnection::~AddConnection()
{
	delete pConn;
}
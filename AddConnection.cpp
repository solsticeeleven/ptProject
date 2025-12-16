#include "AddConnection.h"
#include "ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp) : Action(pApp)
{
}

void AddConnection::ReadActionParameters()
{
    // 1. Get a pointer to Input and Output Interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("New Connection: Click on the Source Pin");
    pIn->GetPointClicked(x1, y1); // Get start coordinates

    pOut->PrintMsg("New Connection: Click on the Destination Pin");
    pIn->GetPointClicked(x2, y2); // Get end coordinates

    pOut->ClearStatusBar();
}

void AddConnection::Execute()
{
    // Find the source and destination pins based on (x1, y1) and (x2, y2)
    OutputPin* pSrcPin = nullptr;
    InputPin* pDstPin = nullptr;

    pConn = new Connection(GraphicsInfo{ x1, y1, x2, y2 }, pSrcPin, pDstPin);
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
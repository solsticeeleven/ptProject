#include "Probe.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

Probe::Probe(ApplicationManager* pApp) : Action(pApp)
{
}

Probe::~Probe()
{
}

void Probe::ReadActionParameters()
{
}

void Probe::Execute()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMsg("Probing Mode: Click on any component or connection to check its signal.");

    int x, y;
    pIn->GetPointClicked(x, y); 

    int compCount = pManager->GetComponentCount();
    bool found = false;

    // Iterate through all components to see if one was clicked
    for (int i = 0; i < compCount; i++)
    {
        Component* pComp = pManager->GetComponent(i);
        if (!pComp) continue;

        GraphicsInfo gfx = pComp->GetGraphicsInfo();

        // Check if point is inside the component's area
        if (x >= gfx.x1 && x <= gfx.x2 && y >= gfx.y1 && y <= gfx.y2)
        {
            found = true;
            int status = -1;

            // Check if it is a Connection (Special handling if needed, or just use GetOutPinStatus)
            status = pComp->GetOutPinStatus();


            string state = (status == HIGH) ? "HIGH (1)" : "LOW (0)";
            string label = pComp->getLabel();
            if (label == "") label = "Component";

            pOut->PrintMsg("Probe Result: " + label + " is " + state);
            return; 
        }
    }

    if (!found)
    {
        pOut->PrintMsg("No component found at this location.");
    }
}

void Probe::Undo()
{
}

void Probe::Redo()
{
}
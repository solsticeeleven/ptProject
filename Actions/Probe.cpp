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
        // For Connections, this bounding box might be large, but it works for basic hit-testing
        if (x >= gfx.x1 && x <= gfx.x2 && y >= gfx.y1 && y <= gfx.y2)
        {
            found = true;
            int status = -1;

            // Check if it is a Connection (Special handling if needed, or just use GetOutPinStatus)
            // Connection::GetOutPinStatus returns the destination pin status, which is effectively the wire's value.
            status = pComp->GetOutPinStatus();

            // Note: If pComp is an LED, GetOutPinStatus might return -1 or undefined depending on your implementation.
            // If so, you might need to check:
            /*
            if (dynamic_cast<LED*>(pComp)) {
                 status = pComp->GetInputPinStatus(0); // Check the input pin for LED
            }
            */

            string state = (status == HIGH) ? "HIGH (1)" : "LOW (0)";
            string label = pComp->getLabel();
            if (label == "") label = "Component";

            pOut->PrintMsg("Probe Result: " + label + " is " + state);
            return; // Exit after finding the first valid component
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
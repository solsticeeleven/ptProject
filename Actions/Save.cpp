#include "Save.h"
#include "../ApplicationManager.h"

// Include all your components
#include "../Components/AND2.h"
#include "../Components/AND3.h"
#include "../Components/BUFF.h"
#include "../Components/INV.h"
#include "../Components/NAND2.h"
#include "../Components/NOR2.h"
#include "../Components/NOR3.h"
#include "../Components/OR2.h"
#include "../Components/XNOR2.h"
#include "../Components/XOR2.h"
#include "../Components/XOR3.h"
#include "../Components/Connection.h"
#include "../Components/Gate.h"

#include <fstream>
#include <map>
#include <string>
using namespace std;

Save::Save(ApplicationManager* pApp) : Action(pApp) {}

void Save::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Enter file name:");
    string fileName = pIn->GetString(pOut) + ".txt";

    ofstream out(fileName);
    if (!out)
    {
        pOut->PrintMsg("Error opening file");
        return;
    }

    // --------------------------------------------------
    // 1) Assign IDs to NON-connection components
    // --------------------------------------------------
    map<Component*, int> compID;
    int id = 1;

    int compCount = 0;
    for (int i = 0; i < pManager->GetComponentCount(); i++)
        if (!dynamic_cast<Connection*>(pManager->GetComponent(i)))
            compCount++;

    out << compCount << endl;

    for (int i = 0; i < pManager->GetComponentCount(); i++)
    {
        Component* c = pManager->GetComponent(i);
        if (dynamic_cast<Connection*>(c)) continue;

        compID[c] = id;

        GraphicsInfo g = c->GetGraphicsInfo();
        string label = c->getLabel();

        // ---- component type ----
        if (dynamic_cast<AND2*>(c))       out << "AND2 ";
        else if (dynamic_cast<AND3*>(c))  out << "AND3 ";
        else if (dynamic_cast<BUFF*>(c))  out << "BUFF ";
        else if (dynamic_cast<INV*>(c))   out << "INV ";
        else if (dynamic_cast<NAND2*>(c)) out << "NAND2 ";
        else if (dynamic_cast<NOR2*>(c))  out << "NOR2 ";
        else if (dynamic_cast<NOR3*>(c))  out << "NOR3 ";
        else if (dynamic_cast<OR2*>(c))   out << "OR2 ";
        else if (dynamic_cast<XNOR2*>(c)) out << "XNOR2 ";
        else if (dynamic_cast<XOR2*>(c))  out << "XOR2 ";
        else if (dynamic_cast<XOR3*>(c))  out << "XOR3 ";

        out << id << " "
            << (label.empty() ? "NOLABEL" : label) << " "
            << g.x1 << " " << g.y1 << endl;

        id++;
    }

    // --------------------------------------------------
    // 2) Save connections
    // --------------------------------------------------
    out << "Connections" << endl;

    for (int i = 0; i < pManager->GetComponentCount(); i++)
    {
        Connection* conn = dynamic_cast<Connection*>(pManager->GetComponent(i));
        if (!conn) continue;

        OutputPin* srcPin = conn->getSourcePin();
        InputPin* dstPin = conn->getDestPin();

        if (!srcPin || !dstPin) continue;

        Component* srcComp = nullptr;
        Component* dstComp = dstPin->getComponent();

        // Find source component
        for (int j = 0; j < pManager->GetComponentCount(); j++)
        {
            Gate* g = dynamic_cast<Gate*>(pManager->GetComponent(j));
            if (g && g->GetOutputPin() == srcPin)
            {
                srcComp = g;
                break;
            }
        }

        if (!srcComp || !dstComp) continue;

        Gate* dstGate = dynamic_cast<Gate*>(dstComp);
        int pinIndex = dstGate->GetInputPinIndex(dstPin);

        out << compID[srcComp] << " "
            << compID[dstComp] << " "
            << pinIndex << endl;
    }

    out << "-1" << endl;
    out.close();

    pOut->PrintMsg("Circuit saved successfully");
}

void Save::ReadActionParameters() {}
void Save::Undo() {}
void Save::Redo() {}

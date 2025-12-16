#include "Load.h"
#include "../ApplicationManager.h"

// Include only your existing components
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

#include <fstream>
#include <map>
#include <sstream>
#include <limits>   // for std::numeric_limits
#include <ios>      // for std::streamsize


Load::Load(ApplicationManager* pApp) : Action(pApp) {}

void Load::ReadActionParameters()
{
    // Nothing to read for Load
}

void Load::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Enter file name to load:");
    std::string fileName = pIn->GetString(pOut) + ".txt";

    std::ifstream in(fileName);
    if (!in)
    {
        pOut->PrintMsg("Error opening file");
        return;
    }

    // 1) Clear existing components safely
    pManager->ClearAllComponents();

    int compCount = 0;
    in >> compCount;
    in.ignore(10000, '\n'); // skip up to 10,000 chars to next line


    std::map<int, Component*> idToComp;

    // 2) Load components
    for (int i = 0; i < compCount; ++i)
    {
        std::string line;
        std::getline(in, line);
        if (line.empty()) { --i; continue; } // skip empty lines

        std::istringstream iss(line);
        std::string type, label;
        int id, x1, y1;

        if (!(iss >> type >> id >> label >> x1 >> y1)) continue;
        if (label == "NOLABEL") label = "";

        Component* comp = nullptr;
        GraphicsInfo g{ x1, y1 };

        if (type == "AND2") comp = new AND2(g, 5);
        else if (type == "AND3") comp = new AND3(g, 5);
        else if (type == "BUFF") comp = new BUFF(g, 5);
        else if (type == "INV") comp = new INV(g, 5);
        else if (type == "NAND2") comp = new NAND2(g, 5);
        else if (type == "NOR2") comp = new NOR2(g, 5);
        else if (type == "NOR3") comp = new NOR3(g, 5);
        else if (type == "OR2") comp = new OR2(g, 5);
        else if (type == "XNOR2") comp = new XNOR2(g, 5);
        else if (type == "XOR2") comp = new XOR2(g, 5);
        else if (type == "XOR3") comp = new XOR3(g, 5);

        if (!comp) continue;

        comp->setLabel(label);
        pManager->AddComponent(comp);
        idToComp[id] = comp;
    }

    // 3) Load connections
    std::string line;
    std::getline(in, line); // should be "Connections"

    while (std::getline(in, line))
    {
        if (line.empty()) continue;
        std::istringstream iss(line);

        int srcID;
        iss >> srcID;
        if (srcID == -1) break;

        int dstID, pinIndex;
        if (!(iss >> dstID >> pinIndex)) continue;

        Component* srcComp = idToComp[srcID];
        Component* dstComp = idToComp[dstID];

        if (!srcComp || !dstComp) continue;

        Gate* srcGate = dynamic_cast<Gate*>(srcComp);
        Gate* dstGate = dynamic_cast<Gate*>(dstComp);
        if (!srcGate || !dstGate) continue;

        InputPin* dstPin = dstGate->GetInputPin(pinIndex);
        if (!dstPin) continue;

        // Connection graphics info (just for drawing)
        GraphicsInfo g;
        g.x1 = srcGate->GetGraphicsInfo().x1;
        g.y1 = srcGate->GetGraphicsInfo().y1;
        g.x2 = dstGate->GetGraphicsInfo().x1;
        g.y2 = dstGate->GetGraphicsInfo().y1;

        Connection* conn = new Connection(g, srcGate->GetOutputPin(), dstPin);
        srcGate->GetOutputPin()->ConnectTo(conn);
        pManager->AddComponent(conn);
    }

    in.close();

    // 4) Redraw interface
    pManager->UpdateInterface();
    pOut->PrintMsg("Circuit loaded successfully");
}

void Load::Undo() {}
void Load::Redo() {}

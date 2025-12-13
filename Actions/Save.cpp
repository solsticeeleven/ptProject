#include "Save.h"
#include "..\ApplicationManager.h" // make ApplicationManager complete for pManager usage

#include <fstream>
#include <vector>
#include <unordered_map>

#include "..\Components\Connection.h"
#include "..\Components\AND2.h"
#include "..\Components\AND3.h"
#include "..\Components\OR2.h"
#include "..\Components\NOR2.h"
#include "..\Components\NOR3.h"
#include "..\Components\XOR2.h"
#include "..\Components\XOR3.h"
#include "..\Components\XNOR2.h"
#include "..\Components\BUFF.h"
#include "..\Components\INV.h"
#include "..\Components\NAND2.h"

Save::Save(ApplicationManager* pApp) : Action(pApp)
{
}

Save::~Save()
{
}

void Save::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Enter filename to save (e.g. circuit.txt): ");
	filename = pIn->GetString(pOut);

	// basic validation
	while (filename.empty()) {
		pOut->PrintMsg("Filename cannot be empty. Enter filename: ");
		filename = pIn->GetString(pOut);
	}

	pOut->ClearStatusBar();
}

void Save::Execute()
{
	ReadActionParameters();

	std::ofstream fout(filename);
	Output* pOut = pManager->GetOutput();

	if (!fout.is_open()) {
		pOut->PrintMsg("Error: Cannot open file for writing.");
		return;
	}

	// Separate components and connections (we save components first)
	std::vector<Component*> comps;
	std::vector<Connection*> conns;

	int total = pManager->GetComponentCount();
	for (int i = 0; i < total; ++i) {
		Component* c = pManager->GetComponent(i);
		Connection* conn = dynamic_cast<Connection*>(c);
		if (conn)
			conns.push_back(conn);
		else
			comps.push_back(c);
	}

	// Assign ids to components (1-based)
	std::unordered_map<Component*, int> idMap;
	for (size_t i = 0; i < comps.size(); ++i) {
		idMap[comps[i]] = static_cast<int>(i) + 1;
	}

	// Write components header
	fout << "COMPONENTS " << comps.size() << "\n";
	for (size_t i = 0; i < comps.size(); ++i) {
		Component* c = comps[i];
		GraphicsInfo g = c->GetGraphicsInfo();
		std::string type = "UNKNOWN";

		if (dynamic_cast<AND2*>(c)) type = "AND2";
		else if (dynamic_cast<AND3*>(c)) type = "AND3";
		else if (dynamic_cast<OR2*>(c)) type = "OR2";
		else if (dynamic_cast<NOR2*>(c)) type = "NOR2";
		else if (dynamic_cast<NOR3*>(c)) type = "NOR3";
		else if (dynamic_cast<XOR2*>(c)) type = "XOR2";
		else if (dynamic_cast<XOR3*>(c)) type = "XOR3";
		else if (dynamic_cast<XNOR2*>(c)) type = "XNOR2";
		else if (dynamic_cast<BUFF*>(c)) type = "BUFF";
		else if (dynamic_cast<INV*>(c)) type = "INV"; //CANT INCLUDE NAND2
		// if you have SWITCH/LED classes, add here similarly

		// write: TYPE ID x1 y1 x2 y2 [label optional]
		fout << type << " " << idMap[c] << " "
			<< g.x1 << " " << g.y1 << " " << g.x2 << " " << g.y2;

		std::string lbl = c->getLabel();
		if (!lbl.empty()) {
			// write label after a space. labels can contain spaces; write the rest of line as label.
			fout << " " << lbl;
		}
		fout << "\n";
	}

	// Write connections
	fout << "CONNECTIONS " << conns.size() << "\n";
	for (size_t i = 0; i < conns.size(); ++i) {
		Connection* conn = conns[i];
		OutputPin* sPin = conn->getSourcePin();
		InputPin* dPin = conn->getDestPin();
		Component* dstCmp = dPin->getComponent();

		// find source component by comparing output pin addresses
		Component* srcCmp = nullptr;
		for (auto &entry : idMap) {
			Component* cand = entry.first;
			Gate* g = dynamic_cast<Gate*>(cand);
			if (g && g->GetOutputPin() == sPin) {
				srcCmp = cand;
				break;
			}
		}

		if (!srcCmp) {
			// source might be a component not in comps (unlikely), skip with message
			continue;
		}

		int srcId = idMap[srcCmp];
		int dstId = -1;
		auto it = idMap.find(dstCmp);
		if (it != idMap.end()) dstId = it->second;

		int dstPinIndex = -1;
		Gate* dstGate = dynamic_cast<Gate*>(dstCmp);
		if (dstGate) dstPinIndex = dstGate->GetInputPinIndex(dPin);

		GraphicsInfo gg = conn->GetGraphicsInfo();

		fout << srcId << " " << dstId << " " << dstPinIndex << " "
			<< gg.x1 << " " << gg.y1 << " " << gg.x2 << " " << gg.y2 << "\n";
	}

	fout.close();
	pOut->PrintMsg("Saved to " + filename);
}

void Save::Undo() {}
void Save::Redo() {}
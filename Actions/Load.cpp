#include "Load.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"

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

#include <fstream>
#include <sstream>
#include <unordered_map>

Load::Load(ApplicationManager* pApp) : Action(pApp), filename("") {}

Load::~Load() {}

void Load::ReadActionParameters()
{
	Output* out = pManager->GetOutput();
	Input* in = pManager->GetInput();

	out->PrintMsg("Enter filename to load:");
	filename = in->GetString(out);
	out->ClearStatusBar();
}

void Load::Execute()
{
	ReadActionParameters();

	Output* out = pManager->GetOutput();

	std::ifstream infile(filename);
	if (!infile.is_open())
	{
		out->PrintMsg("Error: could not open file: " + filename);
		return;
	}

	// Clear existing components
	pManager->SetSelectedComponent(nullptr);
	pManager->ClearAllComponents();

	std::string line;
	// Read components header
	if (!std::getline(infile, line)) {
		out->PrintMsg("Load failed: empty file.");
		return;
	}

	std::istringstream headerIss(line);
	std::string headerType;
	int compCount = 0;
	headerIss >> headerType >> compCount;
	if (headerType != "COMPONENTS") {
		out->PrintMsg("Load failed: invalid file format (missing COMPONENTS).");
		return;
	}

	// Map saved id -> created Component*
	std::unordered_map<int, Component*> idMap;
	for (int i = 0; i < compCount; ++i) {
		// read next non-empty line
		do {
			if (!std::getline(infile, line)) {
				out->PrintMsg("Load failed: unexpected end of components section.");
				return;
			}
		} while (line.size() == 0);

		std::istringstream iss(line);
		std::string type;
		int savedId;
		int x1, y1, x2, y2;
		if (!(iss >> type >> savedId >> x1 >> y1 >> x2 >> y2)) {
			out->PrintMsg("Load failed: malformed component line.");
			return;
		}

		std::string label;
		// read the rest of the line as label (may contain spaces)
		std::getline(iss, label);
		// trim leading spaces
		if (!label.empty() && label.front() == ' ')
			label.erase(0, label.find_first_not_of(' '));

		GraphicsInfo g;
		g.x1 = x1; g.y1 = y1; g.x2 = x2; g.y2 = y2;

		Component* created = nullptr;

		if (type == "AND2") {
			created = new AND2(g, AND2_FANOUT);
		}
		else if (type == "AND3") {
			created = new AND3(g, AND3_FANOUT);
		}
		else if (type == "OR2") {
			created = new OR2(g, OR2_FANOUT);
		}
		else if (type == "NOR2") {
			created = new NOR2(g, NOR2_FANOUT);
		}
		else if (type == "NOR3") {
			created = new NOR3(g, NOR3_FANOUT);
		}
		else if (type == "XOR2") {
			created = new XOR2(g, XOR2_FANOUT);
		}
		else if (type == "XOR3") {
			created = new XOR3(g, XOR3_FANOUT);
		}
		else if (type == "XNOR2") {
			created = new XNOR2(g, XNOR2_FANOUT);
		}
		else if (type == "BUFF") {
			created = new BUFF(g, BUFF_FANOUT);
		}
		else if (type == "INV") {
			created = new INV(g, INV_FANOUT);
		}
		else {
			// Unknown type -> skip
			continue;
		}

		if (created) {
			if (!label.empty())
				created->setLabel(label);
			pManager->AddComponent(created);
			idMap[savedId] = created;
		}
	}

	// Read connections header
	do {
		if (!std::getline(infile, line)) {
			// No connections section; finish loading
			out->PrintMsg("Loaded " + filename);
			return;
		}
	} while (line.size() == 0);

	std::istringstream connHeaderIss(line);
	std::string connHeader;
	int connCount = 0;
	connHeaderIss >> connHeader >> connCount;
	if (connHeader != "CONNECTIONS") {
		out->PrintMsg("Load failed: invalid file format (missing CONNECTIONS).");
		return;
	}

	for (int i = 0; i < connCount; ++i) {
		// read next non-empty line
		do {
			if (!std::getline(infile, line)) {
				out->PrintMsg("Load failed: unexpected end of connections section.");
				return;
			}
		} while (line.size() == 0);

		std::istringstream iss(line);
		int srcId, dstId, dstPinIndex;
		int x1, y1, x2, y2;
		if (!(iss >> srcId >> dstId >> dstPinIndex >> x1 >> y1 >> x2 >> y2)) {
			out->PrintMsg("Load failed: malformed connection line.");
			return;
		}

		auto srcIt = idMap.find(srcId);
		auto dstIt = idMap.find(dstId);
		if (srcIt == idMap.end() || dstIt == idMap.end()) {
			// missing component referenced; skip this connection
			continue;
		}

		Component* srcCmp = srcIt->second;
		Component* dstCmp = dstIt->second;

		Gate* srcGate = dynamic_cast<Gate*>(srcCmp);
		Gate* dstGate = dynamic_cast<Gate*>(dstCmp);
		if (!srcGate || !dstGate) {
			// invalid connection endpoints
			continue;
		}

		OutputPin* sPin = srcGate->GetOutputPin();
		InputPin* dPin = dstGate->GetInputPin(dstPinIndex); // 1-based index as saved

		if (!sPin || !dPin) continue;

		GraphicsInfo gg;
		gg.x1 = x1; gg.y1 = y1; gg.x2 = x2; gg.y2 = y2;

		Connection* conn = new Connection(gg, sPin, dPin);
		// Constructor should set pins, but ensure they are linked
		conn->setSourcePin(sPin);
		conn->setDestPin(dPin);

		pManager->AddComponent(conn);
	}

	infile.close();
	out->PrintMsg("Loaded " + filename);
}

void Load::Undo()
{
	// Not implemented
}

void Load::Redo()
{
	// Not implemented
}
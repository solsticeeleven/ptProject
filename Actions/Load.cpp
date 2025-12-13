#include "Load.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"

#include <fstream>

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

    // Placeholder: actual deserialization of components should go here.
    // For now just confirm file is readable.
    std::string line;
    if (std::getline(infile, line))
    {
        out->PrintMsg("Loaded file: " + filename);
    }
    else
    {
        out->PrintMsg("File is empty or unreadable: " + filename);
    }

    infile.close();
}

void Load::Undo()
{
    // Not implemented
}

void Load::Redo()
{
    // Not implemented
}
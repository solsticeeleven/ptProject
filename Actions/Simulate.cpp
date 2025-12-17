#include "Simulate.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include <iostream>

using namespace std;

Simulate::Simulate(ApplicationManager* pApp) : Action(pApp)
{
    cout << "Initializing Simulation Parameters" << endl;


    time_Step = 0.1;
    total = 10.0;
    current = 0.0;

    cout << "Simulation Initialized with time step: " << time_Step << " & total time: " << total << endl;
}

Simulate::~Simulate() {
}

void Simulate::initialize() {
    cout << " Initializing Simulation" << endl;
}

void Simulate::update() {
    current += time_Step;
}

void Simulate::run() {
    initialize();
    while (current < total) {
        update();
    }
    finalize();
}

void Simulate::finalize() {
    cout << "Simulation Complete at t=   " << current << endl;
}

void Simulate::ReadActionParameters()
{

}

void Simulate::Execute()
{
    Output* pOut = pManager->GetOutput();

    pOut->PrintMsg("Click switches to toggle, or click Truth Table.");

    pOut->CreateSimulationToolBar();

    pManager->UpdateInterface(); 
}


void Simulate::Undo()
{
}

void Simulate::Redo()
{
}
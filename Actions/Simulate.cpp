#include "Simulate.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include <iostream>

using namespace std;

Simulate::Simulate(ApplicationManager* pApp) : Action(pApp)
{
    cout << "Initializing Simulation Parameters" << endl;


    timeStep = 0.1;
    totalTime = 10.0;
    currentTime = 0.0;

    cout << "Simulation Initialized with time step: " << timeStep << " and total time: " << totalTime << endl;
}

Simulate::~Simulate() {
}

void Simulate::initialize() {
    cout << " Initializing Simulation" << endl;
}

void Simulate::update() {
    currentTime += timeStep;
}

void Simulate::run() {
    initialize();
    while (currentTime < totalTime) {
        update();
    }
    finalize();
}

void Simulate::finalize() {
    cout << "Simulation Complete at t=   " << currentTime << endl;
}

void Simulate::ReadActionParameters()
{

}

void Simulate::Execute()
{
    Output* pOut = pManager->GetOutput();

    pOut->PrintMsg("Simulation Mode: Click switches to toggle, or click Truth Table.");

    pOut->CreateSimulationToolBar();

    pManager->Execute();

    pManager->UpdateInterface(); 
}


void Simulate::Undo()
{
}

void Simulate::Redo()
{
}
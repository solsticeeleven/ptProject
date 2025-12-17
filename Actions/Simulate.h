#pragma once
#include "Action.h"


class Simulate : public Action

{

private:

    double time_Step;

    double total;

    double current;

public:

    void initialize();

    void update();

    void run();

    void finalize();



    Simulate(ApplicationManager* pApp);

    virtual ~Simulate();



    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

    virtual void Redo();

};
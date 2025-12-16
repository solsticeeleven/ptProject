#include "AddBUFFgate.h"

AddBUFFgate::AddBUFFgate(ApplicationManager* pApp) : Action(pApp) {
}

AddBUFFgate::~AddBUFFgate(void) {
}

void AddBUFFgate::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Buffer Gate: Click to add the gate");
    pIn->GetPointClicked(Cx, Cy);

    while (Cy < UI.ToolBarHeight || Cy > UI.height - UI.StatusBarHeight || Cx < 0 || Cx > UI.width)
    {
        pOut->PrintMsg("Invalid Location! Click within the drawing area");
        pIn->GetPointClicked(Cx, Cy);
    }

    pOut->ClearStatusBar();
}

void AddBUFFgate::Execute()
{
    ReadActionParameters();

    int Len = UI.BUFF_Width;
    int Wdth = UI.BUFF_Height;

    GraphicsInfo GInfo;
    GInfo.x1 = Cx - Len / 2;
    GInfo.x2 = Cx + Len / 2;
    GInfo.y1 = Cy - Wdth / 2;
    GInfo.y2 = Cy + Wdth / 2;

    for (int i = 0; i < pManager->GetComponentCount(); i++) {
        GraphicsInfo gfxInfo = pManager->GetComponent(i)->GetGraphicsInfo();
        if (!(GInfo.x2 < gfxInfo.x1 || GInfo.x1 > gfxInfo.x2 || GInfo.y2 < gfxInfo.y1 || GInfo.y1 > gfxInfo.y2)) {
            pManager->GetOutput()->PrintMsg("Error: Overlapping with another gate");
            return;
        }
    }

    BUFF* pA = new BUFF(GInfo, BUFF_FANOUT);
    pA->setSelected(false);
    pManager->AddComponent(pA);
}

void AddBUFFgate::Undo() {}
void AddBUFFgate::Redo() {}
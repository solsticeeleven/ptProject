//#include "ChangeSwitch.h"
//#include "../ApplicationManager.h" 
//#include "../Components/Switch.h" 
//#include <iostream>
//#include "Select.h"
//
//
//ChangeSwitch::ChangeSwitch(ApplicationManager* pApp) : Action(pApp) {}
//
//void ChangeSwitch::Execute()
//{
// 
//    std::cout << "Waiting for user to click a Switch..." << std::endl;
//
//    int x, y;
//    pManager->GetUI()->GetPointClicked(x, y);
//
//        Component* pComp = pManager->GetCurrentPointClicked(x, y);
//
//    if (pComp && dynamic_cast<Switch*>(pComp))
//    {
//        Switch* pSwitch = static_cast<Switch*>(pComp);
//
//        pSwitch->ToggleState();
//        std::cout << "Switch state toggled." << std::endl;
//
//            pManager->ExecuteAction(SIMULATE);
//    }
//    else
//    {
//        std::cout << "No switch component found at the clicked location." << std::endl;
//    }
//}
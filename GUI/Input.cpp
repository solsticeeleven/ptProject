//#include "Input.h"
#include "Output.h"

// Input constructor
Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pOut)
{
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	char c;
	string input = " ";
	pOut->PrintMsg("enter a string");
		while (true) {
			c = pWind->WaitKeyPress(c);    // store the key pressed in c
			if (c == 27) {                // check if c= ESC key 
				pOut->PrintMsg("");      //  ESC means cancel so we'll clear the status bar
				return " ";             // return empty string 
			}
			else if (c == 13) {            // check if c = enter key 
				pOut->PrintMsg(input);    // display the final text 
				return input;
			}
			else if (c == 8) {            // check if c= backspace key 
				if (!input.empty())      // only delete if the string is not empty 
					input.pop_back();   // remove last character 
			}
			else {
				input = input + c; 
			}
			pOut->PrintMsg(input);    // update the status bar with the current text
		}
	return NULL;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		// Top toolbar: LABEL .. EXIT
		const int topStart = ITM_LABEL;
		const int topEnd = ITM_EXIT;
		const int topCount = topEnd - topStart + 1;
		if (y >= 0 && y < UI.ToolBarHeight && topCount > 0)
		{
			int slotW = UI.width / topCount;
			int clicked = slotW > 0 ? (x / slotW) : 0;
			if (clicked < 0 || clicked >= topCount) return DSN_TOOL;
			int item = topStart + clicked;

			switch (item)
			{
			case ITM_LABEL:		return ADD_Label;
			case ITM_EDIT:		return EDIT_Label;
			case ITM_DEL:		return DEL;
			case ITM_MOVE:		return MOVE;
			case ITM_SAVE:		return SAVE;
			case ITM_LOAD:		return LOAD;
			case ITM_SIM_MODE:	return SIM_MODE;
			case ITM_EXIT:		return EXIT;
			default:			return DSN_TOOL;
			}
		}

		// Bottom toolbar: AND2 .. CONNECTION (drawn near bottom above status bar)
		const int bottomStart = ITM_AND2;
		const int bottomEnd = ITM_CONNECTION;
		const int bottomCount = bottomEnd - bottomStart + 1;
		int bottomTop = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;
		if (y >= bottomTop && y < bottomTop + UI.ToolBarHeight && bottomCount > 0)
		{
			int slotW = UI.width / bottomCount;
			int clicked = slotW > 0 ? (x / slotW) : 0;
			if (clicked < 0 || clicked >= bottomCount) return DSN_TOOL;
			int item = bottomStart + clicked;

			switch (item)
			{
			case ITM_AND2:		return ADD_AND_GATE_2;
			case ITM_OR2:		return ADD_OR_GATE_2;
			case ITM_NAND2:		return ADD_NAND_GATE_2;
			case ITM_NOR2:		return ADD_NOR_GATE_2;
			case ITM_XOR2:		return ADD_XOR_GATE_2;
			case ITM_XNOR2:		return ADD_XNOR_GATE_2;
			case ITM_AND3:		return ADD_AND_GATE_3;
			case ITM_NOR3:		return ADD_NOR_GATE_3;
			case ITM_XOR3:		return ADD_XOR_GATE_3;
			case ITM_Buff:		return ADD_Buff;
			case ITM_INV:		return ADD_INV;
			case ITM_SWITCH:	return ADD_Switch;
			case ITM_LED:		return ADD_LED;
			case ITM_CONNECTION:return ADD_CONNECTION;
			default:			return DSN_TOOL;
			}
		}

		// Click on drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user wants to select/unselect a component
		}

		// Click on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		// Top DSN image (centered) and left-column simulation icons (stacked)
		int topH = UI.ToolBarHeight;
		int bottomY = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;

		// DSN image area (same sizing logic used in CreateSimulationToolBar)
		int dsImgW = UI.ToolItemWidth * 2;
		if (dsImgW > UI.width) dsImgW = (UI.width * 80) / 100;
		int dsImgH = (topH * 80) / 100;
		int dsX = (UI.width - dsImgW) / 2;
		int dsY = (topH - dsImgH) / 2;

		// If click in top bar inside DSN image -> return to design
		if (y >= 0 && y < topH && x >= dsX && x < dsX + dsImgW)
		{
			return DSN_MODE;
		}

		// Left column detection for simulation icons
		int leftX = 0;
		int leftW = UI.ToolItemWidth;
		int leftTopY = topH;
		int leftBottomY = bottomY;
		int verticalArea = leftBottomY - leftTopY;
		const int leftCount = 4; // ITM_SIM, ITM_TRUTH, ITM_CHANGE_SWITCH, ITM_EXIT_SIM
		if (x >= leftX && x < leftX + leftW && y >= leftTopY && y < leftBottomY && verticalArea > 0)
		{
			int slotV = verticalArea / leftCount;
			int clicked = (y - leftTopY) / slotV;
			switch (clicked)
			{
			case 0: return SIMULATE;          // ITM_SIM
			case 1: return Create_TruthTable; // ITM_TRUTH
			case 2: return Change_Switch;     // ITM_CHANGE_SWITCH
			case 3: return EXIT;              // ITM_EXIT_SIM
			default: return DSN_TOOL;
			}
		}

		// Click in main drawing area while in simulation
		if (y >= topH && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;
		}

		// Click on the status bar
		return STATUS_BAR;
	}
}

Input::~Input()
{
}

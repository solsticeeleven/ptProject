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

	return string();
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
		return SIM_MODE;	//This should be changed after creating the complete simulation bar 
	}
}

Input::~Input()
{
}

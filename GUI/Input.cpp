//#include "Input.h"
#include "Output.h"

// Input constructor
Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetCurrentPointClicked(int &x, int &y)
{
	pWind->GetMouseCoord(x, y);	//Get current mouse coordinates
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString(Output *pOut)
{
	string str="";
	char key='\0';

	while (true)
	{
		pWind->WaitKeyPress(key);
		if (key == 13) //enter
		{
			return str;
		}
		else if (key == 8) //Backspace
		{
			if (str.size() > 0)
			{
				str.resize(str.size() - 1);
			}
		}
		else if (key=='\x1B') //esc
		{
			return "";
		}
		else
			str += key;

		pOut->PrintMsg(str);
	}

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
					input.resize(input.size()-1) ;   // remove last character 
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
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
				case ITM_AND2: return ADD_AND_GATE_2;
				case ITM_OR2: return ADD_OR_GATE_2;
				case ITM_NAND2: return ADD_NAND_GATE_2;
				case ITM_NOR2: return ADD_NOR_GATE_2;
				case ITM_XOR2: return ADD_XOR_GATE_2;
				case ITM_XNOR2: return ADD_XNOR_GATE_2;
				case ITM_AND3: return ADD_AND_GATE_3;
				case ITM_NOR3: return ADD_NOR_GATE_3;
				case ITM_XOR3: return ADD_XOR_GATE_3;
				case ITM_Buff: return ADD_Buff;
				case ITM_INV: return ADD_INV;
				case ITM_SWITCH: return ADD_Switch;
				case ITM_LED: return ADD_LED;
				case ITM_CONNECTION: return ADD_CONNECTION;
				case ITM_LABEL: return ADD_Label;
				case ITM_EDIT: return EDIT_Label;
				case ITM_DEL: return DEL;
				case ITM_MOVE: return MOVE;
				case ITM_COPY: return COPY;
				case ITM_PASTE: return PASTE;
				case ITM_SAVE: return SAVE;
				case ITM_LOAD: return LOAD;
				case ITM_SIM_MODE: return SIM_MODE;
				case ITM_EXIT: return EXIT;

			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.SimToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SIM: return SIMULATE;
			case ITM_TRUTH: return Create_TruthTable;
			case ITM_CHANGE_SWITCH: return Change_Switch;
			case ITM_PROBE: return PROBE;
			case ITM_DSN_MODE: return DSN_MODE;
			case ITM_EXIT_SIM: return EXIT;

			default: return SIM_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
}

Input::~Input()
{
}

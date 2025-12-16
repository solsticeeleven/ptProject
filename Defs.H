#ifndef CONST_H
#define CONST_H
//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType
{
	ADD_Buff,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection

	Create_TruthTable,	//Create Truth Table of the Circuit

	Change_Switch,		//Change Switch Status in Simulation Mode

	// New action for the "Simulate" button in the simulation toolbar
	SIMULATE,

	SELECT,		//Select a Component, a Connection
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection
	COPY,		//Copy a Component, a Connection
	PASTE,		//Paste a Component, a Connection

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode

	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
	SIM_TOOL	//A click on an empty place in the simulation tool bar

};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};


enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_AND2,		//done
	ITM_OR2,		//done
	ITM_NAND2,		//done
	ITM_NOR2,		//done
	ITM_XOR2,		//done
	ITM_XNOR2,		//done
	ITM_AND3,		//done
	ITM_NOR3,		//done
	ITM_XOR3,		//done
	ITM_Buff,		//donneee
	ITM_INV,		//doneee
	ITM_SWITCH,		//donee
	ITM_LED,		//DONe
	ITM_CONNECTION,	//DONE

	ITM_LABEL,		//Add label
	ITM_EDIT,		//Edit label
	ITM_DEL,		//Delete component
	ITM_MOVE,		//Move component
	ITM_COPY,		//Copy component
	ITM_PASTE,		//Paste component

	ITM_SAVE,		//Save circuit
	ITM_LOAD,		//Load circuit

	ITM_SIM_MODE,	//Switch to Simulation Mode

	ITM_EXIT,		//Exit item
	//TODO: Add more items names here doneeeeee

	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum

};


enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_SIM,	//Simulate menu item
	ITM_TRUTH,	//Truth table menu item
	ITM_CHANGE_SWITCH,	//Toggle switch status
	ITM_DSN_MODE,		//Return to Design mode
	ITM_EXIT_SIM,		//Exit application
	//TODO:Add more items names here doneeeeeeeeeee
	ITM_SIMULATE, 
	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5,	//Default fan out of 2-input AND gate
	OR2_FANOUT = 5,
	NAND2_FANOUT = 5,
	NOR2_FANOUT = 5,
	XOR2_FANOUT = 5,
	XNOR2_FANOUT = 5,
	AND3_FANOUT = 5,
	NOR3_FANOUT = 5,
	XOR3_FANOUT = 5,
	BUFF_FANOUT = 5,
	INV_FANOUT = 5
};

//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1, y1, x2, y2;
};

#ifndef NULL
#define NULL 0
#endif

#endif
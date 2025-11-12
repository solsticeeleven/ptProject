#include "Output.h"
#include <windows.h>
#include <string>

static inline bool FileExists(const std::string &path) {
    DWORD attrs = GetFileAttributesA(path.c_str());
    return (attrs != INVALID_FILE_ATTRIBUTES) && ((attrs & FILE_ATTRIBUTE_DIRECTORY) == 0);
}

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	// Prepare list of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2]  = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]   = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_XOR2]  = "images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_NOR2]  = "images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_XNOR2]  = "images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_AND3]  = "images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_NOR3]  = "images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_XOR3]  = "images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_Buff] = "images\\Menu\\Menu_Buff.jpg";        // Buffer gate
	MenuItemImages[ITM_INV] = "images\\Menu\\Menu_INV.jpg";         // Inverter
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\Menu_SWITCH.jpg";      // Switch
	MenuItemImages[ITM_LED] = "images\\Menu\\Menu_LED.jpg";         // LED
	MenuItemImages[ITM_CONNECTION] = "images\\Menu\\Menu_CONNECTION.jpg";  // Wire connection
	MenuItemImages[ITM_LABEL] = "images\\Menu\\Menu_Label.jpg";
	MenuItemImages[ITM_EDIT] = "images\\Menu\\Menu_Edit.jpg";
	MenuItemImages[ITM_DEL] = "images\\Menu\\Menu_Del.jpg";
	MenuItemImages[ITM_MOVE] = "images\\Menu\\Menu_Move.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Menu_Load.jpg";
	MenuItemImages[ITM_SIM_MODE] = "images\\Menu\\Menu_SimMode.jpg";
	MenuItemImages[ITM_EXIT]  = "images\\Menu\\Menu_Exit.jpg";

	// Compute per-item layout using UI.ToolItemWidth (now computed to fit all items)
	int itemWidth = UI.ToolItemWidth;
	int itemHeight = UI.ToolBarHeight;

	// Draw menu item one image at a time.
	for (int i = 0; i < ITM_DSN_CNT; ++i) {
		const string &path = MenuItemImages[i];

		// scale the image to 80% of the slot so there is padding
		int imgW = (itemWidth * 80) / 100;
		int imgH = (itemHeight * 80) / 100;
		int xPos = i * itemWidth + (itemWidth - imgW) / 2;
		int yPos = (itemHeight - imgH) / 2;

		if (!path.empty() && FileExists(path)) {
			// constructing the temporary image can throw (missing file / load error).
			// guard with try/catch so a missing or bad image doesn't crash the app.
			try {
				pWind->DrawImage(path, xPos, yPos, imgW, imgH);
			} catch (...) {
				// draw placeholder background so separators are visible
				pWind->SetPen(UI.BkGrndColor);
				pWind->SetBrush(UI.BkGrndColor);
				pWind->DrawRectangle(i * itemWidth, 0, (i + 1) * itemWidth, UI.ToolBarHeight);
			}
		} else {
			// draw placeholder background so separators are visible
			pWind->SetPen(UI.BkGrndColor);
			pWind->SetBrush(UI.BkGrndColor);
			pWind->DrawRectangle(i * itemWidth, 0, (i + 1) * itemWidth, UI.ToolBarHeight);
		}
	}

	// Draw vertical red separators between buttons
	pWind->SetPen(RED, 1);
	for (int s = 1; s < ITM_DSN_CNT; ++s) {
		int x = s * UI.ToolItemWidth;
		pWind->DrawLine(x, 0, x, UI.ToolBarHeight);
	}

	// Draw a line under the toolbar (unchanged)
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)


}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\Gate_AND2_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

//TODO: Add similar functions to draw all components

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage="Images\\Gates\\Gate_OR2_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage="Images\\Gates\\Gate_NAND2_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage="Images\\Gates\\Gate_NOR2_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage="Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage="Images\\Gates\\Gate_AND3_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_AND3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage="Images\\Gates\\Gate_NOR3_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage="Images\\Gates\\Gate_XOR3_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_XOR3.jpg"; 
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage="Images\\Gates\\Gate_SWITCH_Hi.jpg";
	else 
		GateImage = "Images\\Gates\\Gate_SWITCH.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	//TODO: Add code to draw connection
}


Output::~Output()
{
	delete pWind;
}

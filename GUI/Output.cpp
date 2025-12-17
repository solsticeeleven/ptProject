#include "Output.h"
#include <windows.h>
#include <string>

// helper used to avoid constructing images when files don't exist
static inline bool FileExists(const std::string& path) {
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
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
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

void Output::ClearToolBar() const
{
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	// Clear the main drawing area (between top toolbar and status bar)
	// NOTE: removed code that repainted the bottom toolbar icons.
	// This prevents AND2..CONNECTION icons from being drawn at the bottom.
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearComponentArea(GraphicsInfo gfxInfo) const
{
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(gfxInfo.x1, gfxInfo.y1, gfxInfo.x2, gfxInfo.y2);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;    // Design Mode


	ClearToolBar();

	// Flush and update to avoid stale events/artifacts
	pWind->FlushMouseQueue();
	pWind->UpdateBuffer();

	// Prepare list of images for each menu item (matches DsgnMenuItem order)
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2] = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_XOR2] = "images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2] = "images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_AND3] = "images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_NOR3] = "images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_XOR3] = "images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_Buff] = "images\\Menu\\Menu_Buff.jpg";
	MenuItemImages[ITM_INV] = "images\\Menu\\Menu_INV.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\Menu_SWITCH.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\Menu_LED.jpg";
	MenuItemImages[ITM_CONNECTION] = "images\\Menu\\Menu_CONNECTION.jpg";

	MenuItemImages[ITM_LABEL] = "images\\Menu\\Menu_Label.jpg";
	MenuItemImages[ITM_EDIT] = "images\\Menu\\Menu_Edit.jpg";
	MenuItemImages[ITM_DEL] = "images\\Menu\\Menu_Del.jpg";
	MenuItemImages[ITM_MOVE] = "images\\Menu\\Menu_Move.jpg";
	MenuItemImages[ITM_COPY] = "images\\Menu\\Menu_COPY.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Menu\\Menu_PASTE.jpg";

	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Menu_Load.jpg";
	MenuItemImages[ITM_SIM_MODE] = "images\\Menu\\Menu_SIM_MODE.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	// draw all images side-by-side across top
	for (int i = 0; i < ITM_DSN_CNT; ++i) {
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{

	UI.AppMode = SIMULATION;	//Simulation Mode

	ClearToolBar();

	pWind->FlushMouseQueue();
	pWind->UpdateBuffer();

	// Simulation images (SimMenuItem order)
	string SimMenuItemImages[ITM_SIM_CNT];
	SimMenuItemImages[ITM_SIM] = "images\\Menu\\Menu_Simulate.jpg";      // Start/Run Simulation
	SimMenuItemImages[ITM_TRUTH] = "images\\Menu\\Menu_Truth.jpg";         // Show Truth Table
	SimMenuItemImages[ITM_CHANGE_SWITCH] = "images\\Menu\\Menu_ChangeSwitch.jpg";  // Toggle Switch Status
	SimMenuItemImages[ITM_PROBE] = "images\\Menu\\Menu_Probe.jpg"; 
	SimMenuItemImages[ITM_DSN_MODE] = "images\\Menu\\Menu_Design.jpg";        // Return to Design Mode
	SimMenuItemImages[ITM_EXIT_SIM] = "images\\Menu\\Menu_Exit.jpg";          // Exit Application

	for (int i = 0; i < ITM_SIM_CNT; ++i) {
		pWind->DrawImage(SimMenuItemImages[i], i * UI.SimToolItemWidth, 0, UI.SimToolItemWidth, UI.ToolBarHeight);
	}

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
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
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_AND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawBUFF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_BUFF_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_BUFF.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawINV(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_INV_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_INV.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_LED_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_LED.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_SWITCH_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_SWITCH.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	// Choose color
	color ConnColor = selected ? UI.SelectColor : UI.ConnColor;

	// Raw coordinates
	int x1 = r_GfxInfo.x1;
	int y1 = r_GfxInfo.y1;
	int x2 = r_GfxInfo.x2;
	int y2 = r_GfxInfo.y2;

	// Drawing bounds
	const int minX = 0;
	const int maxX = UI.width - 1;
	const int minY = UI.ToolBarHeight;
	const int maxY = UI.height - UI.StatusBarHeight - 1;

	auto clamp = [](int v, int lo, int hi) {
		return (v < lo) ? lo : (v > hi) ? hi : v;
		};

	// Clamp points
	int cx1 = clamp(x1, minX, maxX);
	int cy1 = clamp(y1, minY, maxY);
	int cx2 = clamp(x2, minX, maxX);
	int cy2 = clamp(y2, minY, maxY);

	// Nothing to draw
	if (cx1 == cx2 && cy1 == cy2)
		return;

	pWind->SetPen(ConnColor, 3);

	int dx = abs(cx2 - cx1);
	int dy = abs(cy2 - cy1);

	// Horizontal dominant → L-shaped wire
	if (dx >= dy)
	{
		int midX = (cx1 + cx2) / 2;
		pWind->DrawLine(cx1, cy1, midX, cy1);
		pWind->DrawLine(midX, cy1, midX, cy2);
		pWind->DrawLine(midX, cy2, cx2, cy2);
	}
	// Vertical dominant → inverted L
	else
	{
		int midY = (cy1 + cy2) / 2;
		pWind->DrawLine(cx1, cy1, cx1, midY);
		pWind->DrawLine(cx1, midY, cx2, midY);
		pWind->DrawLine(cx2, midY, cx2, cy2);
	}
}




Output::~Output()
{
	delete pWind;
}
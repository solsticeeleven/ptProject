#include "Output.h"
#include <windows.h>
#include <string>

// helper used to avoid constructing images when files don't exist
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
	// Clear the main drawing area (between top toolbar and status bar)
	// NOTE: removed code that repainted the bottom toolbar icons.
	// This prevents AND2..CONNECTION icons from being drawn at the bottom.
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
    UI.AppMode = DESIGN;    // Design Mode

    // Flush and update to avoid stale events/artifacts
    pWind->FlushMouseQueue();
    pWind->UpdateBuffer();

    // Prepare list of images for each menu item (matches DsgnMenuItem order)
    string MenuItemImages[ITM_DSN_CNT];
    MenuItemImages[ITM_AND2]  = "images\\Menu\\Menu_AND2.jpg";
    MenuItemImages[ITM_OR2]   = "images\\Menu\\Menu_OR2.jpg";
    MenuItemImages[ITM_NAND2] = "images\\Menu\\Menu_NAND2.jpg";
    MenuItemImages[ITM_NOR2]  = "images\\Menu\\Menu_NOR2.jpg";
    MenuItemImages[ITM_XOR2]  = "images\\Menu\\Menu_XOR2.jpg";
    MenuItemImages[ITM_XNOR2] = "images\\Menu\\Menu_XNOR2.jpg";
    MenuItemImages[ITM_AND3]  = "images\\Menu\\Menu_AND3.jpg";
    MenuItemImages[ITM_NOR3]  = "images\\Menu\\Menu_NOR3.jpg";
    MenuItemImages[ITM_XOR3]  = "images\\Menu\\Menu_XOR3.jpg";
    MenuItemImages[ITM_Buff]  = "images\\Menu\\Menu_Buff.jpg";
    MenuItemImages[ITM_INV]   = "images\\Menu\\Menu_INV.jpg";
    MenuItemImages[ITM_SWITCH]= "images\\Menu\\Menu_SWITCH.jpg";
    MenuItemImages[ITM_LED]   = "images\\Menu\\Menu_LED.jpg";
    MenuItemImages[ITM_CONNECTION] = "images\\Menu\\Menu_CONNECTION.jpg";

    MenuItemImages[ITM_LABEL] = "images\\Menu\\Menu_Label.jpg";
    MenuItemImages[ITM_EDIT]  = "images\\Menu\\Menu_Edit.jpg";
    MenuItemImages[ITM_DEL]   = "images\\Menu\\Menu_Del.jpg";
    MenuItemImages[ITM_MOVE]  = "images\\Menu\\Menu_Move.jpg";
    MenuItemImages[ITM_SAVE]  = "images\\Menu\\Menu_Save.jpg";
    MenuItemImages[ITM_LOAD]  = "images\\Menu\\Menu_Load.jpg";
    MenuItemImages[ITM_SIM_MODE] = "images\\Menu\\Menu_SIM_MODE.jpg";
    MenuItemImages[ITM_EXIT]  = "images\\Menu\\Menu_Exit.jpg";

    // draw all images side-by-side across top
    for (int i = 0; i < ITM_DSN_CNT; ++i) {
		cout << UI.ToolItemWidth;
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

	// Ensure any pending mouse events are discarded so the next click is fresh.
	pWind->FlushMouseQueue();
	// Force buffer update (harmless if no double-buffering)
	pWind->UpdateBuffer();

	// Simulation images (SimMenuItem order)
	string SimMenuItemImages[ITM_SIM_CNT];
	SimMenuItemImages[ITM_SIM] = "images\\Menu\\Menu_Simulate.jpg";      // Start/Run Simulation
	SimMenuItemImages[ITM_TRUTH] = "images\\Menu\\Menu_Truth.jpg";         // Show Truth Table
	SimMenuItemImages[ITM_CHANGE_SWITCH] = "images\\Menu\\Menu_ChangeSwitch.jpg";  // Toggle Switch Status
	SimMenuItemImages[ITM_DSN_MODE] = "images\\Menu\\Menu_Design.jpg";        // Return to Design Mode
	SimMenuItemImages[ITM_EXIT_SIM] = "images\\Menu\\Menu_Exit.jpg";          // Exit Application

	// Clear design areas that might conflict
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	// Clear top row and left strip used by simulation icons
	int slotH = UI.ToolBarHeight;
	int bottomY = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;
	pWind->DrawRectangle(0, 0, UI.width, slotH); // top
	pWind->DrawRectangle(0, slotH, UI.ToolItemWidth, bottomY - slotH + slotH); // left column area

	// Draw the DSN_MODE image centered on the top row (this replaces the top row label icons while in simulation)
	int dsImgW = UI.ToolItemWidth * 2;
	if (dsImgW > UI.width) dsImgW = (UI.width * 80) / 100;
	int dsImgH = (slotH * 80) / 100;
	int dsX = (UI.width - dsImgW) / 2;
	int dsY = (slotH - dsImgH) / 2;
	if (FileExists(SimMenuItemImages[ITM_DSN_MODE])) {
		try {
			pWind->DrawImage(SimMenuItemImages[ITM_DSN_MODE], dsX, dsY, dsImgW, dsImgH);
		} catch (...) {
			pWind->SetPen(UI.BkGrndColor);
			pWind->SetBrush(UI.BkGrndColor);
			pWind->DrawRectangle(dsX, dsY, dsX + dsImgW, dsY + dsImgH);
		}
	} else {
		pWind->SetPen(UI.BkGrndColor);
		pWind->SetBrush(UI.BkGrndColor);
		pWind->DrawRectangle(dsX, dsY, dsX + dsImgW, dsY + dsImgH);
	}

	// Draw simulation icons vertically on the left (exclude the DSN_MODE, which is top-center)
	int leftIndices[] = { ITM_SIM, ITM_TRUTH, ITM_CHANGE_SWITCH, ITM_EXIT_SIM };
	int leftCount = sizeof(leftIndices) / sizeof(leftIndices[0]);
	int leftX = 0;
	int leftW = UI.ToolItemWidth;
	int leftTopY = slotH;
	int leftBottomY = bottomY;
	int verticalArea = leftBottomY - leftTopY;
	int slotV = (leftCount > 0) ? (verticalArea / leftCount) : verticalArea;

	for (int i = 0; i < leftCount; ++i) {
		int simIndex = leftIndices[i];
		const string &path = SimMenuItemImages[simIndex];

		int imgW = (leftW * 80) / 100;
		int imgH = (slotV * 80) / 100;
		int xPos = leftX + (leftW - imgW) / 2;
		int yPos = leftTopY + i * slotV + (slotV - imgH) / 2;

		if (!path.empty() && FileExists(path)) {
			try {
				pWind->DrawImage(path, xPos, yPos, imgW, imgH);
			} catch (...) {
				pWind->SetPen(UI.BkGrndColor);
				pWind->SetBrush(UI.BkGrndColor);
				pWind->DrawRectangle(leftX, leftTopY + i * slotV, leftX + leftW, leftTopY + (i + 1) * slotV);
			}
		} else {
			pWind->SetPen(UI.BkGrndColor);
			pWind->SetBrush(UI.BkGrndColor);
			pWind->DrawRectangle(leftX, leftTopY + i * slotV, leftX + leftW, leftTopY + (i + 1) * slotV);
		}
	}

	// Guiding lines (kept only to separate tool area from drawing area)
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, slotH, UI.width, slotH);   // under top row
	pWind->DrawLine(0, leftBottomY, UI.width, leftBottomY); // line above bottom toolbar region
}
//////////////////////////////////////////////////////////////////////////////////////////
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
		GateImage="Images\\Gates\\Gate_XOR2_Hi.jpg";
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
	// Choose color depending on whether it's selected or not
	color ConnColor = selected ? UI.SelectColor : UI.ConnColor;

	pWind->SetPen(ConnColor, 3);

	// Typically, a connection is drawn as an L-shaped or straight line.
	// Here we’ll draw an L-shaped wire for clarity (horizontal then vertical).

	int x1 = r_GfxInfo.x1;
	int y1 = r_GfxInfo.y1;
	int x2 = r_GfxInfo.x2;
	int y2 = r_GfxInfo.y2;

	// Draw horizontal then vertical segment (looks like a neat circuit wire)
	pWind->DrawLine(x1, y1, x2, y1); // horizontal segment
	pWind->DrawLine(x2, y1, x2, y2); // vertical segment
}



Output::~Output()
{
	delete pWind;
}

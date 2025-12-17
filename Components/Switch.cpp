#include <iostream>
#include "Switch.h"


//Switch Constructor
Switch::Switch(GraphicsInfo &r_GfxInfo) :Component(r_GfxInfo)
{
	m_Status;	//Initialize the status of switch to LOW
	closed = false;
}
void Switch::Operate()
{
	if (closed)
	{
		m_Status=LOW;
	}
	else if (!closed)
	{
		m_Status = HIGH;
}
	}
	void Switch::Draw(Output* pOut)
	{
		// Use the correct Output method to draw a switch
		pOut->DrawSWITCH(m_GfxInfo, isSelected);
	}
	int Switch::GetOutPinStatus()
	{
		return m_Status;
	}
	int Switch::GetInputPinStatus(int n)
	{
		return -1;	//No input pins in switch
	}	
	OutputPin* Switch::GetOutputPin()
	{
		return nullptr; //Switch has no output pin object
	}	
	void Switch::setInputPinStatus(int n, STATUS s)
	{
		//No input pins in switch, so do nothing
	}
	void Switch::Toggle()
	{
		//Toggle the status of the switch
		m_Status = (m_Status == LOW) ? HIGH : LOW;
	}
	Switch::~Switch()
	{
		//No dynamic memory to be deleted
	}
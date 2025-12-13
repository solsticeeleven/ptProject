#include "AND3.h"

AND3::AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(3, r_FanOut)
{
	// copy graphics info
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void AND3::Operate()
{
	// Output HIGH only if all three inputs are HIGH
	if (m_InputPins[0].getStatus() == HIGH &&
		m_InputPins[1].getStatus() == HIGH &&
		m_InputPins[2].getStatus() == HIGH)
	{
		m_OutputPin.setStatus(HIGH);
	}
	else {
		m_OutputPin.setStatus(LOW);
	}
}

void AND3::Draw(Output* pOut)
{
	// Use Output's DrawAND3 implementation
	pOut->DrawAND3(m_GfxInfo, isSelected);
}

int AND3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int AND3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	// n starts from 1
}

void AND3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
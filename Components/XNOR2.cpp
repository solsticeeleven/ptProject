#include "XNOR2.h"

XNOR2::XNOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XNOR2::Operate()
{
	if (m_InputPins[0].getStatus() == m_InputPins[1].getStatus()) {
		m_OutputPin.setStatus(HIGH);
	}
	else {
		m_OutputPin.setStatus(LOW);
	}

}


void XNOR2::Draw(Output* pOut)
{
	pOut->DrawXNOR2(m_GfxInfo, isSelected);
}


int XNOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


int XNOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();
}


void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
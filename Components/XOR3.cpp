#include "XOR3.h"

XOR3::XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(3, r_FanOut)
{
	// copy graphics info
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XOR3::Operate()
{
	// XOR for 3 inputs -> output HIGH when an odd number of inputs are HIGH
	int countHigh = 0;
	if (m_InputPins[0].getStatus() == HIGH) countHigh++;
	if (m_InputPins[1].getStatus() == HIGH) countHigh++;
	if (m_InputPins[2].getStatus() == HIGH) countHigh++;

	if (countHigh % 2 == 1)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

void XOR3::Draw(Output* pOut)
{
	// Use Output's DrawXOR3 implementation (consistent with other components)
	pOut->DrawXOR3(m_GfxInfo, isSelected);
}

int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	// n starts from 1
}

void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
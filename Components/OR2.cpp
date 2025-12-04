#include "OR2.h"

OR2::OR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void OR2::Operate() {
	if (m_InputPins[0].getStatus() == HIGH || m_InputPins[1].getStatus() == HIGH) {
		m_OutputPin.setStatus(HIGH);
	}
	else {
		m_OutputPin.setStatus(LOW);
	}
}

void OR2::Draw(Output* pOut) {
	if (isSelected)
		pOut->DrawOR2(m_GfxInfo, true);
	else
		pOut->DrawOR2(m_GfxInfo);
}

int OR2::GetOutPinStatus() {
	return m_OutputPin.getStatus();
}

int OR2::GetInputPinStatus(int n) {
	return m_InputPins[n - 1].getStatus();
}

void OR2::setInputPinStatus(int n, STATUS s) {
	m_InputPins[n - 1].setStatus(s);
}

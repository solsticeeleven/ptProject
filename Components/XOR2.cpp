#include "XOR2.h"

XOR2::XOR2(const GraphicsInfo& r_GfxInfo, int r_Fanout): Gate(2, r_Fanout) {
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XOR2::Operate() {
	if (m_InputPins[0].getStatus() != m_InputPins[1].getStatus()) {
		m_OutputPin.setStatus(HIGH);
	}
	else {
		m_OutputPin.setStatus(LOW);
	}
}

void XOR2::Draw(Output* pOut) {
	pOut->DrawXOR2(m_GfxInfo, isSelected);
}

int XOR2::GetOutPinStatus() {
	return m_OutputPin.getStatus();
}

int XOR2::GetInputPinStatus(int n) {
	return m_InputPins[n - 1].getStatus();
}

void XOR2::setInputPinStatus(int n, STATUS s) {
	m_InputPins[n - 1].setStatus(s);
}
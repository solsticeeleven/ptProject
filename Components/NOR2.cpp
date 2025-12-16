#include "NOR2.h"

NOR2::NOR2(const GraphicsInfo& r_GfxInfo, int r_Fanout) : Gate(2, r_Fanout) {
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void NOR2::Operate() {
	if (m_InputPins[0].getStatus() == LOW && m_InputPins[1].getStatus() == LOW) {
		m_OutputPin.setStatus(HIGH);
	} 
	else {
		m_OutputPin.setStatus(LOW);
	}
}

void NOR2::Draw(Output* pOut) {
	pOut->DrawNOR2(m_GfxInfo, isSelected);
}

int NOR2::GetOutPinStatus() {
	return m_OutputPin.getStatus();
}

int NOR2::GetInputPinStatus(int n) {
	return m_InputPins[n - 1].getStatus();
}

void NOR2::setInputPinStatus(int n, STATUS s) {
	m_InputPins[n - 1].setStatus(s);
}
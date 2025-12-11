#include "BUFF.h"

BUFF::BUFF(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(1, r_FanOut)
{
    m_GfxInfo = r_GfxInfo;
}

void BUFF::Operate()
{
    STATUS A = m_InputPins[0].getStatus();
    m_OutputPin.setStatus(A);
}

void BUFF::Draw(Output* pOut)
{
    pOut->DrawBUFF(m_GfxInfo, isSelected);
}

int BUFF::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int BUFF::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();
}

void BUFF::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}
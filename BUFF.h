#pragma once
#ifndef _BUFF_H
#define _BUFF_H

#include "Gate.h"

class BUFF : public Gate
{
public:
    BUFF(const GraphicsInfo& r_GfxInfo, int r_FanOut);

    virtual void Operate();
    virtual void Draw(Output* pOut);

    virtual int GetOutPinStatus();
    virtual int GetInputPinStatus(int n);

    virtual void setInputPinStatus(int n, STATUS s);
};

#endif


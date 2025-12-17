#pragma once
#ifndef _LED_H
#define _LED_H

//Led has one input pin and no output pin


#include "InputPin.h"
#include "Component.h"


class LED : public Component
{
protected:

	InputPin* m_InputPins;	//Array of input pins of the Led
	int m_Inputs;		//No. of input pins of that Led.
	bool illum;

public:

	LED (GraphicsInfo* pGfxInfo, int r_Inputs);

	virtual void Operate();	//Calculates the output of the led; whether it is on or off
	virtual void Draw(Output* pOut);	//Draws the led

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual InputPin* GetInputPin(int n);

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	virtual ~LED();
};

#endif

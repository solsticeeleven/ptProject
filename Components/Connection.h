#pragma once
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"

class Connection : public Component
{
	OutputPin* SrcPin;	
	InputPin* DstPin;	
public:
	Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin, InputPin *pDstPin);

	void Operate() override;	//Calculates the output according to the inputs
	void Draw(Output* pOut) override;	//to draw the connection itself

	void setSourcePin(OutputPin *pSrcPin);
	void setDestPin(InputPin *pDstPin);
	OutputPin* getSourcePin();
	InputPin* getDestPin();

	int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	int GetInputPinStatus(int n) ;	//returns status of Inputpin # n if SWITCH, return -1

	void setInputPinStatus(int n, STATUS s) override;	//set status of Inputpin, to be used by connection class.
};

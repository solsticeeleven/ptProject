#ifndef _XOR3_H
#define _XOR3_H

/*
  Class XOR3
  -----------
  represent the 3-input XOR gate (output HIGH when an odd number of inputs are HIGH)
*/

#include "Gate.h"

class XOR3 : public Gate
{
public:
	XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the XOR gate

	virtual void Draw(Output* pOut);	//Draws 3-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n
};

#endif
#ifndef _NOR3_H
#define _NOR3_H

/*
  Class NOR3
  -----------
  represent the 3-input NOR gate
*/

#include "Gate.h"

class NOR3 : public Gate
{
public:
	NOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the NOR gate

	virtual void Draw(Output* pOut);	//Draws 3-input gate

	virtual int GetOutPinStatus();	//returns status of output pin
	virtual int GetInputPinStatus(int n);	//returns status of Input pin # n

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Input pin # n
};

#endif
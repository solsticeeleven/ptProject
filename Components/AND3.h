#ifndef _AND3_H
#define _AND3_H

/*
  Class AND3
  -----------
  represent the 3-input AND gate
*/

#include "Gate.h"

class AND3 : public Gate
{
public:
	AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate

	virtual void Draw(Output* pOut);	//Draws 3-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n
};

#endif
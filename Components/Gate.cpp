#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);
}

OutputPin* Gate::GetOutputPin()
{
	return &m_OutputPin;
}

int Gate::GetInputPinIndex(InputPin* p)
{
	for (int i = 0; i < m_Inputs; ++i) {
		if (&m_InputPins[i] == p)
			return i + 1; // 1-based index to match project usage
	}
	return -1;
}
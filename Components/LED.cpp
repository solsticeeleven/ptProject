#include "LED.h"
#include "..\GUI\Output.h"
#include "Component.h"


//Led Constructor
//Parameters:
//r_Inputs: no. of led's input pins = 1
//r_FanOut: Fan out of the led's output pin
LED::LED(GraphicsInfo* pGfxInfo, int r_Inputs)
{
	illum = false;

	//Allocate number of input pins (equals r_Inputs) = 1
	r_Inputs = 1;
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that led

	//Associate all input pins to this led
	for (int i = 0; i < m_Inputs; i++)
		m_InputPins[i].setComponent(this);
}

InputPin* LED::GetInputPin(int n)
{
	return &m_InputPins[n];
}

void LED::Operate()
{
	//caclulate the output status of the led
	if (GetInputPinStatus(1) == LOW)
	{
		illum = 0;
	}

	else if (GetInputPinStatus(1) == HIGH)
	{
		illum = 1;
	}
	//Add you code here
}

//Draws the led
void LED::Draw(Output* pOut)
{
	//Call Output class and pass led drawing info to it.
	// Use the Output class to draw the LED at the component's graphics info
	// Pass the selection status to highlight if selected
	pOut->DrawLED(m_GfxInfo, isSelected);
}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)
{
	n = 1;
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	n = 1;
	m_InputPins[n - 1].setStatus(s);
}

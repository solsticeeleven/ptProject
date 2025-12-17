#ifndef _SWITCH_H
#define _SWITCH_H

#include "Component.h"
#include "OutputPin.h"

class Switch : public Component
{	
	private:
		STATUS m_Status;	//Status of the Switch	
		bool closed;        // Indicates if the switch is closed or open
public:	
		Switch(GraphicsInfo &r_GfxInfo);	
		virtual void Operate();	//Calculates the output according to the inputs
		virtual void Draw(Output* pOut);	//Draws the Switch
		
		virtual int GetOutPinStatus();	//returns status of outputpin
		virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n

		virtual OutputPin* GetOutputPin(); //returns pointer to outputpin
		virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
		
		void Toggle(); //Toggles the status of the switch
		
		virtual ~Switch();

};	
#endif
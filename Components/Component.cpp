#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo): isSelected(false)
{
	m_Label = "";
	m_GfxInfo = r_GfxInfo;	
}

GraphicsInfo Component::GetGraphicsInfo() const
{
	return m_GfxInfo;
}

void Component::setSelected(bool s) {
	isSelected = s;
}

void Component::setLabel(string label) {
	m_Label = (label.empty()) ? "" : label;
}

string Component::getLabel() const {
	return m_Label;
}

Component::Component()
{}

Component::~Component()
{}


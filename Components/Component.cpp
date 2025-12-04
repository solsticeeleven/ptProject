#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
}

GraphicsInfo Component::GetGraphicsInfo() const
{
	return m_GfxInfo;
}

void Component::setSelected(bool s) {
	isSelected = s;
}

Component::Component()
{}

Component::~Component()
{}


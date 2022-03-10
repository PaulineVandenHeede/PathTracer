// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Light.h"

Light::Light(const Elite::RGBColor& colour, const float intensity, Group group)
	: m_Colour{ colour }
	, m_Intesity{ intensity }
	, m_Group{ group }
	, m_Enabled{ true }
{
}

Light::Group Light::GetGroup() const
{
	return m_Group;
}

void Light::DetermineGroup()
{
	if (m_Group != Group::none)
		return;

	m_Group = ReturnGroup();
}

bool Light::IsEnabled() const
{
	return m_Enabled;
}

void Light::ChangeEnable()
{
	m_Enabled = !m_Enabled;
}


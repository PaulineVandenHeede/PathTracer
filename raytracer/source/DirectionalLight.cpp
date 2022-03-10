// 2DAE07 - Vanden Heede, Pauline
#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Elite::FVector3& direction, const Elite::RGBColor& colour, const float intensity, const Light::Group group)
	: Light{ colour, intensity, group }
	, m_Direction{ direction }
{
}

Elite::FVector3 DirectionalLight::GetDirection(const Elite::FPoint3& hitPoint) const
{
	return m_Direction;
}

Elite::RGBColor DirectionalLight::GetBiradiance(const Elite::FPoint3& hitPoint) const
{
	Elite::RGBColor Ergb{ m_Colour * m_Intesity };
	return Ergb;
}

float DirectionalLight::LambertsCosineLaw(const Elite::FVector3& hitPointNormal, const Elite::FPoint3& hitPoint) const
{
	return Elite::Dot(hitPointNormal, m_Direction);
}

Light::Group DirectionalLight::ReturnGroup()
{
	return Light::Group::directional;
}

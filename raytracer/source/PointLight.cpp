// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "PointLight.h"

unsigned int PointLight::m_NrofPointlights{ 0 };
float PointLight::m_TotalXPos{ 0.f };
float PointLight::m_AverageXPos{ 0.f };

PointLight::PointLight(const Elite::FPoint3& position, const Elite::RGBColor& colour, const float intensity, const Light::Group group)
	: Light{ colour, intensity, group }
	, m_Position{ position }
{
	m_TotalXPos += position.x;
	++m_NrofPointlights;
	m_AverageXPos = (m_TotalXPos / m_NrofPointlights);
}


Elite::FVector3 PointLight::GetDirection(const Elite::FPoint3& hitPoint) const
{
	return Elite::FVector3{ hitPoint - m_Position };
}

Elite::RGBColor PointLight::GetBiradiance(const Elite::FPoint3& hitPoint) const
{
	//Formula for the biradiance of a pointlight
	if (hitPoint == m_Position) // there's no distance in between the points -> cannot devide by zero
		return Elite::RGBColor();
	float squareDistance{ Elite::SqrDistance(hitPoint, m_Position) };
	Elite::RGBColor Ergb{ m_Colour  * (m_Intesity / squareDistance) };
	return Ergb;
}

float PointLight::LambertsCosineLaw(const Elite::FVector3& hitPointNormal, const Elite::FPoint3& hitPoint) const
{
	return Elite::Dot(hitPointNormal, Elite::GetNormalized(GetDirection(hitPoint)));
}

Light::Group PointLight::ReturnGroup()
{
	if (m_AverageXPos < m_Position.x)
		return Light::Group::right;
	else
		return Light::Group::left;
}



//2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Light.h"

class PointLight final : public Light
{
public:
	PointLight(const Elite::FPoint3& position, const Elite::RGBColor& colour, const float intensity, const Light::Group group = Light::Group::none);

	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& hitPoint) const override;
	virtual Elite::RGBColor GetBiradiance(const Elite::FPoint3& hitPoint) const override;
	virtual float LambertsCosineLaw(const Elite::FVector3& hitPointNormal, const Elite::FPoint3& hitPoint) const override;


private:
	//Datamembers - derived class
	Elite::FPoint3 m_Position;

	static float m_TotalXPos;
	static unsigned int m_NrofPointlights;
	static float m_AverageXPos;

	//Helper functions
	virtual Group ReturnGroup() override;
};


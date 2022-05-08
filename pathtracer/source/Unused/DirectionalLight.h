// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Light.h"

class DirectionalLight final : public Light
{
public:
	DirectionalLight(const Elite::FVector3& direction, const Elite::RGBColor& colour, const float intensity, const Light::Group group = Light::Group::none);

	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& hitPoint) const override;
	virtual Elite::RGBColor GetBiradiance(const Elite::FPoint3& hitPoint) const override;
	virtual float LambertsCosineLaw(const Elite::FVector3& hitPointNormal, const Elite::FPoint3& hitPoint) const override;

private:
	//Datamembers- derived class
	Elite::FVector3 m_Direction;

	//Helper funcitons
	virtual Group ReturnGroup() override;
};


// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Material.h"

class Material_LambertCookTorrance final : public Material
{
public:
	//Albedo colour -> only for metal else 0.04,0.04,0.04
	//Metalness bool
	//Roughness float -> 0.01 = smooth (cannot be zero), 1.0 = rough
	Material_LambertCookTorrance(const Elite::RGBColor& albedoColour, const float roughness, const bool metalness);


	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const override;
private:
	//Datamembers - derived class
	bool m_Metalness;
};


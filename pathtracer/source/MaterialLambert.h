// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Material.h"

class MaterialLambert final : public Material
{
public:
	MaterialLambert(const Elite::RGBColor& diffuseColour, const float diffuseReflectance);

	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& w0 = Elite::FVector3::ZeroVector(), const Elite::FVector3& w1 = Elite::FVector3::ZeroVector()) const override;

};


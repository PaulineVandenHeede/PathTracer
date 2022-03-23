// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "MaterialLambert.h"
#include "BRDF.h"

MaterialLambert::MaterialLambert(const Elite::RGBColor& diffusColour, const float diffuseReflectance)
	: Material{ diffusColour, diffuseReflectance }
{
}

Elite::RGBColor MaterialLambert::Shade(const HitRecord& hitRecord, const Elite::FVector3& w0, const Elite::FVector3& w1) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_DiffuseColour);
}

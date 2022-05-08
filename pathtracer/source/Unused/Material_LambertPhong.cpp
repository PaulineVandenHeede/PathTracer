// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Material_LambertPhong.h"
#include "BRDF.h"

Material_LambertPhong::Material_LambertPhong(const float diffuseReflectance, const Elite::RGBColor& colour, const float specularReflectance, const int phongExponent)
	: Material{ colour, diffuseReflectance }
	, m_SpecularReflectance{ specularReflectance }
	, m_PhongExponent{ phongExponent }
{
}

Elite::RGBColor Material_LambertPhong::Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_DiffuseColour)
	 	+ BRDF::Phong(m_SpecularReflectance, m_PhongExponent, lightDirection, viewDirection, hitRecord.normal);
}

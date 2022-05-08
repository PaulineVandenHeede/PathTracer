// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Material_LambertCookTorrance.h"

Material_LambertCookTorrance::Material_LambertCookTorrance(const Elite::RGBColor& albedoColour, const float roughness, bool metalness)
	: Material{ albedoColour, roughness }
	, m_Metalness{ metalness }
{
}

Elite::RGBColor Material_LambertCookTorrance::Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const
{
	//Determine F0 = albedo colour -> lookup in slide for metals
	const Elite::RGBColor f0{ (m_Metalness == 0) ? Elite::RGBColor{ 0.04f, 0.04f, 0.04f } : m_DiffuseColour };
	
	Elite::RGBColor fresnel{ };

	Elite::RGBColor specularReflectance{ BRDF::CookTorrance(m_DiffuseReflectance, f0, viewDirection, hitRecord.normal, lightDirection, fresnel) };
	//Conservation of energy: snell's law
	Elite::RGBColor kd{ (m_Metalness == 1) ? Elite::RGBColor() : (Elite::RGBColor{ 1, 1, 1 } - fresnel) };

	//Final colour: kd * diffuse + ks * specular
	return fresnel * specularReflectance + kd * BRDF::Lambert(kd, m_DiffuseColour);
}

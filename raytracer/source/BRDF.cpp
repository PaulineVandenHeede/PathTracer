// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "BRDF.h"
#include "EMath.h"

Elite::RGBColor BRDF::Lambert(const float diffuseReflectance, const Elite::RGBColor& diffuseColour)
{
	const float constant{ diffuseReflectance / float(E_PI) };
	return diffuseColour * constant;
}

Elite::RGBColor BRDF::Lambert(const Elite::RGBColor& diffuseReflectance, const Elite::RGBColor& diffuseColour)
{
	return (diffuseReflectance / float(E_PI)) * diffuseColour;
}

Elite::RGBColor BRDF::Phong(const float specularReflectance, const int phongExponent, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection, const Elite::FVector3& hitRecordNormal)
{
	Elite::FVector3 reflect{-lightDirection + 2 * Elite::Dot(hitRecordNormal, lightDirection) * hitRecordNormal};
	float cosAngleReflectView{ Elite::Dot(reflect, viewDirection) };

	if (cosAngleReflectView < 0)
		return Elite::RGBColor(0.f, 0.f, 0.f);

	float PhongSpecularReflection{ specularReflectance * powf(cosAngleReflectView, float(phongExponent)) };

	return Elite::RGBColor(PhongSpecularReflection, PhongSpecularReflection, PhongSpecularReflection);
}

Elite::RGBColor BRDF::CookTorrance(const float roughness, const Elite::RGBColor& f0 , const Elite::FVector3& viewDirection, const Elite::FVector3& hitRecordNormal, const Elite::FVector3& lightDirection, Elite::RGBColor& fresnel)
{
	float denominator{ 4 * Elite::Dot(viewDirection, hitRecordNormal) * Elite::Dot(lightDirection, hitRecordNormal) };

	if(Elite::AreEqual(denominator, 0.f))
		return Elite::RGBColor();

	const Elite::FVector3 halfVector{ Elite::GetNormalized(viewDirection + lightDirection) };
	const float squaredRoughness{ roughness * roughness };

	fresnel = BRDF::Fresnel(f0, halfVector, viewDirection);
	//Smith's method: G for both shadowing and masking
	float geometry{ BRDF::Geometry(hitRecordNormal, viewDirection, squaredRoughness) * BRDF::Geometry(hitRecordNormal, lightDirection, squaredRoughness) };
	float normalDistribution{ BRDF::NormalDistribution(hitRecordNormal, halfVector, squaredRoughness) };

	return (fresnel * geometry * normalDistribution) / denominator;
}

Elite::RGBColor BRDF::Fresnel(const Elite::RGBColor& albedoColour, const Elite::FVector3& halfVector, const Elite::FVector3& viewDirection)
{
	//Schlick method
	float step1{ powf((1 - Elite::Dot(halfVector, viewDirection)), 5.f) };
	return albedoColour + ((Elite::RGBColor{ 1, 1, 1 } - albedoColour) * step1);
}

float BRDF::NormalDistribution(const Elite::FVector3& hitRecordNormal, const Elite::FVector3& halfVector, const float squaredRoughness)
{
	//Trowbridge-Reitz GGX
	float pow4Roughness{ squaredRoughness * squaredRoughness };
	float step1{ Elite::Dot(hitRecordNormal, halfVector) };
	float step2{ ((step1 * step1) * (pow4Roughness - 1)) + 1 };
	float denominator{ float(E_PI) * (step2 * step2) };
	if (Elite::AreEqual(denominator, 0.f))
		return 0.0f;
	return (pow4Roughness / denominator);
}

float BRDF::Geometry(const Elite::FVector3& hitRecordNormal, const Elite::FVector3& viewDirection, const float squaredRoughness)
{
	//Schlick-GGX
	float kDirect{ ((squaredRoughness + 1) * (squaredRoughness + 1)) / 8 };
	float dotNormalView{ Elite::Dot(hitRecordNormal, viewDirection) };
	float denominator{ (dotNormalView * (1 - kDirect)) + kDirect };
	if (Elite::AreEqual(denominator, 0.f))
		return 0.0f;
	return (dotNormalView / denominator);
}
 
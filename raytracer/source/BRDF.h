// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "ERGBColor.h"

namespace BRDF
{
	Elite::RGBColor Lambert(const float diffuseReflectance, const Elite::RGBColor& diffuseColour);
	Elite::RGBColor Lambert(const Elite::RGBColor& diffuseReflectance, const Elite::RGBColor& diffuseColour);
	Elite::RGBColor Phong(const float specularReflectance, const int phongExponent, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection, const Elite::FVector3& hitRecordNormal);
	Elite::RGBColor CookTorrance(const float roughness, const Elite::RGBColor& f0 , const Elite::FVector3& viewDirection, const Elite::FVector3& hitRecordNormal, const Elite::FVector3& lightDirection, Elite::RGBColor& fresnel);
	Elite::RGBColor Fresnel(const Elite::RGBColor& albedoColour, const Elite::FVector3& halfVector, const Elite::FVector3& viewDirection);
	float NormalDistribution(const Elite::FVector3& hitRecordNormal, const Elite::FVector3& halfVector, const float squaredRoughness);
	float Geometry(const Elite::FVector3& hitRecordNormal, const Elite::FVector3& viewDirection, const float squaredRoughness);
}
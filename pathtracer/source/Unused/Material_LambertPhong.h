// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Material.h"

class Material_LambertPhong final : public Material
{
public:
	/*The smaller the phong exponent the rougher the metal looks
		->The bigger the light spot
	*/
	Material_LambertPhong(const float diffuseReflectance, const Elite::RGBColor& colour, const float specularReflectance, const int phongExponent);

	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const override;
private:
	//Datamembers - derived class
	float m_SpecularReflectance;
	int m_PhongExponent;
};


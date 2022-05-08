// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "ERGBColor.h"
#include "EMath.h"
#include "HitRecord.h"
#include "BRDF.h"

class Material
{
public:
	Material(const Elite::RGBColor& colour, const float diffuseReflectance);

	//Calculates the outgoing radiance
	/*Calculates the outgoing radiance
			hitRecord
			w0 = incoming/ incident light direction = light direction
			w1 = view direction = ray direction
	*/
	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& w0 = Elite::FVector3::ZeroVector(), const Elite::FVector3& w1 = Elite::FVector3::ZeroVector()) const = 0;

protected:
	//Datamembers - base class
	Elite::RGBColor m_DiffuseColour;
	float m_DiffuseReflectance;
};


// 2DAE07 - Vanden Heede, Pauline
#pragma once
#include "EMath.h"
#include "MaterialManager.h"

struct HitRecord
{
	HitRecord();

	// Datamembers
	float tValue;
	Elite::FVector3 normal;
	Elite::FPoint3 hitPoint;
	Elite::RGBColor renderColour;
	MaterialName materialName;
};
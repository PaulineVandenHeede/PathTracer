// 2DAE07 - Vanden Heede, Pauline
#pragma once
#include "EMath.h"
#include "MaterialManager.h"

struct HitRecord
{
	HitRecord();

	// Datamembers
	MaterialName materialName;
	Elite::RGBColor renderColour;
	Elite::FVector3 normal;
	Elite::FPoint3 hitPoint;
	float tValue;
};
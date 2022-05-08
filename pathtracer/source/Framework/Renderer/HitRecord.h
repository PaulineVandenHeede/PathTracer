// 2DAE07 - Vanden Heede, Pauline
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#pragma once
#include "EMath.h"
#include "Materials.h"

struct HitRecord
{
	HitRecord();

	// Datamembers
	float tValue;
	Elite::FVector3 normal;
	Elite::FPoint3 hitPoint;
	Materials::BaseMaterial* pMaterial;
};
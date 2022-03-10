// 2DAE07 - Vanden Heede, Pauline
#pragma once
#include "EMath.h"
using namespace Elite;


struct Ray
{
	// Constructor
	Ray(const FPoint3& origin, const FVector3& direction, float tMin = 0.0001f, float tMax = FLT_MAX);

	// Datamembers
	FPoint3 origin;
	FVector3 direction;
	float tMin;
	float tMax;
};
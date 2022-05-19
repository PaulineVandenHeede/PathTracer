// 2DAE07 - Vanden Heede, Pauline
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022

#pragma once
#include "EMath.h"
using namespace Elite;


struct Ray
{
	// Constructor
	Ray() = default;
	//Ray(const FPoint3& origin, const FVector3& direction, float tMin = 0.0001f, float tMax = FLT_MAX);
	Ray(const FPoint3& origin, const FVector3& direction, float tMin = 0.0001f, float tMax = FLT_MAX);

	FPoint3 PointAtParameter(float t) const { return origin + t * direction; }

	// Datamembers
	FPoint3 origin;
	FVector3 direction;
	float tMin;
	float tMax;
};
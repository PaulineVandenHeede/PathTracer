// 2DAE07 - Vanden Heede, Pauline
#include "pch.h"
#include "Ray.h"

// Constructor
Ray::Ray(const FPoint3& origin, const FVector3& direction, float tMin, float tMax)
	: origin{ origin }
	, direction{ direction }
	, tMin{ tMin }
	, tMax{ tMax }
{

}
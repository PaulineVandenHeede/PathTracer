// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Plane.h"
#include "Hit.h"

Plane::Plane(const Elite::FPoint3& origin, const Elite::FVector3& normal, const MaterialName materialName, const CullMode cullMode)
	: Object{ origin, materialName }
	, m_Normal{ normal }
	, m_CullMode{ cullMode }
{
}

void Plane::Update(const float elapsedSec)
{
}

bool Plane::Hit(const Ray& ray, HitRecord& hitRecord, bool shadow) const
{
	//Find t = length of line between origin ray and hit position on plane
	//Dot1: ratio between the vectors, if this is zero they are perpendicular
	//Dot2: How are these two situated between each other
	float t{};
	if (!Hit::PlaneHit(ray, m_Normal, m_Origin, t, m_CullMode, shadow))
		return false;

	//Check if t is in interval of ray
	if (t < ray.tMin || t > ray.tMax)
		return false;

	if (hitRecord.tValue < t)
		return true;

	//Fill hitRecord with right information
	//Only display the closest value
	hitRecord.materialName = m_MaterialName;
	hitRecord.normal = m_Normal;
	hitRecord.hitPoint = ray.origin + t * ray.direction;
	hitRecord.tValue = t;
	return true;
}

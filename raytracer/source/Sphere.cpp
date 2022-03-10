// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Sphere.h"
#include "Hit.h"

Sphere::Sphere(const Elite::FPoint3& origin, const MaterialName materialName, const float radius)
	: Object{ origin, materialName }
	, m_Radius{ radius }
{
}

void Sphere::Update(const float elapsedSec)
{
}

bool Sphere::Hit(const Ray& ray, HitRecord& hitRecord, bool shadow) const
{
	float t{};
	if (!Hit::SphereHitAnalytic(ray, m_Origin, m_Radius, t))
		return false;

	//Check if t's are in interval
	if (t < ray.tMin || t > ray.tMax)
		return false;

	//Fill hitRecord
	if (hitRecord.tValue < t)
		return true;

	hitRecord.materialName = m_MaterialName;
	hitRecord.hitPoint = ray.origin + t * ray.direction;
	hitRecord.normal = GetNormalized(hitRecord.hitPoint - m_Origin);
	hitRecord.tValue = t;

	return true;
}

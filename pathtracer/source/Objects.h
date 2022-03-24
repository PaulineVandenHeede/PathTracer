#pragma once
#include "EMath.h"
#include "Ray.h"

struct HitRecord;

namespace Objects
{
	struct BaseObject
	{
		BaseObject() = default;
		~BaseObject() = default;
		virtual bool Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const = 0;
	};


	struct Sphere final : public BaseObject
	{
		Sphere(const Elite::FPoint3& _center, const float _radius) : center{ _center }, radius{ _radius } {}

		virtual bool Hit(HitRecord& record, const Ray& ray, float tmin = 0.01f, float tmax = FLT_MAX) const override;

		Elite::FPoint3 center;
		float radius;
	};
}




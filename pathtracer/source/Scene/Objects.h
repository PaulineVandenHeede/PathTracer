//3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#pragma once
#include "EMath.h"
#include "Ray.h"
#include "Materials.h"

struct HitRecord;

namespace Objects
{
	struct BaseObject
	{
		BaseObject() = default;
		virtual ~BaseObject() = default;
		virtual bool Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const = 0;
	};


	struct Sphere final : public BaseObject
	{
		//Sphere(const Elite::FPoint3& _center, const float _radius) : center{ _center }, radius{ _radius } {}
		Sphere(const Elite::FPoint3& _center, const float _radius, Materials::BaseMaterial* const _pMaterial) : center{ _center }, radius{ _radius }, pMaterial{ _pMaterial } {}
		virtual ~Sphere() override
		{
			SafeDelete(pMaterial);
		}
		virtual bool Hit(HitRecord& record, const Ray& ray, float tmin = 0.01f, float tmax = FLT_MAX) const override;

		Materials::BaseMaterial* pMaterial;
		Elite::FPoint3 center;
		float radius;
	};
}




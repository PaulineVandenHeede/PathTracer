//3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#pragma once
#include "EMath.h"
#include "Ray.h"
#include "Materials.h"

#include <array>

struct HitRecord;

enum CullMode
{
	frontCulling,
	backCulling,
	noCulling
};

namespace Objects
{
	struct BaseObject
	{
		BaseObject() = default;
		BaseObject(const Elite::FPoint3& _origin, Materials::BaseMaterial* _pMaterial) : origin{ _origin }, pMaterial{ _pMaterial } {}
		virtual ~BaseObject();

		virtual bool Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const = 0;
		virtual float PDFValue(const Elite::FPoint3& origin, const Elite::FVector3& direction) const { return 0.f; }
		virtual Elite::FVector3 Random(const Elite::FPoint3& origin) const { return { 1.f, 0.f, 0.f }; }

		Materials::BaseMaterial* pMaterial;
		Elite::FPoint3 origin;
	};

	struct Sphere final : public BaseObject
	{
		//Sphere(const Elite::FPoint3& _center, const float _radius) : center{ _center }, radius{ _radius } {}
		Sphere(const Elite::FPoint3& _origin, const float _radius, Materials::BaseMaterial* const _pMaterial) : BaseObject{ _origin, _pMaterial }, radius{ _radius } {}
		virtual ~Sphere() = default;
		bool Hit(HitRecord& record, const Ray& ray, float tmin = 0.01f, float tmax = FLT_MAX) const override;
		float PDFValue(const Elite::FPoint3& origin, const Elite::FVector3& direction) const override;
		Elite::FVector3 Random(const Elite::FPoint3& origin) const override;
		
		float radius;
	};

	struct Plane final : public BaseObject
	{
		Plane(const Elite::FPoint3& _origin, const Elite::FVector3& _normal, Materials::BaseMaterial* const _pMaterial, CullMode _cullMode = CullMode::noCulling)
			: BaseObject{ _origin, _pMaterial }, normal{ _normal }, cullMode{ _cullMode } {}
		virtual ~Plane() = default;
		virtual bool Hit(HitRecord& record, const Ray& ray, float tmin = 0.01f, float tmax = FLT_MAX) const override;

		CullMode cullMode;
		Elite::FVector3 normal;
	};

	struct Rectangle final : public BaseObject
	{
		Rectangle(std::array<Elite::FPoint3, 4>&& _corners, Materials::BaseMaterial* _pMaterial, CullMode _cullMode = CullMode::noCulling);
		virtual ~Rectangle() = default;

		bool Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const override;
		float PDFValue(const Elite::FPoint3& origin, const Elite::FVector3& direction) const override;
		Elite::FVector3 Random(const Elite::FPoint3& origin) const override;

		CullMode cullMode;
		Elite::FVector3 normal;
		std::array<Elite::FPoint3, 4> corners;
	};
}




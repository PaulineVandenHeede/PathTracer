// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Object.h"

class Sphere final : public Object
{
public:
	Sphere(const Elite::FPoint3& origin, const MaterialName materialName, const float radius);

	virtual void Update(const float elapsedSec) override;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool shadow) const override;

private:
	//Datamembers - derived class
	float m_Radius;
};
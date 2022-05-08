// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Object.h"
#include "Hit.h"

class Plane final : public Object
{
public:
	Plane(const Elite::FPoint3& origin, const Elite::FVector3& normal, const MaterialName materialName, const CullMode cullMode = CullMode::noCulling);

	virtual void Update(const float elapsedSec) override;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool shadow) const override;

private:
	//Datamembers - derived class
	Elite::FVector3 m_Normal;
	CullMode m_CullMode;
};
// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "EMath.h"
#include "Ray.h"
#include "HitRecord.h"
#include "MaterialManager.h"

using namespace Elite;
class MaterialManager;

class Object
{
public:
	Object(const Elite::FPoint3& origin, const MaterialName materialName);
	virtual ~Object() = default;

	virtual void Update(const float elapsedSec) = 0;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool shadow = false) const = 0; //Pure virtual

protected:
	//Datamembers - base class
	Elite::FPoint3 m_Origin;
	MaterialName m_MaterialName;
};
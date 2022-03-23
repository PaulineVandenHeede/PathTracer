// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Object.h"
#include "Hit.h"

class Triangle final : public Object
{
public:
	Triangle(const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2, const MaterialName materialName, const Elite::FVector3& translation = FVector3{0.f,0.f,0.f}, const float scale = 1.f, const float startingAngle = 0.f, bool counterclockwise = true, const CullMode cullMode = CullMode::noCulling);

	virtual void Update(const float elapsedSec) override;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool shadow) const override;
private:
	//Datamembers - derived class
	Elite::FMatrix4 m_Transformation;

	Elite::FVector3 m_Normal;
	Elite::FVector3 m_Translation;

	Elite::FPoint3 m_PositionOne;
	Elite::FPoint3 m_PositionTwo;
	Elite::FPoint3 m_Center;

	CullMode m_CullMode;

	int m_RotationSpeed;

	//Helper functions
	void Transfrom(const float angle);
	void InverseTransform();
};


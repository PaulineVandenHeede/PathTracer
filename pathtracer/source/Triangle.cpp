// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Triangle.h"

//v0,v1,v2: in counter-clock-wise order due to out coordinate system and the cross product
Triangle::Triangle(const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2, MaterialName materialName, const Elite::FVector3& translation, const float scale, const float startingAngle, bool counterclockwise, const CullMode cullMode)
	: Object{ v0, materialName }
	, m_Transformation{ Elite::FMatrix4::Identity() }
	, m_Normal{ Elite::FVector3::ZeroVector() }
	, m_Translation{ translation }
	, m_Center{  } //Get's filled in the body
	, m_CullMode{ cullMode }
	, m_RotationSpeed{ 60 * (counterclockwise ? 1 : -1) }
{
	m_Transformation *= static_cast<Elite::FMatrix4>(Elite::MakeScale(scale, scale, scale));

	m_Origin = static_cast<Elite::FPoint3>(m_Transformation* static_cast<Elite::FPoint4>(v0));
	m_PositionOne = static_cast<Elite::FPoint3>(m_Transformation* static_cast<Elite::FPoint4>(v1));
	m_PositionTwo = static_cast<Elite::FPoint3>(m_Transformation* static_cast<Elite::FPoint4>(v2));
	//Do this for if the triangle doesn't get updated
	Transfrom(Elite::ToRadians(startingAngle));
}

void Triangle::Update(const float elapsedSec)
{
	InverseTransform();
	float angle{ Elite::ToRadians(m_RotationSpeed * elapsedSec) };
	Transfrom(angle);
}

bool Triangle::Hit(const Ray& ray, HitRecord& hitRecord, bool shadow) const
{
	float t{};
	if (!Hit::TriangleHit(ray, m_Normal, m_Center, m_Origin, m_PositionOne, m_PositionTwo, t, m_CullMode, shadow))
		return false;

	if (hitRecord.tValue < t)
		return true;

	hitRecord.normal = Elite::GetNormalized(m_Normal);
	hitRecord.hitPoint = ray.origin + (t * ray.direction);
	hitRecord.materialName = m_MaterialName;
	hitRecord.tValue = t;

	return true;
}

void Triangle::Transfrom(const float angle)
{
	m_Transformation = FMatrix4::Identity();

	m_Transformation *= Elite::MakeTranslation(m_Translation);
	m_Transformation *= static_cast<Elite::FMatrix4>(Elite::MakeRotationY(angle));

	m_Origin = static_cast<FPoint3>(m_Transformation * static_cast<FPoint4>(m_Origin));
	m_PositionOne = static_cast<FPoint3>(m_Transformation * static_cast<FPoint4>(m_PositionOne));
	m_PositionTwo = static_cast<FPoint3>(m_Transformation * static_cast<FPoint4>(m_PositionTwo));

	//Rotate normal too -> it has to point out of the front triangle at all times
	//Center has to be calculated again
	m_Center = static_cast<Elite::FPoint3>((static_cast<Elite::FVector3>(m_Origin) + static_cast<Elite::FVector3>(m_PositionOne) + static_cast<Elite::FVector3>(m_PositionTwo)) / 3);
	m_Normal = Elite::GetNormalized(Elite::Cross(m_PositionOne - m_Origin, m_PositionTwo - m_Origin));
}
void Triangle::InverseTransform()
{
	m_Transformation = Elite::FMatrix4::Identity();
	m_Transformation *= static_cast<Elite::FMatrix4>(Elite::MakeTranslation(-m_Translation));

	m_Origin = static_cast<Elite::FPoint3>(m_Transformation * static_cast<Elite::FPoint4>(m_Origin));
	m_PositionOne = static_cast<Elite::FPoint3>(m_Transformation * static_cast<Elite::FPoint4>(m_PositionOne));
	m_PositionTwo = static_cast<Elite::FPoint3>(m_Transformation * static_cast<Elite::FPoint4>(m_PositionTwo));
}

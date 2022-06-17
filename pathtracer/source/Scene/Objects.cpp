//3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#include "pch.h"
#include "Objects.h"
#include "HitRecord.h"

namespace Objects
{
	BaseObject::~BaseObject()
	{
		SafeDelete(pMaterial);
	}

	bool Sphere::Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const
	{
		//Calculate discriminant
		Elite::FVector3 rp{ ray.origin - origin };
		float A{ Elite::Dot(ray.direction, ray.direction) };
		float B{ /*2.f * */Elite::Dot(rp, ray.direction) }; //remove redundant 2
		float C{ Elite::Dot(rp,rp) - (radius * radius) };

		float D{ B * B -/* 4 **/ A * C }; //remove redundant 2; 2*2 = 4

		if (D < 0 || Elite::AreEqual(D, 0.f))
			return false;


		float Ds{ sqrtf(D) };
		//Find t: length of line between origin ray and hit point sphere
		//Use substraction, except when t < ray.tMin
		float t = (-B - Ds) / A;
		//Check if t's are in interval
		if (t < tmin || t > tmax)
		{
			t = (-B + Ds) / A; //if not check other t
			if (t < tmin || t > tmax)
				return false; //not hit
		}

		record.tValue = t;
		record.hitPoint = ray.PointAtParameter(t);
		record.normal = (record.hitPoint - origin) / radius;
		record.pMaterial = pMaterial;
		return true;
	}

	float Sphere::PDFValue(const Elite::FPoint3& _origin, const Elite::FVector3& direction) const
	{
		HitRecord record{};
		if (Hit(record, Ray(_origin, direction), 0.01f, FLT_MAX))
		{
			float area = static_cast<float>(E_PI_4) * radius * radius;
			float distanceSq = record.tValue * record.tValue * SqrMagnitude(direction);
			float cosine = fabs(Elite::Dot(direction, record.normal) / Magnitude(direction));
			return distanceSq / (cosine * area);
		}
		return 0.f;
	}

	Elite::FVector3 Sphere::Random(const Elite::FPoint3& _origin) const
	{
		Elite::FPoint3 point = origin + FVector3(RandomPointOnUnitSphereSphericalCoordinates());
		return point - _origin;
	}

	bool Plane::Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const
	{
		//Check if we hit the plane where the triangle is situated in
		const float dotLookNormal{ Elite::Dot(ray.direction, normal) };

		switch (cullMode)
		{
		case CullMode::backCulling:
			//If positive we are looking at the back
			if (dotLookNormal < 0.f)
				break;
			else
				return false;
		case CullMode::frontCulling:
			//If negative then we are looking to the front
			if (dotLookNormal > 0.f)
				break;
			else
				return false;
		case CullMode::noCulling:
			if (Elite::AreEqual(dotLookNormal, 0.f))
				return false;
			break;
		default:
			break;
		}

		const float t = Elite::Dot((origin - ray.origin), normal) / dotLookNormal;

		//Check if t is in interval of ray
		if (t < ray.tMin || t > ray.tMax)
			return false;

		if (record.tValue < t)
			return true;

		//Fill in hitrecord
		record.tValue = t;
		record.hitPoint = ray.origin + t * ray.direction;
		record.normal = normal;
		record.pMaterial = pMaterial;

		return true;
	}

	Rectangle::Rectangle(std::array<Elite::FPoint3, 4>&& _corners, Materials::BaseMaterial* _pMaterial, CullMode _cullMode)
		: BaseObject{ _corners[0], _pMaterial }, corners{ std::move(_corners) }, cullMode{_cullMode}
	{
		//calculate normal from points > they are given in counterclockwise
		Elite::FVector3 direction = Elite::Cross(_corners[1] - _corners[0], _corners[2] - _corners[0]);
		normal = Elite::GetNormalized(direction);
	}
	bool Rectangle::Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const
	{
		//Check if we hit the plane where the triangle is situated in
		const float dotLookNormal{ Elite::Dot(ray.direction, normal) };

		switch (cullMode)
		{
		case CullMode::backCulling:
			//If positive we are looking at the back
			if (dotLookNormal < 0.f)
				break;
			else
				return false;
		case CullMode::frontCulling:
			//If negative then we are looking to the front
			if (dotLookNormal > 0.f)
				break;
			else
				return false;
		case CullMode::noCulling:
			if (Elite::AreEqual(dotLookNormal, 0.f))
				return false;
			break;
		default:
			break;
		}

		const float t = Elite::Dot((origin - ray.origin), normal) / dotLookNormal;

		//Check if t is in interval of ray
		if (t < ray.tMin || t > ray.tMax)
			return false;

		if (record.tValue < t)
			return true;

		//Must be within the range of our ray
		Elite::FPoint3 hitPoint = ray.origin + (t * ray.direction);

		//Check if hitpoint is on the right side of the line
		//If this is true for all the 3 edges of the triangle than the point is condisered to be into the triangle
		Elite::FVector3 edge{ corners[1] - corners[0]};
		Elite::FVector3 sideToPoint{ hitPoint - corners[0]};

		if (Elite::Dot(normal, Elite::Cross(edge, sideToPoint)) < 0)
			return false;

		edge = corners[2] - corners[1];
		sideToPoint = hitPoint - corners[1];
		if (Elite::Dot(normal, Elite::Cross(edge, sideToPoint)) < 0)
			return false;

		edge = corners[3] - corners[2];
		sideToPoint = hitPoint - corners[2];
		if (Elite::Dot(normal, Elite::Cross(edge, sideToPoint)) < 0)
			return false;

		edge = corners[0] - corners[3];
		sideToPoint = hitPoint - corners[3];
		if (Elite::Dot(normal, Elite::Cross(edge, sideToPoint)) < 0)
			return false;

		//Fill in hitrecord
		record.tValue = t;
		record.hitPoint = ray.origin + t * ray.direction;
		record.normal = normal;
		record.pMaterial = pMaterial;

		return true;
	}
	float Rectangle::PDFValue(const Elite::FPoint3& origin, const Elite::FVector3& direction) const
	{
		HitRecord record{};
		if(Hit(record, Ray(origin, direction), 0.01f, FLT_MAX))
		{
			float area = AreaOfRectangle(corners);
			float distanceSq = record.tValue * record.tValue * SqrMagnitude(direction);
			float cosine = fabs(Elite::Dot(direction, record.normal) / Magnitude(direction));
			return distanceSq / (cosine * area);
		}
		return 0.0f;
	}
	Elite::FVector3 Rectangle::Random(const Elite::FPoint3& _origin) const
	{
		FPoint3 point = RandomPointInRectangle(corners);
		return point - _origin;
	}
}



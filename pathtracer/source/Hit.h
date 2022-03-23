// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Ray.h"

enum class CullMode
{
	//culling == removing/ reduction
	backFace,
	frontFace, // we don't want to render the front of the triangle
	noCulling
};

namespace Hit
{
	inline bool PlaneHit(const Ray& ray, const Elite::FVector3& normal, const Elite::FPoint3& origin, float& tValue, CullMode cullMode, bool shadow)
	{
		//Check if we hit the plane where the triangle is situated in
		float dotLookNormal{ Elite::Dot(ray.direction, normal) };

		if (shadow)
			dotLookNormal = -dotLookNormal;

		switch (cullMode)
		{
		case CullMode::backFace:
			//If positive we are looking at the back
			if (dotLookNormal < 0.f)
				break;
			else
				return false;
		case CullMode::frontFace:
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

		if (shadow)
			dotLookNormal = -dotLookNormal;

		tValue = Elite::Dot((origin - ray.origin), normal) / dotLookNormal;
		return true;
	}
	inline bool SphereHitAnalytic(const Ray& ray, const Elite::FPoint3& origin, const float radius, float& tValue)
	{
		//Calculate discriminant
		Elite::FVector3 rp{ ray.origin - origin };
		float A{ Elite::Dot(ray.direction, ray.direction) };
		float B{ 2.f * Elite::Dot(rp, ray.direction) };
		float C{ Elite::Dot(rp,rp) - (radius * radius) };

		float D{ B * B - 4 * A * C };

		if (D < 0 || Elite::AreEqual(D, 0.f)) //Only interested when the ray has 2 intersection points with sphere
			return false;

		//float Ds{ sqrtf(D) };
		////Find t: length of line between origin ray and hit point sphere
		////Use substraction, except when t < ray.tMin
		//tValue = (-B - Ds) / 2 * A;

		//if (tValue < ray.tMin)
		//{
		//	tValue = (-B + Ds) / 2 * A;
		//}
		return true;
	}
	inline bool SphereHitGeometric(const Ray& ray, const Elite::FPoint3& origin, const float radius, float& tValue)
	{
		Elite::FVector3 reject{ Elite::Reject(((origin - ray.origin)), ray.direction) };
		float od2{ Elite::SqrMagnitude(reject) };
		float r2{ radius * radius };

		// Only interested when the ray has 2 intersection points
		if (od2 > r2 || Elite::AreEqual(od2, r2))
			return false;

		float tca{ Elite::Dot(((origin - ray.origin)), ray.direction) };
		float thc{ sqrtf(r2 - od2) };
		tValue = tca - thc;

		//Check if t's are in interval
		if (tValue < ray.tMin || tValue > ray.tMax)
		{
			tValue = tca + thc;
		}
		return true;
	}
	inline bool TriangleHit(const Ray& ray, const Elite::FVector3& normal, const Elite::FPoint3& center, const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2, float& tValue, CullMode cullMode, bool shadow)
	{
		if (!Hit::PlaneHit(ray, normal, center, tValue, cullMode, shadow))
			return false;

		if (tValue < ray.tMin || tValue > ray.tMax)
			return false;

		//Must be within the range of our ray
		Elite::FPoint3 hitPoint = ray.origin + (tValue * ray.direction);

		//Check if hitpoint is on the right side of the line
		//If this is true for all the 3 edges of the triangle than the point is condisered to be into the triangle
		Elite::FVector3 edge{ v1 - v0 };
		Elite::FVector3 sideToPoint{ hitPoint - v0 };

		if (Elite::Dot(normal, Elite::Cross(edge, sideToPoint)) < 0)
			return false;

		edge = v2 - v1;
		sideToPoint = hitPoint - v1;
		if (Elite::Dot(normal, Elite::Cross(edge, sideToPoint)) < 0)
			return false;

		edge = v0 - v2;
		sideToPoint = hitPoint - v2;
		if (Elite::Dot(normal, Elite::Cross(edge, sideToPoint)) < 0)
			return false;

		return true;
	}
}
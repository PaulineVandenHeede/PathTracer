//3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#include "pch.h"
#include "Objects.h"
#include "HitRecord.h"

namespace Objects
{
	bool Sphere::Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const
	{
		//Calculate discriminant
		Elite::FVector3 rp{ ray.origin - center };
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
		record.normal = (record.hitPoint - center) / radius;
		record.pMaterial = pMaterial;
		return true;
	}

}



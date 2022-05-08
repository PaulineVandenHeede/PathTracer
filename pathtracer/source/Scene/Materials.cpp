//3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#include "Materials.h"

//Framework includes
#include "EMath.h"

//Project includes
#include "HitRecord.h"
#include "Ray.h"

namespace Materials
{
	//LAMBERTIAN MATERIAL
	Lambertian::Lambertian(const Elite::RGBColor& color)
		: albedoColor{ color }
	{
	}

	bool Lambertian::Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatteredRay) const
	{
		Elite::FVector3 target = static_cast<Elite::FVector3>(record.hitPoint) + record.normal + static_cast<Elite::FVector3>(Elite::RandomPointInUnitSphere());
		scatteredRay = Ray(record.hitPoint, target - static_cast<Elite::FVector3>(record.hitPoint));
		attenuation = albedoColor;
		return true;
	}


}
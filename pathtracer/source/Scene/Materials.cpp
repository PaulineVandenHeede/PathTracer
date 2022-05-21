//3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#include "Materials.h"

//Framework includes
#include "EMath.h"

//Project includes
#include "HitRecord.h"
#include "Ray.h"

namespace Materials
{
	bool BaseMaterial::Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatterRay, float& pdf) const
	{
		return false;
	}

	float BaseMaterial::ScatterPDF(const Ray& inRay, const HitRecord& record, const Ray& scatterRay) const
	{
		return 0.f;
	}

	const Elite::RGBColor& BaseMaterial::Emit() const
	{
		return Elite::RGBColor{ 0.f, 0.f, 0.f };
	}


	//LAMBERTIAN MATERIAL
	Lambertian::Lambertian(const Elite::RGBColor& color)
		: albedoColor{ color }
	{
	}

	bool Lambertian::Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatteredRay, float& pdf) const
	{
		Elite::FVector3 target = static_cast<Elite::FVector3>(record.hitPoint) + record.normal + static_cast<Elite::FVector3>(Elite::RandomPointInUnitSphere());
		scatteredRay = Ray(record.hitPoint, GetNormalized(target - static_cast<Elite::FVector3>(record.hitPoint)));
		attenuation = albedoColor;
		pdf = Elite::Dot(record.normal, scatteredRay.direction) / E_PI;
		return true;
	}
	float Lambertian::ScatterPDF(const Ray& inRay, const HitRecord& record, const Ray& scatterRay)
	{
		std::array<Elite::FVector3, 3> onb = BuildONBFromW(record.normal);
		float cosine = Elite::Dot(record.normal, GetNormalized(scatterRay.direction));
		cosine = Elite::Clamp(cosine, 0.f, FLT_MAX);
		return cosine / static_cast<float>(E_PI);
	}




	DiffuseLight::DiffuseLight(const Elite::RGBColor& color)
		: lightColour{ color }
	{
	}
	
	const Elite::RGBColor& DiffuseLight::Emit() const
	{
		return lightColour; //Doesn't light lose colour?
	}



}
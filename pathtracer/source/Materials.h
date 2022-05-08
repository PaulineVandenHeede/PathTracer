#pragma once
#include "ERGBColor.h"

struct Ray;
struct HitRecord;


namespace Materials
{
	struct BaseMaterial
	{
		BaseMaterial() = default;
		virtual ~BaseMaterial() = default;

		virtual bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatterRay) const = 0; //pure virtual
	};

	struct Lambertian final : public BaseMaterial
	{
		Lambertian(const Elite::RGBColor& color);
		virtual ~Lambertian() override = default;

		virtual bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatteredRay) const override;

	private:
		Elite::RGBColor albedoColor;
	};
}


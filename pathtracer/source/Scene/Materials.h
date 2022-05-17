//3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#pragma once
#include "ERGBColor.h"
#include "EMath.h"

struct Ray;
struct HitRecord;


namespace Materials
{
	struct BaseMaterial
	{
		BaseMaterial() = default;
		virtual ~BaseMaterial() = default;

		virtual bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatterRay) const = 0; //pure virtual
		virtual const Elite::RGBColor& Emit() const;
	};

	struct Lambertian final : public BaseMaterial
	{
		Lambertian(const Elite::RGBColor& color);
		virtual ~Lambertian() override = default;

		virtual bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatteredRay) const override;

	private:
		Elite::RGBColor albedoColor;
	};

	struct DiffuseLight final : public BaseMaterial
	{
	public:
		DiffuseLight(const Elite::RGBColor& color);
		virtual ~DiffuseLight() override = default;

		virtual bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatteredRay) const override;
		virtual const Elite::RGBColor& Emit() const override;

	private:
		Elite::RGBColor lightColour;
	};
}


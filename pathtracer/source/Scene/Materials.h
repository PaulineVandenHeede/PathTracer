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

		virtual bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation) const;
		virtual float PDF(const Ray& inRay, const HitRecord& record, const Ray& scatterRay) const;
		virtual Elite::RGBColor Emit(const Ray& ray, const HitRecord& record) const;
	};

	struct Lambertian final : public BaseMaterial
	{
		Lambertian(const Elite::RGBColor& color);
		virtual ~Lambertian() override = default;

		bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation) const override;
		float PDF(const Ray& inRay, const HitRecord& record, const Ray& scatterRay) const override;
	private:
		Elite::RGBColor albedoColor;
	};

	struct DiffuseLight final : public BaseMaterial
	{
	public:
		DiffuseLight(const Elite::RGBColor& color);
		virtual ~DiffuseLight() override = default;

		virtual Elite::RGBColor Emit(const Ray& ray, const HitRecord& record) const override;

	private:
		Elite::RGBColor lightColour;
	};
}


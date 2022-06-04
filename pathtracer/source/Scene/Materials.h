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

		virtual bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatterRay, float& pdf) const;
		virtual float ScatterPDF(const Ray& inRay, const HitRecord& record, const Ray& scatterRay) const;
		virtual Elite::RGBColor Emit(const Ray& ray, const HitRecord& record) const;
	};

	struct Lambertian final : public BaseMaterial
	{
		Lambertian(const Elite::RGBColor& color);
		virtual ~Lambertian() override = default;

		bool Scatter(const Ray& inRay, const HitRecord& record, Elite::RGBColor& attenuation, Ray& scatteredRay, float& pdf) const override;
		float ScatterPDF(const Ray& inRay, const HitRecord& record, const Ray& scatterRay) const override;
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


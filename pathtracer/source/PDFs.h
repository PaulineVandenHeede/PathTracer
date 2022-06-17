#pragma once
#include "EMath.h"
#include "Objects.h"

namespace pdf
{
	class PDF
	{
	public:
		PDF() = default;

		virtual float Value(const Elite::FVector3& direction) const = 0;
		virtual Elite::FVector3 Generate() const = 0;
	};

	class CosineDensity final : public PDF
	{
	public:
		CosineDensity(const Elite::FVector3& normal);

		float Value(const Elite::FVector3& direction) const override;
		Elite::FVector3 Generate() const override;

	private:
		std::array<Elite::FVector3, 3> onb;
	};

	class LightDensity final : public PDF
	{
	public:
		LightDensity(const Objects::BaseObject* _pObject, const Elite::FPoint3& _origin);

		float Value(const Elite::FVector3& direction) const override;
		Elite::FVector3 Generate() const override;
	private:
		const Objects::BaseObject* pObject;
		Elite::FPoint3 origin;
	};
}
#include "PDFs.h"

pdf::CosineDensity::CosineDensity(const Elite::FVector3& normal)
{
	onb = BuildONBFromW(normal);
}

float pdf::CosineDensity::Value(const Elite::FVector3& direction) const
{
	const float cosine = Elite::Dot(GetNormalized(direction), onb[2]);
	if (cosine > 0.f)
		return cosine / static_cast<float>(E_PI);
	else
		return 0.f;
}

Elite::FVector3 pdf::CosineDensity::Generate() const
{
	return GetLocalFromONB(onb, Elite::RandomCosineDirection());
}

pdf::LightDensity::LightDensity(const Objects::BaseObject* _pObject, const Elite::FPoint3& _origin)
	: pObject{ _pObject }
	, origin{ _origin }
{
}

float pdf::LightDensity::Value(const Elite::FVector3& direction) const
{
	return pObject->PDFValue(origin, direction);
}

Elite::FVector3 pdf::LightDensity::Generate() const
{
	return pObject->Random(origin);
}

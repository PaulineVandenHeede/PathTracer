// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Material.h"

Material::Material(const Elite::RGBColor& colour, const float diffuseReflectance)
	: m_DiffuseColour{ colour }
	, m_DiffuseReflectance{ diffuseReflectance }
{
}

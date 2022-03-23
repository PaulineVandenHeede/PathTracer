// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Object.h"

Object::Object(const Elite::FPoint3& origin, const MaterialName materialName)
	: m_Origin{ origin }
	, m_MaterialName{ materialName }
{
}


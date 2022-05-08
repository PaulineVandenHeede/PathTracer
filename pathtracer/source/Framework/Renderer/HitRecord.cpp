// 2DAE07 - Vanden Heede, Pauline
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#include "pch.h"
#include "HitRecord.h"

using namespace Elite;

HitRecord::HitRecord()
	: normal{  }
	, hitPoint{  }
	, tValue{ FLT_MAX }
	, pMaterial{ nullptr }
{
}
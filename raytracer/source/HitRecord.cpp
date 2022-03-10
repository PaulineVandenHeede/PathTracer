// 2DAE07 - Vanden Heede, Pauline
#include "pch.h"
#include "HitRecord.h"

using namespace Elite;

HitRecord::HitRecord()
	: materialName{  }
	, renderColour{  }
	, normal{  }
	, hitPoint{  }
	, tValue{ FLT_MAX }
{
}
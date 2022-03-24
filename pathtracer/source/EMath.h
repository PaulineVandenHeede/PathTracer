/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EMath.h: General Math header that includes all math types and utilities
/*=============================================================================*/
#ifndef ELITE_MATH
#define ELITE_MATH

/* --- STANDARD --- */
#include <math.h>
#include <cassert>
#include <random>
/* --- UTILITIES --- */
#include "EMathUtilities.h"
/* --- TYPES --- */
#include "EVector.h"
#include "EVector2.h"
#include "EVector3.h"
#include "EVector4.h"
#include "EPoint.h"
#include "EPoint2.h"
#include "EPoint3.h"
#include "EPoint4.h"
#include "EMatrix.h"
#include "EMatrix2.h"
#include "EMatrix3.h"
#include "EMatrix4.h"

namespace Elite
{
	/* --- TYPE DEFINES --- */
	typedef Vector<2, float>	FVector2;
	typedef Vector<2, double>	DVector2;
	typedef Vector<2, int>		IVector2;
	typedef Vector<3, float>	FVector3;
	typedef Vector<3, double>	DVector3;
	typedef Vector<3, int>		IVector3;
	typedef Vector<4, float>	FVector4;
	typedef Vector<4, double>	DVector4;
	typedef Vector<4, int>		IVector4;

	typedef Point<2, float>		FPoint2;
	typedef Point<2, double>	DPoint2;
	typedef Point<2, int>		IPoint2;
	typedef Point<3, float>		FPoint3;
	typedef Point<3, double>	DPoint3;
	typedef Point<3, int>		IPoint3;
	typedef Point<4, float>		FPoint4;
	typedef Point<4, double>	DPoint4;
	typedef Point<4, int>		IPoint4;

	typedef Matrix<2, 2, float>		FMatrix2;
	typedef Matrix<2, 2, double>	DMatrix2;
	typedef Matrix<3, 3, float>		FMatrix3;
	typedef Matrix<3, 3, double>	DMatrix3;
	typedef Matrix<4, 4, float>		FMatrix4;
	typedef Matrix<4, 4, double>	DMatrix4;


	/*!Random point in unit sphere*/
	inline FPoint3 RandomPointInUnitSphere()
	{
		std::mt19937 gen((std::random_device())());
		FVector3 point{};
		do {
			float x = std::generate_canonical<float, 10>(gen);
			float y = std::generate_canonical<float, 10>(gen);
			float z = std::generate_canonical<float, 10>(gen);
			point = 2.f * FVector3(x, y, z) - FVector3(1.f, 1.f, 1.f);
		} while (SqrMagnitude(point) >= 1.0f);
		return static_cast<FPoint3>(point);
	}
}
#endif

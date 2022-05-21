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
#include <array>
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

	inline FPoint3 RandomPointInUnitDisk()
	{
		std::mt19937 gen((std::random_device())());
		FVector3 point{};
		do {
			float x = std::generate_canonical<float, 10>(gen);
			float y = std::generate_canonical<float, 10>(gen);
			point = 2.f * FVector3(x, y, 0.f) - FVector3(1.f, 1.f, 0.f);
		} while (SqrMagnitude(point) >= 1.0f);
		return static_cast<FPoint3>(point);
	}

	inline float RandomFloatCanonical()
	{
		std::mt19937 gen((std::random_device())());
		return std::generate_canonical<float, 10>(gen);
	}

	inline Elite::FVector3 RandomCosineDirection()
	{
		std::mt19937 gen((std::random_device())());
		float r1 = std::generate_canonical<float, 10>(gen);
		float r2 = std::generate_canonical<float, 10>(gen);
		float phi = 2 * static_cast<float>(E_PI) * r1;
		float x = std::cosf(phi) * 2.f * Elite::Square(r2);
		float y = std::sinf(phi) * 2.f * Elite::Square(r1);
		float z = Elite::Square(1 - r2);
		return { x, y, z };
	}

	inline std::array<Elite::FVector3, 3> BuildONBFromW(const Elite::FVector3& normal)
	{
		std::array<Elite::FVector3, 3> ONB{};
		ONB[2] = GetNormalized(normal);
		Elite::FVector3 a{};
		if(std::fabs(ONB[2].x) > 0.9f)
			a = Elite::FVector3{ 0.f, 1.f, 0.f };
		else
			a = Elite::FVector3{ 1.f, 0.f, 0.f };

		ONB[1] = GetNormalized(Elite::Cross(ONB[2], a));
		ONB[0] = Elite::Cross(ONB[2], ONB[1]);
	}
	inline Elite::FVector3 GetLocalFromONB(const std::array<Elite::FVector3, 3>& onb, const Elite::FVector3& direction)
	{
		return direction.x * onb[0] + direction.y * onb[1] + direction.z * onb[2];
	}
}
#endif

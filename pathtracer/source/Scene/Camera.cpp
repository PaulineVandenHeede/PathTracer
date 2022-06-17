// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#include "pch.h"
#include "Camera.h"
#include "SDL.h"

#include <iostream>

//TEMP
Camera::Camera()
	: lowerLeftCorner { -2.0f, -1.0f, -1.0f }
	, horizontal{ 4.f, 0.f, 0.f }
	, vertical{ 0.f, 2.f, 0.f }
	, origin{ 0.f, 0.f, 0.f }
{
}

Camera::Camera(const float fov, const float aspectRatio)
{
	//fov is in degrees
	const float theta = fov * float(M_PI) / 180; //to radians
	const float halfHeight = tanf(theta / 2.f);
	const float halfWidth = aspectRatio * halfHeight;
	lowerLeftCorner = { -halfWidth, -halfHeight, -1.f };
	horizontal = { 2 * halfWidth, 0.f, 0.f };
	vertical = { 0.f, 2 * halfHeight, 0.f };
	origin = { 0.f,0.f,0.f };
}

Camera::Camera(const Elite::FPoint3& position, const Elite::FVector3& lookAt, const Elite::FVector3& up, float fov, float aspectRatio)
{
	//fov is in degrees
	const float theta = fov * float(M_PI) / 180; //to radians
	const float halfHeight = tanf(theta / 2.f);
	const float halfWidth = aspectRatio * halfHeight;
	origin = position;

	w = Elite::GetNormalized(static_cast<Elite::FVector3>(position) - lookAt);
	u = Elite::GetNormalized(Elite::Cross(up, w));
	v = Elite::Cross(w, u);

	lowerLeftCorner = static_cast<Elite::FVector3>(origin) - halfWidth * u - halfHeight * v - w;
	horizontal = 2 * halfWidth * u;
	vertical = 2 * halfHeight * v;
}

Camera::Camera(const Elite::FPoint3& position, const Elite::FVector3& lookAt, const Elite::FVector3& up, float fov, float aspectRatio, float aperture, float focusDist)
{
	/*time0 = t0;
	time1 = t1;*/
	focalLength = aperture / 2.f;

	const float theta = fov * float(M_PI) / 180; //to radians
	const float halfHeight = tanf(theta / 2.f);
	const float halfWidth = aspectRatio * halfHeight;
	origin = position;

	w = Elite::GetNormalized(static_cast<Elite::FVector3>(position) - lookAt);
	u = Elite::GetNormalized(Elite::Cross(up, w));
	v = Elite::Cross(w, u);

	lowerLeftCorner = static_cast<Elite::FVector3>(origin) - halfWidth * focusDist * u - halfHeight * focusDist * v - w * focusDist;
	horizontal = 2 * halfWidth * focusDist * u;
	vertical = 2 * halfHeight * focusDist * v;
}



Ray Camera::GetRayFocus(float x, float y) const
{
	FVector3 randomDirection = focalLength * static_cast<FVector3>(RandomPointInUnitDiskPolarCoordinates());
	FVector3 offset = u * randomDirection.x + v * randomDirection.y;
	//float time = time0 + RandomFloatCanonical() * (time1 - time0);
	return Ray(origin + offset, lowerLeftCorner + x * horizontal + y * vertical - static_cast<FVector3>(origin) - offset);
}




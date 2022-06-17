// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#pragma once
#include "EMath.h"
#include "Ray.h"

class Camera
{
public:
	Camera(); //TEMP
	Camera(const float fov, const float aspectRatio);
	Camera(const Elite::FPoint3& position, const Elite::FVector3& lookAt, const Elite::FVector3& up, float fov, float aspectRatio);
	Camera(const Elite::FPoint3& position, const Elite::FVector3& lookAt, const Elite::FVector3& up, float fov, float aspectRatio, float aperture, float focusDist/*, float t0, float t1*/);

	Ray GetRayFocus(float u, float y) const;
private:
	//Datamembers
	Elite::FVector3 lowerLeftCorner{ -2.0f, -1.0f, -1.0f };
	Elite::FVector3 horizontal{ 4.f, 0.f, 0.f };
	Elite::FVector3 vertical{ 0.f, 2.f, 0.f };
	Elite::FPoint3 origin{ 0.f, 0.f, 0.f };

	Elite::FVector3 u, v, w;
	float focalLength;
};


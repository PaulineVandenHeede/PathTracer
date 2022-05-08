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
	Camera(const Elite::FPoint3& position,const Elite::FVector3& forward, const float angle, const uint32_t screenWidth, const uint32_t screenHeight);

	const Elite::FPoint3& GetCameraCoordinates() const;
	Elite::FPoint3 CalculateWorldCoordinates(const uint32_t c, const uint32_t r);

	void CalculateLookAtMatrix();
	bool UpdateCamera(const float elapsedSec);

	//TEMP
	Ray GetRay(float u, float v) const { return Ray{ origin, lowerLeftCorner + u * horizontal + v * vertical - static_cast<Elite::FVector3>(origin) }; }
private:
	//Datamembers
	Elite::FMatrix4 m_LookAt;
	
	Elite::FVector3 m_Forward;
	Elite::FVector3 m_Up;
	Elite::FVector3 m_Right;

	Elite::FPoint3 m_Position;
	
	float m_FOV;
	float m_AspectRatio;
	float m_Distance; //s

	uint32_t m_ScreenWidth;
	uint32_t m_ScreenHeight;

	float m_DirtyAngle;


	//TEMP
	Elite::FVector3 lowerLeftCorner{ -2.0f, -1.0f, -1.0f };
	Elite::FVector3 horizontal{ 4.f, 0.f, 0.f };
	Elite::FVector3 vertical{ 0.f, 2.f, 0.f };
	Elite::FPoint3 origin{ 0.f, 0.f, 0.f };
};


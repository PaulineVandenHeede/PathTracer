// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "EMath.h"

class Camera
{
public:
	Camera(const Elite::FPoint3& position,const Elite::FVector3& forward, const float angle, const uint32_t screenWidth, const uint32_t screenHeight);

	const Elite::FPoint3& GetCameraCoordinates() const;
	Elite::FPoint3 CalculateWorldCoordinates(const uint32_t c, const uint32_t r);

	void CalculateLookAtMatrix();
	bool UpdateCamera(const float elapsedSec);

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
};


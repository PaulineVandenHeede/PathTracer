// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
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

	Elite::FVector3 w = Elite::GetNormalized(static_cast<Elite::FVector3>(position) - lookAt);
	Elite::FVector3 u = Elite::GetNormalized(Elite::Cross(up, w));
	Elite::FVector3 v = Elite::Cross(w, u);

	lowerLeftCorner = static_cast<Elite::FVector3>(origin) - halfWidth * u - halfHeight * v - w;
	horizontal = 2 * halfWidth * u;
	vertical = 2 * halfHeight * v;
}

Camera::Camera(const Elite::FPoint3& position, const Elite::FVector3& forward, const float angle, const uint32_t screenWidth, const uint32_t screenHeight)
	: m_LookAt{ Elite::FMatrix4::Identity() }
	, m_Forward{ forward }
	, m_Up{ Elite::FVector3::ZeroVector() }
	, m_Right{ Elite::FVector3::ZeroVector() }
	, m_Position{ position }
	, m_FOV{ tanf(Elite::ToRadians(angle)/ 2.f) }
	, m_AspectRatio{ float(screenWidth) / screenHeight }
	, m_Distance{ -1 }
	, m_ScreenWidth{ screenWidth }
	, m_ScreenHeight{ screenHeight }
	, m_DirtyAngle{ 0.f }
{
	Elite::FVector3 worldUp{ 0, 1, 0 };

	m_Right = Cross(worldUp, m_Forward);
	if (m_Right == Elite::FVector3::ZeroVector())
		m_Right = Elite::FVector3{ 0, 0, 1 };
	Elite::Normalize(m_Right);
	m_Up = Cross(m_Forward, m_Right);
	Elite::Normalize(m_Up);

	CalculateLookAtMatrix();
}

const Elite::FPoint3& Camera::GetCameraCoordinates() const
{
	return m_Position;
}

Elite::FPoint3 Camera::CalculateWorldCoordinates(uint32_t c, uint32_t r)
{
	float x = ((2 * (c + 0.5f) / m_ScreenWidth) - 1) * m_AspectRatio * m_FOV;
	float y = (1 - (2 * (r + 0.5f) / m_ScreenHeight)) * m_FOV;

	Elite::FPoint4 pointWorldSpace{ x, y, m_Distance, 1 };
	pointWorldSpace = (m_LookAt * pointWorldSpace);

	return Elite::FPoint3{ pointWorldSpace.x, pointWorldSpace.y, pointWorldSpace.z };
}

void Camera::CalculateLookAtMatrix()
{
	//Saved: column based --> we work with row based
	m_LookAt = Elite::FMatrix4{ 
		static_cast<Elite::FVector4>(m_Right), 
		static_cast<Elite::FVector4>(m_Up), 
		static_cast<Elite::FVector4>(m_Forward),
		static_cast<Elite::FVector4>(m_Position) };
}
bool Camera::UpdateCamera(const float elapsedSec)
{
	bool didItUpdate{ false };
	Elite::IVector2 displacement{};
	uint32_t mouseState = SDL_GetRelativeMouseState(&displacement.x, &displacement.y);

	/*if (m_DirtyAngle < 360.f)
	{
		m_DirtyAngle += 1.f;
		m_Forward = Elite::MakeRotationX(Elite::ToRadians(1.f)) * m_Forward;
		std::cout << m_DirtyAngle << std::endl;
		didItUpdate = true;
	}*/

	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) && mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) //First check this because else one of the next statements will also be right so if won't go in the if statement then
	{
		m_Position += (m_Right * (elapsedSec * displacement.x));
		m_Position += (m_Up * (elapsedSec * displacement.y));
		didItUpdate = true;
	}
	else if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		m_Forward = Elite::MakeRotationZYX(Elite::ToRadians(displacement.y * elapsedSec), Elite::ToRadians(displacement.x * elapsedSec), 0.f) * m_Forward;
		didItUpdate = true;
	}
	else if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_Position.z += elapsedSec * displacement.y;
		m_Forward = Elite::MakeRotationY(Elite::ToRadians(displacement.x * elapsedSec)) * m_Forward;
		didItUpdate = true;
	}
	
	return didItUpdate;
}




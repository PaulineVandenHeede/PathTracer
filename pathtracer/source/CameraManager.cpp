// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "CameraManager.h"
#include "Camera.h"
#include "SDL.h"
#include <algorithm>


CameraManager::CameraManager()
	: m_IDActiveCamera{ 0 }
	, m_Timer{ 0.f }
	, m_MaxTimer{ 0.1f }
{
}

CameraManager::~CameraManager()
{
	std::for_each(m_pCameras.begin(), m_pCameras.end(), [](std::pair<unsigned int, Camera*> cameraPair) {
		delete cameraPair.second;
		cameraPair.second = nullptr;
		});
	m_pCameras.clear();
}

void CameraManager::AddCamera(Camera* pCamera)
{
	if (m_pCameras.find(m_IDActiveCamera + 1) != m_pCameras.cend())
		return;

	++m_IDActiveCamera;
	m_pCameras.emplace(m_IDActiveCamera, pCamera);
}

void CameraManager::HandleUserInput(const uint8_t* pKeyboardStates, const float elapsedSec)
{
	m_Timer += elapsedSec;
	//Toggle between cameras in the scene
	if (pKeyboardStates[SDL_SCANCODE_C])
	{
		if (m_Timer > m_MaxTimer)
		{
			(m_IDActiveCamera %= m_pCameras.size())++; //++ at the end because else you will have the wrong ID
			m_Timer = 0.f;
		}
	}
}


Camera* CameraManager::GetActiveCamera() const
{
	std::unordered_map<unsigned int, Camera*>::const_iterator search{ m_pCameras.find(m_IDActiveCamera) };
	if (search != m_pCameras.cend())
		return search->second;
	else
		return nullptr;

	/*try
	{
		return m_pCameras.at(m_IDActiveCamera);
	}
	catch (const std::exception & e)
	{
		return nullptr;
	}*/
}

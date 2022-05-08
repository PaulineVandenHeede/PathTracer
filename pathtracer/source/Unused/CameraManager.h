// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include <unordered_map>
#include "EMath.h"

class Camera;

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	//Rule of 5 - > we don't want two camera managers
	CameraManager(const CameraManager&) = delete;
	CameraManager(CameraManager&&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;
	CameraManager& operator=(CameraManager&&) = delete;

	void AddCamera(Camera* pCamera);
	void HandleUserInput(const uint8_t* pKeyboardStates, const float elapsedSec);
	Camera* GetActiveCamera() const;

private:
	//Datamembers
	unsigned int m_IDActiveCamera;
	float m_Timer;
	float m_MaxTimer;
	std::unordered_map<unsigned int, Camera*> m_pCameras;
};


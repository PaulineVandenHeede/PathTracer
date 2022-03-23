// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Camera.h"
#include "SDL.h"

#include "Objects.h"

Scene::~Scene()
{
	for (Object* pObject : m_pObjects)
	{
		delete pObject;
		pObject = nullptr;
	}
	m_pObjects.clear();

	for (Objects::BaseObject* pObject : m_pSceneObjects)
	{
		delete pObject;
		pObject = nullptr;
	}
	m_pSceneObjects.clear();
}

void Scene::AddObject(Object* pObject)
{
	m_pObjects.push_back(pObject);
}

void Scene::AddObjectToScene(Objects::BaseObject* pObject)
{
	m_pSceneObjects.push_back(pObject);
}

void Scene::AddLight(Light* pLight)
{
	m_LightManager.AddLight(pLight);
}

void Scene::AddCamera(Camera* pCamera)
{
	m_CameraManager.AddCamera(pCamera);
}

void Scene::Update(const float elapsedSec)
{
	for (Object* pObject : m_pObjects)
	{
		pObject->Update(elapsedSec);
	}

	if (m_CameraManager.GetActiveCamera()->UpdateCamera(elapsedSec))
		m_CameraManager.GetActiveCamera()->CalculateLookAtMatrix();
}

void Scene::HandleUserInput(const uint8_t* pKeyboardStates, const float elapsedSec)
{
	m_CameraManager.HandleUserInput(pKeyboardStates, elapsedSec);
	m_LightManager.HandleUserInput(pKeyboardStates, elapsedSec);
}

bool Scene::Hit(const Ray& ray, HitRecord& hitRecord, bool shadow)
{
	bool hit{ false };
	for (Object* pObject : m_pObjects)
	{
		if (pObject->Hit(ray, hitRecord, shadow))
		{
			hit = true;
		}
	}
	return hit;
}

bool Scene::Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const
{
	bool hitAnything = false;
	float closestSoFar = tmax;
	HitRecord temp{};
	uint32_t size = static_cast<uint32_t>(m_pSceneObjects.size());
	for (uint32_t i{ 0 }; i < size; ++i)
	{
		if (m_pSceneObjects[i]->Hit(temp, ray, tmin, closestSoFar))
		{
			hitAnything = true;
			closestSoFar = temp.tValue;
			record = temp;
		}
	}

	return hitAnything;
}

bool Scene::validCamera()
{
	return (m_CameraManager.GetActiveCamera() != nullptr);
}

const Elite::FPoint3& Scene::GetActiveCameraCoordinates() const
{
	return m_CameraManager.GetActiveCamera()->GetCameraCoordinates();
}

Elite::FPoint3 Scene::CalculateWorldCoordinates(uint32_t c, uint32_t r)
{
	return m_CameraManager.GetActiveCamera()->CalculateWorldCoordinates(c, r);
}

void Scene::CalculateBiradiance(const Ray& ray, HitRecord& hitRecord)
{
	m_LightManager.CalculateBiradianceOfLights(ray, hitRecord);
}

void Scene::InitialiseGroupLights()
{
	m_LightManager.InitialiseGroup();
}

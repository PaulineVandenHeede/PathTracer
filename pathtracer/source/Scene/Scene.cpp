// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021-2022
#include "pch.h"

#include "Scene.h"
#include "Camera.h"

#include "Objects.h"
#include "HitRecord.h"
#include "Ray.h"

Scene::~Scene()
{
	/*for (Object* pObject : m_pObjects)
	{
		delete pObject;
		pObject = nullptr;
	}
	m_pObjects.clear();*/

	for (Objects::BaseObject* pObject : m_pSceneObjects)
	{
		delete pObject;
		pObject = nullptr;
	}
	m_pSceneObjects.clear();

	SafeDelete(m_pCamera);
}


void Scene::AddObjectToScene(Objects::BaseObject* pObject)
{
	m_pSceneObjects.push_back(pObject);
}


void Scene::AddCamera(Camera* pCamera)
{
	m_pCamera = pCamera;
}

void Scene::Update(const float elapsedSec)
{
	/*for (Object* pObject : m_pObjects)
	{
		pObject->Update(elapsedSec);
	}*/

	//if (m_CameraManager.GetActiveCamera()->UpdateCamera(elapsedSec))
		//m_CameraManager.GetActiveCamera()->CalculateLookAtMatrix();
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
	return (m_pCamera != nullptr);
}

std::vector<Objects::BaseObject*> Scene::GetLightsFromScene() const
{
	std::vector<Objects::BaseObject*> lights;

	uint32_t size = static_cast<uint32_t>(m_pSceneObjects.size());
	for (uint32_t i{ 0 }; i < size; ++i)
	{
		Objects::BaseObject* pObject = m_pSceneObjects[i];
		if (typeid(*pObject->pMaterial) == typeid(Materials::DiffuseLight))
		{
			lights.push_back(pObject);
		}
	}

	return lights;
}


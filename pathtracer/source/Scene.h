// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include <vector>
#include "LightManager.h"
#include "CameraManager.h"

class Object;

namespace Objects
{
	struct BaseObject;
}

class Scene
{
public:
	Scene() = default;
	~Scene();

	Scene(const Scene&) = delete;
	Scene(Scene&&) = default;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) = default;

	//Adders
	void AddObject(Object* pObject);
	void AddObjectToScene(Objects::BaseObject* pObject);
	void AddLight(Light* pLight);
	void AddCamera(Camera* pCamera);

	void Update(const float elapsedSec);
	void HandleUserInput(const uint8_t* pKeyboardStates, const float elapsedSec);
	bool Hit(const Ray& ray, HitRecord& hitRecord, bool shadow = false);
	bool Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const;

	bool validCamera();
	const Elite::FPoint3& GetActiveCameraCoordinates() const;
	Elite::FPoint3 CalculateWorldCoordinates(uint32_t c, uint32_t r);

	void CalculateBiradiance(const Ray& ray, HitRecord& hitRecord);
	void InitialiseGroupLights();

	const std::vector<Objects::BaseObject*>& GetObjectsInScene() const { return m_pSceneObjects; }

private:
	std::vector<Object*> m_pObjects;
	LightManager m_LightManager;
	CameraManager m_CameraManager;

	std::vector<Objects::BaseObject*> m_pSceneObjects;
};


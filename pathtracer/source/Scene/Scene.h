// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021-2022
#pragma once
#include <vector>

struct Ray;
struct HitRecord;

class Camera;

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
	void AddObjectToScene(Objects::BaseObject* pObject);
	//void AddLight(Light* pLight);
	void AddCamera(Camera* pCamera);

	void Update(const float elapsedSec);
	bool Hit(HitRecord& record, const Ray& ray, float tmin, float tmax) const;

	bool validCamera();
	/*const Elite::FPoint3& GetActiveCameraCoordinates() const;
	Elite::FPoint3 CalculateWorldCoordinates(uint32_t c, uint32_t r);*/
	const Camera* GetCamera() const { return m_pCamera; }
	
	const std::vector<Objects::BaseObject*>& GetObjectsInScene() const { return m_pSceneObjects; }
	std::vector<Objects::BaseObject*> GetLightsFromScene() const;

private:
	//std::vector<Object*> m_pObjects;
	//LightManager m_LightManager;
	//CameraManager m_CameraManager;

	std::vector<Objects::BaseObject*> m_pSceneObjects;
	Camera* m_pCamera;
};


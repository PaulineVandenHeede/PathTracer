// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include <vector>
#include <unordered_set>
#include "Object.h"
#include "MaterialManager.h"
#include "Scene.h"

class LightManager;
class CameraManager;

//Singleton
class SceneGraph
{
public:
	static SceneGraph* GetInstance();

	//Destructor -> Rule of 5 -> Delete: singleton -> should only be one
	~SceneGraph() = default;

	SceneGraph(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&) = delete;
	SceneGraph(const SceneGraph&&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	//Adders
	unsigned int AddScene();
	void AddCameraToScene(unsigned int sceneID, Camera* pCamera);
	void AddObjectToScene(unsigned int sceneID, Object* pObject);
	void AddLightToScene(unsigned int sceneID, Light* pLight);

	bool HitActiveScene(const Ray& ray, HitRecord& hitRecord, bool shadow = false);
	void UpdateActiveScene(const float elapsedSec);

	bool validCameraActiveScene();
	const FPoint3& GetActiveCameraCoordinates() const;
	FPoint3 CalculateActiveCameraWorldCoordinates(uint32_t c, uint32_t r);

	void CalculateActiveSceneBiradiance(const Ray& ray, HitRecord& hitRecord);
	void InitialiseGroupLightsOfScene(unsigned int sceneID);
	void HandleUserInput(const float elapsedSec, bool& isLooping);

	void PrintKeyBindings() const;
	
	MaterialManager& GetMaterialManager();

private:
	//Default constructor
	SceneGraph();

	//Datamembers
	static SceneGraph* m_pSceneGraph;

	MaterialManager m_MaterialManager;
	std::unordered_map<unsigned int, Scene> m_Scenes;

	float m_Timer;
	float m_MaxTimer;

	unsigned int m_IDActiveScene;
	
};
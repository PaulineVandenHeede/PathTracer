// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021-2022
#pragma once
//Standard includes
#include <vector>
#include <unordered_map>

//Project includes
#include "Scene.h"

class Camera;

namespace Objects
{
	struct BaseObject;
}

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
	void AddObjectToScene(uint32_t sceneID, Objects::BaseObject* pObject);
	//void AddLightToScene(unsigned int sceneID, Light* pLight);
	
	void UpdateActiveScene(const float elapsedSec);

	bool validCameraActiveScene();
	
	const std::vector<Objects::BaseObject*>& GetObjectsActiveScene() const { return m_Scenes.at(m_IDActiveScene).GetObjectsInScene(); }
	const Scene& GetActiveScene() const { return m_Scenes.at(m_IDActiveScene); }

private:
	//Default constructor
	SceneGraph();

	//Datamembers
	static SceneGraph* m_pSceneGraph;

	//MaterialManager m_MaterialManager;
	std::unordered_map<unsigned int, Scene> m_Scenes;

	float m_Timer;
	float m_MaxTimer;

	unsigned int m_IDActiveScene;
	
};
// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021-2022
#include "pch.h"

//Project includes
#include "SceneGraph.h"
#include "Camera.h"
#include "Objects.h"

//Library includes
#include "SDL.h"

//Standard includes
#include <iostream>
#include <iomanip>

SceneGraph* SceneGraph::m_pSceneGraph{ nullptr };

SceneGraph* SceneGraph::GetInstance()
{
	if (!m_pSceneGraph)
	{
		m_pSceneGraph = new SceneGraph{  };
	}
	return m_pSceneGraph; //Now sure this isn't a nullptr
}


//Adders
unsigned int SceneGraph::AddScene()
{
	std::unordered_map<unsigned int, Scene>::const_iterator search{ m_Scenes.find(m_IDActiveScene + 1) };
	if ( search != m_Scenes.cend())
		return search->first;

	++m_IDActiveScene;
	m_Scenes[m_IDActiveScene]; //Calls the default constructor of scene
	return m_IDActiveScene;
}
void SceneGraph::AddCameraToScene(unsigned int sceneID, Camera* pCamera)
{
	std::unordered_map<unsigned int, Scene>::const_iterator found{ m_Scenes.find(sceneID) };
	if (found == m_Scenes.cend())
	{
		delete pCamera;
		pCamera = nullptr;
		return;
	}

	m_Scenes.at(sceneID).AddCamera(pCamera);

	/*try 
	{
		m_pScenes.at(sceneID)->AddCamera(pCamera);
	}
	catch(const std::exception& e)
	{
		delete pCamera;
		pCamera = nullptr;
		return;
	}*/
}
void SceneGraph::AddObjectToScene(uint32_t sceneID, Objects::BaseObject* pObject)
{
	std::unordered_map<unsigned int, Scene>::const_iterator found{ m_Scenes.find(sceneID) };
	if (found == m_Scenes.cend())
	{
		delete pObject;
		pObject = nullptr;
		return;
	}

	m_Scenes.at(sceneID).AddObjectToScene(pObject);
}
//void SceneGraph::AddLightToScene(unsigned int sceneID, Light* pLight)
//{
//	std::unordered_map<unsigned int, Scene>::const_iterator found{ m_Scenes.find(sceneID) };
//	if (found == m_Scenes.cend())
//	{
//		delete pLight;
//		pLight = nullptr;
//		return;
//	}
//
//	m_Scenes.at(sceneID).AddLight(pLight);
//}

void SceneGraph::UpdateActiveScene(const float elapsedSec)
{
	m_Scenes[m_IDActiveScene].Update(elapsedSec);
}

bool SceneGraph::validCameraActiveScene()
{
	return m_Scenes[m_IDActiveScene].validCamera();
}

//Private functions
SceneGraph::SceneGraph()
	: m_Timer{ 0.f }
	, m_MaxTimer{ 0.1f }
	, m_IDActiveScene{ 0 }
{
}
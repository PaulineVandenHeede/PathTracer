// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "SceneGraph.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "TriangleMesh.h"

#include "MaterialManager.h"

#include "LightManager.h"
#include "PointLight.h"
#include "DirectionalLight.h"

#include "CameraManager.h"
#include "Camera.h"

#include "Ray.h"
#include "Objects.h"

#include "SDL.h"
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
void SceneGraph::AddObjectToScene(unsigned int sceneID, Object* pObject)
{
	std::unordered_map<unsigned int, Scene>::const_iterator found{ m_Scenes.find(sceneID) };
	if (found == m_Scenes.cend())
	{
		delete pObject;
		pObject = nullptr;
		return;
	}

	m_Scenes.at(sceneID).AddObject(pObject);
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
void SceneGraph::AddLightToScene(unsigned int sceneID, Light* pLight)
{
	std::unordered_map<unsigned int, Scene>::const_iterator found{ m_Scenes.find(sceneID) };
	if (found == m_Scenes.cend())
	{
		delete pLight;
		pLight = nullptr;
		return;
	}

	m_Scenes.at(sceneID).AddLight(pLight);
}

bool SceneGraph::HitActiveScene(const Ray& ray, HitRecord& hitRecord, bool shadow)
{
	return m_Scenes[m_IDActiveScene].Hit(ray, hitRecord, shadow);
}
void SceneGraph::UpdateActiveScene(const float elapsedSec)
{
	m_Scenes[m_IDActiveScene].Update(elapsedSec);
}

bool SceneGraph::validCameraActiveScene()
{
	return m_Scenes[m_IDActiveScene].validCamera();
}

const FPoint3& SceneGraph::GetActiveCameraCoordinates() const
{
	return m_Scenes.at(m_IDActiveScene).GetActiveCameraCoordinates();
}

FPoint3 SceneGraph::CalculateActiveCameraWorldCoordinates(uint32_t c, uint32_t r)
{
	return m_Scenes.at(m_IDActiveScene).CalculateWorldCoordinates(c,r);
}

void SceneGraph::CalculateActiveSceneBiradiance(const Ray& ray, HitRecord& hitRecord)
{
	m_Scenes.at(m_IDActiveScene).CalculateBiradiance(ray, hitRecord);
}

void SceneGraph::InitialiseGroupLightsOfScene(unsigned int sceneID)
{
	std::unordered_map<unsigned int, Scene>::iterator search{ m_Scenes.find(m_IDActiveScene) };
	if (search == m_Scenes.end())
		return;

	search->second.InitialiseGroupLights();
}

void SceneGraph::HandleUserInput(const float elapsedSec, bool& isLooping)
{
	m_Timer += elapsedSec;
	const uint8_t* pKeyboardStates = SDL_GetKeyboardState(nullptr);

	if (pKeyboardStates[SDL_SCANCODE_S])
	{
		if (m_Timer > m_MaxTimer)
		{
			(m_IDActiveScene %= m_Scenes.size())++;
			// (++m_IDActiveScene %= m_pScenes.size())++; //++ at the end because else you will have the wrong ID
			if (!SceneGraph::GetInstance()->validCameraActiveScene())
				isLooping = false;

			m_Timer = 0.f;
		}
	}
	if (pKeyboardStates[SDL_SCANCODE_H])
	{
		if (m_Timer > m_MaxTimer)
		{
			PrintKeyBindings();
			m_Timer = 0.f;
		}
	}

	m_Scenes.at(m_IDActiveScene).HandleUserInput(pKeyboardStates, elapsedSec);
}

void SceneGraph::PrintKeyBindings() const
{
	std::cout << "--- Key Bindings --- \n";
	std::cout << "Print key bindings: H\n";
	std::cout << "Toggle between different scenes: S\n";
	std::cout << std::setw(3) << std::left << "" << "Toggle between different camera's in scene: C\n";
	std::cout << std::setw(6) << std::left << "" << "Move the camera according to the local x- and y-axis: LMB + RMB + drag\n";
	std::cout << std::setw(6) << std::left << "" << "Rotate the camera : RMB + drag\n";
	std::cout << std::setw(6) << std::left << "" << "Move the camera according to the word z-axis and rotate around the world y-axis: LMB + drag\n";
	std::cout << std::setw(3) << std::left << "" << "Toggle between Irradiance only, BRDF only and all combined. Lamberts Cosine Law is always used: T\n";
	std::cout << std::setw(3) << std::left << "" << "Enable/Disbale directional lights: J\n";
	std::cout << std::setw(3) << std::left << "" << "Enable/Disbale left point lights: K\n";
	std::cout << std::setw(3) << std::left << "" << "Enable/Disbale right point lights: L\n";
	std::cout << std::setw(3) << std::left << "" << "Enable/Disbale hard shadows: Z\n";
}

MaterialManager& SceneGraph::GetMaterialManager()
{
	return m_MaterialManager;
}

//Private functions
SceneGraph::SceneGraph()
	: m_MaterialManager{ }
	, m_Timer{ 0.f }
	, m_MaxTimer{ 0.1f }
	, m_IDActiveScene{ 0 }
{
	//--- Add first scene ---
	//unsigned int activeSceneID{ AddScene() };
	
	//Add Objects to first scene
	//AddObjectToScene(activeSceneID, new Plane{ Elite::FPoint3(0.f, -1.f, 0.f), Elite::FVector3(0.f, 1.f, 0.f), MaterialName::Lambert_LightGrey });
	//AddObjectToScene(activeSceneID, new Plane{ Elite::FPoint3(0.f, 0.f, -11.f), Elite::FVector3(0.f, 0.f, 1.f), MaterialName::Lambert_LightGrey });
	//AddObjectToScene(activeSceneID, new Plane{ Elite::FPoint3(-5.f, 0.f, 0.f), Elite::FVector3(1.f, 0.f, 0.f), MaterialName::Lambert_LightGrey });
	//AddObjectToScene(activeSceneID, new Plane{ Elite::FPoint3(5.f, 0.f, 0.f), Elite::FVector3(-1.f, 0.f, 0.f),  MaterialName::Lambert_LightGrey });
	//AddObjectToScene(activeSceneID, new TriangleMesh{ "Resources/lowpoly_bunny.obj" , MaterialName::LambertCookTorrance_metal_halfrough_copper });
	////Add Lights to first scene
	//AddLightToScene(activeSceneID, new PointLight{ Elite::FPoint3{ -1.f, 5.f, -4.f }, Elite::RGBColor{ 1.0f, 0.839f, 0.666f }, 25 });
	//AddLightToScene(activeSceneID, new PointLight{ Elite::FPoint3{ 1.f, 5.f, 4.f }, Elite::RGBColor{ 1.0f, 0.839f, 0.666f }, 25 });
	//AddLightToScene(activeSceneID, new DirectionalLight{ Elite::FVector3{ 0.f, -1.f, 0.f }, Elite::RGBColor{ 1.0f, 0.839f, 0.666f }, 0.5f });
	//InitialiseGroupLightsOfScene(activeSceneID);

	//--- Add second scene ---
	// activeSceneID = AddScene();
	//Add Objects to second scene
	//AddObjectToScene(activeSceneID, new Plane{ Elite::FPoint3(0.f, -1.f, 0.f), Elite::FVector3(0.f, 1.f, 0.f), MaterialName::Lambert_LightGrey });
	//AddObjectToScene(activeSceneID, new Plane{ Elite::FPoint3(0.f, 0.f, -11.f), Elite::FVector3(0.f, 0.f, 1.f), MaterialName::Lambert_LightGrey });
	//AddObjectToScene(activeSceneID, new Plane{ Elite::FPoint3(-5.f, 0.f, 0.f), Elite::FVector3(1.f, 0.f, 0.f), MaterialName::Lambert_LightGrey });
	//AddObjectToScene(activeSceneID, new Plane{ Elite::FPoint3(5.f, 0.f, 0.f), Elite::FVector3(-1.f, 0.f, 0.f), MaterialName::Lambert_LightGrey });

	///*AddObjectToScene(activeSceneID, new Triangle{ Elite::FPoint3(-0.75f, 1.5f, 0.f), Elite::FPoint3(-0.75f, 0.f, 0.f), Elite::FPoint3(0.75f, 0.f, 0.f), MaterialName::Lambert_Copper, Elite::FVector3(-2.5f, 5.f, 0.f), 4.f / 3.f, 0.f, false, CullMode::backFace });
	//AddObjectToScene(activeSceneID, new Triangle{ Elite::FPoint3(-0.75f, 1.5f, 0.f), Elite::FPoint3(-0.75f, 0.f, 0.f), Elite::FPoint3(0.75f, 0.f, 0.f), MaterialName::Lambert_Copper, Elite::FVector3(0.f, 5.f, 0.f), 4.f / 3.f, 0.f, false, CullMode::frontFace });
	//AddObjectToScene(activeSceneID, new Triangle{ Elite::FPoint3(-0.75f, 1.5f, 0.f), Elite::FPoint3(-0.75f, 0.f, 0.f), Elite::FPoint3(0.75f, 0.f, 0.f), MaterialName::Lambert_Copper, Elite::FVector3(2.5f, 5.f, 0.f), 4.f / 3.f });*/

	//AddObjectToScene(activeSceneID, new Sphere{ Elite::FPoint3(-2.5f, 3.5f, 0.f), MaterialName::LambertCookTorrance_dielectric_rough_silver, 1.f });
	//AddObjectToScene(activeSceneID, new Sphere{ Elite::FPoint3(0.f, 3.5f, 0.f), MaterialName::LambertCookTorrance_dielectric_halfrough_silver, 1.f });
	//AddObjectToScene(activeSceneID, new Sphere{ Elite::FPoint3(2.5f, 3.5f, 0.f), MaterialName::LambertCookTorrance_dielectric_smooth_silver, 1.f });

	//AddObjectToScene(activeSceneID, new Sphere{ Elite::FPoint3(-2.5f, 1.f, 0.f),MaterialName::LambertCookTorrance_metal_rough_silver, 1.f });
	//AddObjectToScene(activeSceneID, new Sphere{ Elite::FPoint3(0.f, 1.f, 0.f), MaterialName::LambertCookTorrance_metal_halfrough_silver, 1.f });
	//AddObjectToScene(activeSceneID, new Sphere{ Elite::FPoint3(2.5f, 1.f, 0.f), MaterialName::LambertCookTorrance_metal_smooth_silver, 1.f });
	////Add Lights to second scene

	//AddLightToScene(activeSceneID, new PointLight{ Elite::FPoint3{ -1.f, 3.f, -4.f }, Elite::RGBColor{ 1.0f, 0.839f, 0.666f }, 25 });
	//AddLightToScene(activeSceneID, new PointLight{ Elite::FPoint3{ 1.f, 3.f, 4.f }, Elite::RGBColor{ 1.0f, 0.839f, 0.666f }, 25 });
	//AddLightToScene(activeSceneID, new DirectionalLight{ Elite::FVector3{ 0.f, -1.f, 0.f }, Elite::RGBColor{ 1.0f, 0.839f, 0.666f }, 0.5f });
	//InitialiseGroupLightsOfScene(activeSceneID);

	//Origin points are in screen space
	//AddObjectToScene(activeSceneID, new Sphere(Elite::FPoint3(-1.f, 1.f, 0.f), MaterialName::LambertCookTorrance_dielectric_smooth_copper, 1.f));
	//AddObjectToScene(activeSceneID, new Sphere(FPoint3(1.f, 1.f, 0.f), MaterialName::LambertCookTorrance_dielectric_halfrough_copper, 1.f));

	//AddObjectToScene(activeSceneID, new Plane(FPoint3(0.f, 0.f, 0.f), FVector3(0.f, 1.f, 0.0f), MaterialName::Lambert_LightGrey));
	//AddObjectToScene(activeSceneID, new Plane(FPoint3(0.f, 0.f, -6.f), FVector3(0.f, 0.f, 1.0f), MaterialName::Lambert_LightGrey));

	///*AddPointLight(FPoint3{ 0, 5, -5 }, RGBColor{ 1, 1, 1 }, 25);
	//AddPointLight(FPoint3{ 0, 2.5f, 5 }, RGBColor{ 1, 1, 1 }, 25);
	//AddDirectionalLight(FVector3{ 0, -1, 1 }, RGBColor{ 1, 1, 1 }, 1);*/

	//AddLightToScene(activeSceneID, new PointLight{ Elite::FPoint3{ 0.f, 10.f, -5.f }, Elite::RGBColor{ 1.0f, 1.0f, 1.0f }, 25 });
	//AddLightToScene(activeSceneID, new PointLight{ Elite::FPoint3{ 0.f, 2.5f, 5.f }, Elite::RGBColor{ 1.0f, 1.0f, 1.0f }, 25 });
	//AddLightToScene(activeSceneID, new DirectionalLight{ Elite::FVector3{ 0.f, -1.f, 1.f }, Elite::RGBColor{ 1.0f, 1.0f, 1.0f }, 0.5f });
	//InitialiseGroupLightsOfScene(activeSceneID);
}
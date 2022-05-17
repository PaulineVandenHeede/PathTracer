//Modified by: 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021-2022
#include "pch.h"
//External includes
#include "vld.h"
#include "SDL.h"
#undef main

//Standard includes
#include <iostream>

//Project includes
#include "SceneGraph.h"

#include "ETimer.h"
#include "ERenderer.h"

#include "Camera.h"
#include "Objects.h"


void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

void PrintKeyBindings()
{
	}

int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;

	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 600;
	const uint32_t height = 300;
	SDL_Window* pWindow = SDL_CreateWindow(
		"PathTracer - Pauline Vanden Heede",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize "framework"
	Elite::Timer* pTimer = new Elite::Timer();
	Elite::Renderer* pRenderer = new Elite::Renderer(pWindow);


	//Create Scene
	SceneGraph* pSceneGraph = SceneGraph::GetInstance();
	const uint32_t sceneID = pSceneGraph->AddScene();
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 0.f, 10.f, -1.f }, 5, new Materials::Lambertian{ Elite::RGBColor{ 0.8f, 0.3f, 0.3f} }});
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 0.f, -100.5f, -1.f }, 100, new Materials::Lambertian{ Elite::RGBColor{ 0.8f, 0.8f, 0.f } }});
	pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 1.f, 0.f, -1.f }, 0.5f, new Materials::Lambertian{ Elite::RGBColor{ 0.8f, 0.6f, 0.2f } } });
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ -1.f, 0.f, -1.f }, 0.5f, new Materials::Lambertian{ Elite::RGBColor{ 0.8f, 0.8f, 0.8f } } });

	//Ground Plane
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Plane{ Elite::FPoint3{ 0.f, 0.f, 0.f }, Elite::FVector3{ 0.f, 1.f, 0.f }, new Materials::Lambertian{ Elite::RGBColor{ 1.f, 1.f, 1.f} } });
	//Left Plane
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Plane{ Elite::FPoint3{ 50.f, 0.f, 0.f }, Elite::FVector3{ 1.f, 0.f, 0.f }, new Materials::Lambertian{ Elite::RGBColor{ 0.8f, 0.f, 0.f} } });
	//Right Plane
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Plane{ Elite::FPoint3{ -50.f, 0.f, 0.f }, Elite::FVector3{ -1.f, 0.f, 0.f }, new Materials::Lambertian{ Elite::RGBColor{ 0.f, 0.f, 0.8f} } });
	//Top Plane
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Plane{ Elite::FPoint3{ 0.f, 50.f, 0.f }, Elite::FVector3{ 0.f, -1.f, 0.f }, new Materials::Lambertian{ Elite::RGBColor{ 1.f, 1.f, 1.f } } });
	//Back Plane
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Plane{ Elite::FPoint3{ 0.f, 0.f, 50.f }, Elite::FVector3{ 0.f, 0.f, -1.f }, new Materials::Lambertian{ Elite::RGBColor{ 1.f, 1.f, 1.f } } });
	//Front Plane
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Plane{ Elite::FPoint3{ 0.f, 0.f, -50.f }, Elite::FVector3{ 0.f, 0.f, 1.f }, new Materials::Lambertian{ Elite::RGBColor{ 0.3f, 0.3f, 0.3f} } });

	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ Elite::FPoint3{ 0.f, 0.f, -2.f },
			{ FPoint3{ -2.f, -2.f, -2.f }, FPoint3{ -2.f, 2.f, -2.f }, FPoint3{ 2.f, 2.f, -2.f }, FPoint3{ 2.f, -2.f, -2.f } },
			new Materials::DiffuseLight{ Elite::RGBColor{ 4.f, 4.f, 4.f }  }, Elite::FVector3{ 0.f, 0.f, -1.f } });

	//Create Camera
	//pSceneGraph->AddCameraToScene(sceneID, new Camera{ {0.f, 25.f, -40.f}, {0.f, 25.f, -1.f}, {0.f, 1.f, 0.f},
	//	40, float(width) / float(height) });
	pSceneGraph->AddCameraToScene(sceneID, new Camera{ {-2.f, 2.f, 1.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f},
		90, float(width) / float(height) });

	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	bool takeScreenshot = false;

	if (!SceneGraph::GetInstance()->validCameraActiveScene())
		isLooping = false;

	while (isLooping)
	{
		//--------- Get input events ---------
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isLooping = false;
				break;
			case SDL_KEYUP:
				if(e.key.keysym.scancode == SDL_SCANCODE_X)
					takeScreenshot = true;
				break;
			}
		}
		//--------- Handle user inputs -------
		//SceneGraph::GetInstance()->HandleUserInput(pTimer->GetElapsed(), isLooping);
		//if (!isLooping)
		//	continue;
		//--------- Update scene -------
		//SceneGraph::GetInstance()->UpdateActiveScene(pTimer->GetElapsed());

		//--------- Render ---------
		pRenderer->Render();

		//--------- Timer ---------
		pTimer->Update();
		printTimer += pTimer->GetElapsed();
		if (printTimer >= 1.f)
		{
			printTimer = 0.f;
			std::cout << "FPS: " << pTimer->GetFPS() << std::endl;
		}
		isLooping = false;
		takeScreenshot = true;

		//Save screenshot after full render
		if (takeScreenshot)
		{
			if (!pRenderer->SaveBackbufferToImage())
				std::cout << "Screenshot saved!" << std::endl;
			else
				std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
			takeScreenshot = false;
		}
	}
	pTimer->Stop();

	//Shutdown "framework"
	delete pRenderer;
	delete pTimer;

	ShutDown(pWindow);
	return 0;
}

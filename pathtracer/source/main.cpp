//Altered by: 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
//External includes
#include "vld.h"
#include "SDL.h"
#include "SDL_surface.h"
#undef main

//Standard includes
#include <iostream>

//Project includes
#include "SceneGraph.h"

#include "CameraManager.h"
#include "Camera.h"

#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "TriangleMesh.h"

#include "PointLight.h"
#include "DirectionalLight.h"

#include "ETimer.h"
#include "ERenderer.h"

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
	//--------- Initialise camera's ---------
	//Add Cameras to first scene
	//SceneGraph::GetInstance()->AddCameraToScene(1, new Camera{ Elite::FPoint3{ 0.f, 1.f, 5.f }, Elite::FVector3{ 0.f, 0.f, 1.f }, 45.f, width, height });
	//SceneGraph::GetInstance()->AddCameraToScene(1, new Camera{ Elite::FPoint3{ 0.f, 5.f, 0.f }, Elite::FVector3{ 0.f, 1.f, 0.f }, 45.f, width, height });
	//SceneGraph::GetInstance()->AddCameraToScene(1, new Camera{ Elite::FPoint3{ 0.f, 3.f, 10.f }, Elite::FVector3{ 0.f, 0.f, 1.f }, 45.f,width, height });
	////Add Cameras to second scene
	//SceneGraph::GetInstance()->AddCameraToScene(2, new Camera{ Elite::FPoint3{ 0.f, 3.f, -10.f }, Elite::FVector3{ 0.f, 0.f, -1.f }, 45.f, width, height });
	//SceneGraph::GetInstance()->AddCameraToScene(2, new Camera{ Elite::FPoint3{ 0.f, 10.f, 0.f }, Elite::FVector3{ 0.f, 1.f, 0.f }, 45.f, width, height });
	//SceneGraph::GetInstance()->AddCameraToScene(2, new Camera{ Elite::FPoint3{ 0.f, 20.f, 20.f }, Elite::FVector3{ 0.f, 1.f, 1.f }, 45.f, width, height });
	//SceneGraph::GetInstance()->AddCameraToScene(2, new Camera{ Elite::FPoint3{ 0.f, 3.f, 10.f }, Elite::FVector3{ 0.f, 0.f, 1.f }, 45.f, width, height });
	//--------- Print Key bindings ---------
	//SceneGraph::GetInstance()->PrintKeyBindings();

	//Create Scene
	SceneGraph* pSceneGraph = SceneGraph::GetInstance();
	uint32_t sceneID = pSceneGraph->AddScene();
	pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 0.f, 0.f, -1.f }, 0.5f });
	pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 0.f, -100.5f, -1.f }, 100.f });
	pSceneGraph->AddCameraToScene(sceneID, new Camera{});

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

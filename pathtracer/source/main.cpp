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

	const uint32_t width = 500;
	const uint32_t height = 500;
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
	pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 278.f, 278, 278.f }, 100.f, new Materials::Lambertian{ Elite::RGBColor{ 0.8f, 0.6f, 0.2f } } });
	//pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ -1.f, 0.f, -1.f }, 0.5f, new Materials::Lambertian{ Elite::RGBColor{ 0.8f, 0.8f, 0.8f } } });

	//LeftPlane
	FPoint3 leftFrontDown = { 555.f, 0.f, 0.f };
	FPoint3 leftFrontUp = { 555.f, 555.f, 0.f };
	FPoint3 leftBackDown = { 555.f, 0.f, 555.f };
	FPoint3 leftBackUp = { 555.f, 555.f, 555.f };

	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ leftFrontDown, { leftFrontDown, leftBackDown, leftBackUp, leftFrontUp },
			new Materials::Lambertian{ Elite::RGBColor{ 0.12f, 0.45f, 0.15f }}, FVector3{ -1.f, 0.f, 0.f }});

	float area = AreaOfRectangle({ leftFrontDown, leftBackDown, leftBackUp, leftFrontUp });
	std::cout << area << std::endl;

	//RightPlane
	leftFrontDown.x = 0.f;
	leftFrontUp.x = 0.f;
	leftBackDown.x = 0.f;
	leftBackUp.x = 0.f;
	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ leftFrontDown, { leftFrontDown, leftFrontUp, leftBackUp, leftBackDown },
			new Materials::Lambertian{ Elite::RGBColor{ 0.65f, 0.05f, 0.05f }}, FVector3{ 1.f, 0.f, 0.f } });

	area = AreaOfRectangle({ leftFrontDown, leftFrontUp, leftBackUp, leftBackDown });
	std::cout << area << std::endl;

	//BackPlane
	FPoint3 leftDown{ 555.f, 0.f, 555.f };
	FPoint3 leftUp{ 555.f, 555.f, 555.f };
	FPoint3 rightDown{ 0.f, 0.f, 555.f };
	FPoint3 rightUp{ 0.f, 555.f, 555.f };
	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ leftDown, { leftDown, rightDown, rightUp, leftUp },
			new Materials::Lambertian{ Elite::RGBColor{ 0.73f, 0.73f, 0.73f }}, FVector3{ 0.f, 0.f, -1.f } });

	area = AreaOfRectangle({ leftDown, rightDown, rightUp, leftUp});
	std::cout << area << std::endl;

	//UpPlane
	FPoint3 leftBack{ 555.f, 555.f, 555.f };
	FPoint3 rightBack{ 0.f, 555.f, 555.f };
	FPoint3 leftFront{ 555.f, 555.f, 0.f };
	FPoint3 rightFront{ 0.f, 555.f, 0.f };

	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ leftFront, { rightFront, leftFront, leftBack, rightBack },
			new Materials::Lambertian{ Elite::RGBColor{ 0.73f, 0.73f, 0.73f }}, FVector3{ 0.f, -1.f, 0.f } });

	area = AreaOfRectangle({ rightFront, leftFront, leftBack, rightBack });
	std::cout << area << std::endl;

	//DownPlane
	leftBack.y = 0.f;
	rightBack.y = 0.f;
	leftFront.y = 0.f;
	rightFront.y = 0.f;

	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ leftDown, { leftBack, leftFront, rightFront, rightBack },
			new Materials::Lambertian{ Elite::RGBColor{ 0.73f, 0.73f, 0.73f }}, FVector3{ 0.f, 1.f, 0.f } });

	area = AreaOfRectangle({ leftBack, leftFront, rightFront, rightBack });
	std::cout << area << std::endl;

	//Light
	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ Elite::FPoint3{ 213.f, 554.f, 227.f  },
			{ FPoint3{ 213.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 332.f }, FPoint3{ 213.f, 554.f, 332.f } },
			new Materials::DiffuseLight{ Elite::RGBColor{ 15.f, 15.f, 15.f }  }, Elite::FVector3{ 0.f, -1.f, 0.f } });

	area = AreaOfRectangle({ FPoint3{ 213.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 332.f }, FPoint3{ 213.f, 554.f, 332.f } });
	std::cout << area << std::endl;

	//random points in rectangle
	/*std::array<FPoint3, 4> rect = { FPoint3{ 213.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 332.f }, FPoint3{ 213.f, 554.f, 332.f } };
	for(int i{ 0 }; i < 20; ++i)
	{
		FPoint3 point = RandomPointInRectangle(rect);
		std::cout << "Point " << i << ": (" << point.x << ", " << point.y << ", " << point.z << ")\n";
	}*/


	//sphere in cornell box


	//Create Camera
	FPoint3 position{ 278.f, 278.f, -800.f };
	FVector3 lookAt{ 278.f, 278.f, 0.f };

	pSceneGraph->AddCameraToScene(sceneID, new Camera{ position, lookAt, {0.f, 1.f, 0.f}, 40, float(width) / float(height), 0.f, 10.f});
	//pSceneGraph->AddCameraToScene(sceneID, new Camera{ {-2.f, 2.f, 1.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f},
	//	90, float(width) / float(height) });

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

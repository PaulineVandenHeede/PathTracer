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

#include "BenchmarkInterface.h"
#include <functional>


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

	//Create Scene
	SceneGraph* pSceneGraph = SceneGraph::GetInstance();
	const uint32_t sceneID = pSceneGraph->AddScene();

#pragma region Spheres
	pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 200.f, 278.f, 150.f }, 150.f, new Materials::Lambertian{ Elite::RGBColor{ 1.f, 0.7f, 0.1f } } });
	pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 400.f, 100.f, 200.f }, 100.f, new Materials::Lambertian{ Elite::RGBColor{ 0.8f, 0.8f, 0.8f } } });
	pSceneGraph->AddObjectToScene(sceneID, new Objects::Sphere{ Elite::FPoint3{ 325.f, 50.f, 50.f }, 50.f, new Materials::Lambertian{ Elite::RGBColor{ 0.f, 1.f, 1.f } } });
#pragma endregion !Spheres

#pragma region Planes
	//LeftPlane
	FPoint3 leftFrontDown = { 555.f, 0.f, 0.f };
	FPoint3 leftFrontUp = { 555.f, 555.f, 0.f };
	FPoint3 leftBackDown = { 555.f, 0.f, 555.f };
	FPoint3 leftBackUp = { 555.f, 555.f, 555.f };

	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ { leftFrontDown, leftBackDown, leftBackUp, leftFrontUp },
			new Materials::Lambertian{ Elite::RGBColor{ 0.12f, 0.45f, 0.15f } } });

	/*float area = AreaOfRectangle({ leftFrontDown, leftBackDown, leftBackUp, leftFrontUp });
	std::cout << area << std::endl;*/

	//RightPlane
	leftFrontDown.x = 0.f;
	leftFrontUp.x = 0.f;
	leftBackDown.x = 0.f;
	leftBackUp.x = 0.f;
	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ { leftFrontDown, leftFrontUp, leftBackUp, leftBackDown },
			new Materials::Lambertian{ Elite::RGBColor{ 0.65f, 0.05f, 0.05f }} });

	/*area = AreaOfRectangle({ leftFrontDown, leftFrontUp, leftBackUp, leftBackDown });
	std::cout << area << std::endl;*/

	//BackPlane
	FPoint3 leftDown{ 555.f, 0.f, 555.f };
	FPoint3 leftUp{ 555.f, 555.f, 555.f };
	FPoint3 rightDown{ 0.f, 0.f, 555.f };
	FPoint3 rightUp{ 0.f, 555.f, 555.f };
	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ { leftDown, rightDown, rightUp, leftUp },
			new Materials::Lambertian{ Elite::RGBColor{ 0.73f, 0.73f, 0.73f }} });

	/*area = AreaOfRectangle({ leftDown, rightDown, rightUp, leftUp});
	std::cout << area << std::endl;*/

	//UpPlane
	FPoint3 leftBack{ 555.f, 555.f, 555.f };
	FPoint3 rightBack{ 0.f, 555.f, 555.f };
	FPoint3 leftFront{ 555.f, 555.f, 0.f };
	FPoint3 rightFront{ 0.f, 555.f, 0.f };

	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ { rightFront, leftFront, leftBack, rightBack },
			new Materials::Lambertian{ Elite::RGBColor{ 0.73f, 0.73f, 0.73f }} });

	/*area = AreaOfRectangle({ rightFront, leftFront, leftBack, rightBack });
	std::cout << area << std::endl;*/

	//DownPlane
	leftBack.y = 0.f;
	rightBack.y = 0.f;
	leftFront.y = 0.f;
	rightFront.y = 0.f;

	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ { leftBack, leftFront, rightFront, rightBack },
			new Materials::Lambertian{ Elite::RGBColor{ 0.73f, 0.73f, 0.73f } } });

	/*area = AreaOfRectangle({ leftBack, leftFront, rightFront, rightBack });
	std::cout << area << std::endl;*/
#pragma endregion !Planes

#pragma region Lights
	//Light
	pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{{ FPoint3{ 213.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 332.f }, FPoint3{ 213.f, 554.f, 332.f } },
			new Materials::DiffuseLight{ Elite::RGBColor{ 15.f, 15.f, 15.f }  } });
	/*pSceneGraph->AddObjectToScene(sceneID,
		new Objects::Rectangle{ { FPoint3{ 343.f, 1.f, 332.f }, FPoint3{ 343.f, 1.f, 227.f }, FPoint3{ 213.f, 1.f, 227.f }, FPoint3{ 213.f, 1.f, 332.f } },
			new Materials::DiffuseLight{ Elite::RGBColor{ 15.f, 15.f, 15.f }  } });*/
#pragma endregion !Lights

	//Create Camera
	FPoint3 position{ 278.f, 278.f, -800.f };
	FVector3 lookAt{ 278.f, 278.f, 0.f };

	pSceneGraph->AddCameraToScene(sceneID, new Camera{ position, lookAt, {0.f, 1.f, 0.f}, 40, float(width) / float(height), 0.f, 10.f});

	//Initialize "framework"
	Elite::Renderer* const pRenderer = new Elite::Renderer(pWindow);

	//Start loop
	if (!SceneGraph::GetInstance()->validCameraActiveScene())
		return 0;

#ifdef BENCHMARKING
	BenchmarkInterface benchmarker{ 10, pRenderer };

	std::function<void()> render = std::bind(&Renderer::Render, pRenderer);
	benchmarker.TimeFunction(render);

	std::string name{ "BENCHMARK_" + std::to_string(pRenderer->GetNrOfSamples()) + "SPP_" + std::to_string(pRenderer->GetDepth()) + "D_" };
#ifdef NORMAL_SAMPLING
	name += "NORMAL";
#endif
#ifdef LIGHT_ONLY_SAMPLING
	name += "IMPORTANCE";
#endif
#ifdef IMPORTANCE_SAMPLING
	name += "COMBINATION";
#endif

#ifdef STRATIFIED_SAMPLING
	name += "_STRATIFIED";
#endif

	name += ".csv";

	benchmarker.OutputResults<std::chrono::seconds>(name, "Render Times", false);
#endif

#ifdef RENDER
	pRenderer->Render();
	if (!pRenderer->SaveBackbufferToImage())
		std::cout << "Screenshot saved!" << std::endl;
#endif

	//Shutdown "framework"
	delete pRenderer;

	ShutDown(pWindow);
	return 0;
}

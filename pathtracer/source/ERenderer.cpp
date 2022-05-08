//Altered by: 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
//External includes
#include "SDL.h"
#include "SDL_surface.h"
#include "SDL_image.h"

//Project includes
#include "ERenderer.h"
#include "SceneGraph.h"
#include "CameraManager.h"
#include "Plane.h"
#include "Sphere.h"
#include "Camera.h"
#include "MaterialManager.h"
#include "MaterialLambert.h"

#include "Objects.h"
#include "Scene.h"

Elite::Renderer::Renderer(SDL_Window * pWindow)
	: m_pWindow{ pWindow }
	, m_pFrontBuffer{ SDL_GetWindowSurface(pWindow) }
	, m_pBackBuffer{}
	, m_pBackBufferPixels{}
	, m_Width{}
	, m_Height{}
	, m_NrSamples{ 100 }
	, m_RandomGenerator{ (std::random_device())()}
{
	//Initialize
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
}

Elite::Renderer::~Renderer()
{
	delete SceneGraph::GetInstance();
}

void Elite::Renderer::Render()
{
	SDL_LockSurface(m_pBackBuffer);

	//HitRecord hitRecord{};
	//The ray starts from the camera position --> Perspective view
	//Ray ray{ SceneGraph::GetInstance()->GetActiveCameraCoordinates(), FVector3{0,0,-1} };

	//Loop over all the pixels
	//camera settings -> for now
	/*FVector3 lowerLeftCorner{ -2.0f, -1.0f, -1.0f };
	FVector3 horizontal{ 4.f, 0.f, 0.f };
	FVector3 vertical{ 0.f, 2.f, 0.f };
	FPoint3 origin{ 0.f, 0.f, 0.f };*/

	const Scene& scene = SceneGraph::GetInstance()->GetActiveScene();
	const Camera* pCamera = scene.GetCamera();

	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			Elite::RGBColor colour{  };

			for (uint32_t s = 0; s < m_NrSamples; ++s)
			{
				float u = float(c + std::generate_canonical<float, 10>(m_RandomGenerator)) / float(m_Width);
				float v = float(m_Height - r + std::generate_canonical<float,10>(m_RandomGenerator)) / float(m_Height);
				
				Ray ray = pCamera->GetRay(u, v);
				//Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
				//Normalize(ray.direction);
				//HitRecord record;
				colour += Colour(ray, scene, 0);
			}

			colour.r /= float(m_NrSamples);
			colour.g /= float(m_NrSamples);
			colour.b /= float(m_NrSamples);
			colour = Elite::RGBColor(sqrtf(colour.r), sqrtf(colour.g), sqrtf(colour.b));
			/*if ( t > 0.0f)
			{
				FVector3 normal = FVector3(ray.PointAtParameter(t)) - FVector3(0.f, 0.f, -1.f);
				Normalize(normal);
			}*/


			//Fill the pixels - pixel access demo

			//FVector3 colour{ float(c) / float(m_Width), float(m_Height - r) / float(m_Height) , 0.2f };

			//float rColour = float(c) / float(m_Width);
			//float gColour = ; //0,0 is Top Left not Bottom Left
			//float bColour = 0.2f;

			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<Uint8>(255.99f * colour.r),
				static_cast<Uint8>(255.99f * colour.g),
				static_cast<Uint8>(255.99f * colour.b));
		}
	}

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	IMG_SaveJPG(m_pBackBuffer, "BackbufferRender.jpg", 100);
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

Elite::RGBColor Elite::Renderer::Colour(const Ray& ray, const Scene& scene, int depth)
{
	HitRecord record{};
	if (scene.Hit(record, ray, 0.01f, FLT_MAX))
	{
		Ray scattered{};
		Elite::RGBColor attenuation{};
		if(depth < 50 && record.pMaterial->Scatter(ray, record, attenuation, scattered))
		{
			return attenuation * Colour(scattered, scene, depth + 1);
		}
		else
		{
			return Elite::RGBColor{0.f, 0.f, 0.f};
		}
		//Elite::FVector3 target = static_cast<Elite::FVector3>(record.hitPoint) + record.normal + static_cast<Elite::FVector3>(Elite::RandomPointInUnitSphere());
		//return Colour(Ray(record.hitPoint, target - static_cast<Elite::FVector3>(record.hitPoint)), scene) * 0.5f;
	}
	else
	{
		//BACKGROUND
		Elite::FVector3 direction = GetNormalized(ray.direction);
		float t = 0.5f * direction.y + 1.f;
		Elite::FVector3 colour = (1.f - t) * m_BackgroundColourOne + t * m_BackgroundColourTwo;
		return Elite::RGBColor{ colour.x, colour.y, colour.z };
	}
}



//Altered by: 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
//External includes
#include "SDL.h"
#include "SDL_surface.h"

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
	FVector3 lowerLeftCorner{ -2.0f, -1.0f, -1.0f };
	FVector3 horizontal{ 4.f, 0.f, 0.f };
	FVector3 vertical{ 0.f, 2.f, 0.f };
	FPoint3 origin{ 0.f, 0.f, 0.f };

	FVector3 white{ 1.f, 1.f, 1.f };
	FVector3 lightBlue{ 0.5f, 0.7f, 1.f };

	HitRecord record{};

	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			float u = float(c) / float(m_Width);
			float v = float(m_Height - r) / float(m_Height);

			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
			Normalize(ray.direction);

			FVector3 colour{  };

			const Scene& scene = SceneGraph::GetInstance()->GetActiveScene();
			
			HitRecord record;
			/*if ( t > 0.0f)
			{
				FVector3 normal = FVector3(ray.PointAtParameter(t)) - FVector3(0.f, 0.f, -1.f);
				Normalize(normal);
			}*/
			if (scene.Hit(record, ray, 0.01f, FLT_MAX))
			{
				colour = FVector3(record.normal.x + 1, record.normal.y + 1, record.normal.z + 1) * 0.5f;
			}
			else
			{
				float t = 0.5f * ray.direction.y + 1.f;
				colour = (1.f - t) * white + t * lightBlue;
			}


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
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}



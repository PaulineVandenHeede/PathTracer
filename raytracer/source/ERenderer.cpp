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

	HitRecord hitRecord{};
	//The ray starts from the camera position --> Perspective view
	Ray ray{ SceneGraph::GetInstance()->GetActiveCameraCoordinates(), FVector3{0,0,-1} };

	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			FVector3 lookDirection{ SceneGraph::GetInstance()->CalculateActiveCameraWorldCoordinates(c, r) - ray.origin };
			Normalize(lookDirection);
			ray.direction = lookDirection;

			//Only if an object is hit we are going to calculate the rendering equation for that point
			if (SceneGraph::GetInstance()->HitActiveScene(ray, hitRecord))
			{ 
				SceneGraph::GetInstance()->CalculateActiveSceneBiradiance(ray, hitRecord);
				m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				 	static_cast<uint8_t>(hitRecord.renderColour.r * 255),
				 	static_cast<uint8_t>(hitRecord.renderColour.g * 255),
				 	static_cast<uint8_t>(hitRecord.renderColour.b * 255));
			}
			else //If there's no hit set the pixel to black --> this is needed for when there's a camera movement
			{
				m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
					0, 0, 0);
			}
			hitRecord.tValue = FLT_MAX;
			hitRecord.renderColour = { 0.f, 0.f, 0.f };

			//Fill the pixels - pixel access demo
			/*float cw = (255.0f / m_Width) * c;
			float ch = (255.0f / m_Height) * r;
			uint8_t uColor = static_cast<uint8_t>((cw + ch) / 2.0f);
			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(uColor),
				static_cast<uint8_t>(uColor),
				static_cast<uint8_t>(uColor));*/
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



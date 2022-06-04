//Modified by: 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021-2022
#include "pch.h"

//Library includes
#include "SDL.h"
#include "SDL_surface.h"
#include "SDL_image.h"

//Project includes
#include "ERenderer.h"
#include "SceneGraph.h"
#include "Camera.h"
#include "Scene.h"
#include "HitRecord.h"
#include "Ray.h"
#include "PDFs.h"

//#define NORMAL_SAMPLING
//#define LIGHT_ONLY_SAMPLING
#define IMPORTANCE_SAMPLING

Elite::Renderer::Renderer(SDL_Window * pWindow)
	: m_pWindow{ pWindow }
	, m_pFrontBuffer{ SDL_GetWindowSurface(pWindow) }
	, m_pBackBuffer{}
	, m_pBackBufferPixels{}
	, m_Width{}
	, m_Height{}
	, m_NrSamples{ 100 } //default: 100
	, m_Depth{ 50 } //default: 50
	, m_RandomGenerator{ (std::random_device())()}
{
	//Initialize
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
	pRect = new Objects::Rectangle{ Elite::FPoint3{ 213.f, 554.f, 227.f  },
			{ FPoint3{ 213.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 227.f }, FPoint3{ 343.f, 554.f, 332.f }, FPoint3{ 213.f, 554.f, 332.f } },
			new Materials::DiffuseLight{ Elite::RGBColor{ 15.f, 15.f, 15.f }  }, Elite::FVector3{ 0.f, -1.f, 0.f }, CullMode::backCulling };;
}

Elite::Renderer::~Renderer()
{
	delete pRect;
	delete SceneGraph::GetInstance();
}

void Elite::Renderer::Render()
{
	SDL_LockSurface(m_pBackBuffer);
	

	const Scene& scene = SceneGraph::GetInstance()->GetActiveScene();
	const Camera* pCamera = scene.GetCamera();

	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			Elite::RGBColor colour{  };

			for (uint32_t s = 0; s < m_NrSamples; ++s)
			{
				float u = float(c + std::generate_canonical<float, 10>(m_RandomGenerator)) / float(m_Width);
				float v = float(m_Height - r + std::generate_canonical<float,10>(m_RandomGenerator)) / float(m_Height);
				
				Ray ray = pCamera->GetRayFocus(u, v);
				colour += Colour(ray, scene, 0);
			}

			//averaging colour sample
			colour.r /= float(m_NrSamples);
			colour.g /= float(m_NrSamples);
			colour.b /= float(m_NrSamples);
			//gamma correction
			colour = Elite::RGBColor(sqrtf(colour.r), sqrtf(colour.g), sqrtf(colour.b));

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
	if (scene.Hit(record, ray, 0.001f, FLT_MAX))
	{
		Ray scattered{};
		Elite::RGBColor attenuation{};
		Elite::RGBColor emitted = record.pMaterial->Emit(ray, record);
		float pdfValue{ 0 };
		if(depth < m_Depth && record.pMaterial->Scatter(ray, record, attenuation, scattered, pdfValue))
		{

#ifdef NORMAL_SAMPLING
			pdf::CosineDensity pdf{ record.normal };
			scattered = Ray(record.hitPoint, pdf.Generate());
			pdfValue = pdf.Value(scattered.direction);
#endif

#ifdef LIGHT_ONLY_SAMPLING
			pdf::LightDensity pdf{ pRect, record.hitPoint };
			scattered = Ray(record.hitPoint, pdf.Generate());
			pdfValue = pdf.Value(scattered.direction);
#endif

#ifdef IMPORTANCE_SAMPLING
			pdf::LightDensity pdfLight{ pRect, record.hitPoint };
			pdf::CosineDensity pdfCosine{ record.normal };

			if (RandomFloatCanonical() < 0.5f)
				scattered = Ray(record.hitPoint, pdfLight.Generate());
			else
				scattered = Ray(record.hitPoint, pdfCosine.Generate());
	
			pdfValue = 0.5f * pdfLight.Value(scattered.direction) + 0.5f * pdfCosine.Value(scattered.direction);
#endif


			Elite::RGBColor colour = emitted + attenuation * record.pMaterial->ScatterPDF(ray, record, scattered) * Colour(scattered, scene, depth + 1) / pdfValue;
			colour.MaxToOne();
			return colour;
		}
		else
		{
			return emitted;
		}
	}
	else
	{
		//BACKGROUND
		/*Elite::FVector3 direction = GetNormalized(ray.direction);
		float t = 0.5f * direction.y + 1.f;
		Elite::FVector3 colour = (1.f - t) * m_BackgroundColourOne + t * m_BackgroundColourTwo;
		return Elite::RGBColor{ colour.x, colour.y, colour.z };*/
		return Elite::RGBColor{ 0.1f, 0.1f, 0.1f };
	}
}



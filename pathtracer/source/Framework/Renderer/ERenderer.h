/*=============================================================================*/
// Copyright 2017-2019 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
// ERenderer.h: class that holds the surface to render to, does traverse the pixels 
// and traces the rays using a tracer
/*=============================================================================*/
#ifndef ELITE_RAYTRACING_RENDERER
#define	ELITE_RAYTRACING_RENDERER

#include <cstdint>
#include <random>

#include "Objects.h"

struct SDL_Window;
struct SDL_Surface;

class SceneGraph;
class Camera;
class Scene;
struct Ray;

namespace Elite
{
	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Render();
		bool SaveBackbufferToImage() const;

	private:
		SDL_Window* m_pWindow;
		SDL_Surface* m_pFrontBuffer;
		SDL_Surface* m_pBackBuffer;
		uint32_t* m_pBackBufferPixels;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_NrSamples;
		uint32_t m_Depth;

		Elite::FVector3 m_BackgroundColourOne{ 1.f, 1.f, 1.f };
		Elite::FVector3 m_BackgroundColourTwo{ 0.5f, 0.7f, 1.f };

		//random samples
		std::mt19937 m_RandomGenerator;
		Objects::Rectangle* pRect;

		Elite::RGBColor Colour(const Ray& ray, const Scene& scene, int depth);
	};
}

#endif
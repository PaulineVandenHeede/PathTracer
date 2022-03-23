// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "LightManager.h"
#include "SceneGraph.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "Camera.h"
#include "SDL.h"
#include <typeinfo>

LightManager::LightManager()
	: m_DisplayHardShadows{ true }
	, m_Timer{ 0.f }
	, m_MaxTimer{ 0.1f }
	, m_CalculateMode{ CalculateMode::AllCombined }
{
}

LightManager::~LightManager()
{
	for (size_t i{}; i < m_pLights.size(); ++i)
	{
		delete m_pLights[i];
		m_pLights[i] = nullptr;
	}
	m_pLights.clear();
}

void LightManager::AddLight(Light* pLight)
{
	m_pLights.push_back(pLight);
}

void LightManager::InitialiseGroup()
{
	for (Light* pLight : m_pLights)
	{
		pLight->DetermineGroup();
	}
}


//NormalSurface: opposite of direction ray 
void LightManager::CalculateBiradianceOfLights(const Ray& ray, HitRecord& hitRecord)
{
	if (this == nullptr)
		return;

	Elite::RGBColor finalColorPixel{ };
	FVector3 directionToLight{ };
	float dot{ };
	float lengthRay{ };
	Ray rayHitpointToLight{ hitRecord.hitPoint, directionToLight, 0.01f, lengthRay};
	HitRecord hitRecordShadow{};
	for (Light* pLight : m_pLights)
	{
		if (!pLight->IsEnabled())
			continue;

		//Get the direction of the light + the magnitude
		directionToLight = -pLight->GetDirection(hitRecord.hitPoint);
		lengthRay = Normalize(directionToLight); //Returns the magnitude of the not normalised vector

		if (m_DisplayHardShadows)
		{
			//For the direction --> has to be normalized --> we need length of the ray for our tmax
			//Normalize = divide by the length of the vector
			rayHitpointToLight.direction = directionToLight;
			rayHitpointToLight.tMax = lengthRay;

			//If it the ray that goes out of the hitPoint to the light hits an object than that point is in the shade
			if (SceneGraph::GetInstance()->HitActiveScene(rayHitpointToLight, hitRecordShadow, true))
				continue;
			//If this is true then skip this light -> this is how we create a fading shadow 
			//-> because an other light can have an influence on the same pixel
		}
		
		//We want to take the angle, that we look at the object, into account
		//We have to take the negative because we get inverted colours
		dot = -pLight->LambertsCosineLaw(hitRecord.normal, hitRecord.hitPoint);
		if (dot < 0.f) //Because the point on the surface points away from the light
			continue;

		//If the material is nullptr there is no a collision with an object
		// if (hitRecord.materialName == nullptr)
		//  	continue;

		//We combine the Biradiance of the light, with the colour of the material of the object, with the angle we look at the object
		//Biradiance = outgoing light of the lightSource that falls on the hitpoint
		switch (m_CalculateMode)
		{
		case CalculateMode::AllCombined:
			finalColorPixel += pLight->GetBiradiance(hitRecord.hitPoint) * SceneGraph::GetInstance()->GetMaterialManager().GetMaterial(hitRecord.materialName)->Shade(hitRecord, directionToLight, -ray.direction) * dot;
			break;
		case CalculateMode::BRDFOnly:
			finalColorPixel += SceneGraph::GetInstance()->GetMaterialManager().GetMaterial(hitRecord.materialName)->Shade(hitRecord, directionToLight, -ray.direction) * dot;
			break;
		case CalculateMode::IrradianceOnly:
			finalColorPixel += pLight->GetBiradiance(hitRecord.hitPoint) * dot;
			break;
		}
	}

	hitRecord.renderColour = finalColorPixel;
	//So we don't get an overflow on our colour: 1.5f --> 255 * 1.5 = 382.5 --> which gets translated to 127.5
	//When an overflow occurs it just start counting from 0 again for the colour.
	hitRecord.renderColour.MaxToOne();
}

void LightManager::HandleUserInput(const uint8_t* pKeyboardStates, const float elapsedSec)
{
	if (this == nullptr)
		return;

	m_Timer += elapsedSec;

	if (pKeyboardStates[SDL_SCANCODE_J])
	{
		if (m_Timer > m_MaxTimer)
		{
			for (Light* pLight : m_pLights)
			{
				//Enable/disable all directional lights
				if (pLight->GetGroup() == Light::Group::directional)
					pLight->ChangeEnable();
			}
			m_Timer = 0.f;
		}
	}
	else if (pKeyboardStates[SDL_SCANCODE_K])
	{
		if (m_Timer > m_MaxTimer)
		{
			for (Light* pLight : m_pLights)
			{
				//Enable/disable all left pointlights
				if (pLight->GetGroup() == Light::Group::left)
					pLight->ChangeEnable();
			}
			m_Timer = 0.f;
		}
	}
	else if (pKeyboardStates[SDL_SCANCODE_L])
	{
		if (m_Timer > m_MaxTimer)
		{
			for (Light* pLight : m_pLights)
			{
				//Enable/disable all right pointlights
				if (pLight->GetGroup() == Light::Group::right)
					pLight->ChangeEnable();
			}
			m_Timer = 0.f;
		}
	}
	else if (pKeyboardStates[SDL_SCANCODE_Z])
	{
		//Enable/disable hard shadows
		if (m_Timer > m_MaxTimer)
		{
			m_DisplayHardShadows = !m_DisplayHardShadows;
			m_Timer = 0.f;
		}
		
	}
	else if (pKeyboardStates[SDL_SCANCODE_T])
	{
		if (m_Timer > m_MaxTimer)
		{
			int mode = int(m_CalculateMode);
			m_CalculateMode = CalculateMode(++ mode % int(CalculateMode::end));
			m_Timer = 0.f;
		}
	}

}

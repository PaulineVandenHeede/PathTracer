// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Light.h"
#include "HitRecord.h"
#include "Ray.h"
#include <vector>

class LightManager
{
public:
	LightManager();
	~LightManager();

	void AddLight(Light* pLight);
	void InitialiseGroup();
	void CalculateBiradianceOfLights(const Ray& ray, HitRecord& hitRecord);
	void HandleUserInput(const uint8_t* pKeyboardStates, const float elapsedSec);

private:
	enum class CalculateMode
	{
		AllCombined = 0,
		IrradianceOnly = 1,
		BRDFOnly = 2,
		end = 3
	};

	//Datamembers
	std::vector<Light*> m_pLights;
	bool m_DisplayHardShadows;
	float m_Timer;
	const float m_MaxTimer;
	CalculateMode m_CalculateMode;
};


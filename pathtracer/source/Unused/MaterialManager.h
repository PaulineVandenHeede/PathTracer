// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include <unordered_map>

class Material;

enum class MaterialName
{
	Default,
	Lambert_LightBlue,
	Lambert_LightPink,
	Lambert_DarkPurple,
	Lambert_LightGrey,
	Lambert_Copper,
	LambertPhong_LightGreen ,
	LambertCookTorrance_dielectric_rough_silver,
	LambertCookTorrance_dielectric_halfrough_silver,
	LambertCookTorrance_dielectric_smooth_silver,
	LambertCookTorrance_metal_rough_silver,
	LambertCookTorrance_metal_halfrough_silver,
	LambertCookTorrance_metal_smooth_silver,
	LambertCookTorrance_dielectric_rough_gold,
	LambertCookTorrance_dielectric_halfrough_gold,
	LambertCookTorrance_dielectric_smooth_gold,
	LambertCookTorrance_metal_rough_gold,
	LambertCookTorrance_metal_halfrough_gold,
	LambertCookTorrance_metal_smooth_gold,
	LambertCookTorrance_dielectric_rough_copper,
	LambertCookTorrance_dielectric_halfrough_copper,
	LambertCookTorrance_dielectric_smooth_copper,
	LambertCookTorrance_metal_rough_copper,
	LambertCookTorrance_metal_halfrough_copper,
	LambertCookTorrance_metal_smooth_copper,
};


class MaterialManager
{
public:
	
	MaterialManager();
	~MaterialManager();

	//Rule of 5 -> we only want one materialmanager
	MaterialManager(const MaterialManager& mm) = delete;
	MaterialManager& operator=(MaterialManager& mm) = delete;
	MaterialManager(const MaterialManager&& mm) = delete;
	MaterialManager& operator=(MaterialManager&& mm) = delete;

	Material* GetMaterial(const MaterialName name);

private:
	//Datamembers
	std::unordered_map<MaterialName, Material*> m_pMaterials;

	//Helper funcitons
	void AddMaterial(const MaterialName name, Material* pMaterial);
};


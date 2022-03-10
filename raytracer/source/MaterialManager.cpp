// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "MaterialManager.h"
#include "MaterialLambert.h"
#include "Material_LambertPhong.h"
#include "Material_LambertCookTorrance.h"
#include <iostream>

using materialMapIt = std::unordered_map<std::string, Material*>::iterator;

MaterialManager::MaterialManager()
{
	//Default colour, for when someone gives a name that's not in the map yet
	AddMaterial(MaterialName::Default, new MaterialLambert{ Elite::RGBColor{1.f, 0.f, 1.f}, 1.f });

	//Week 1-3
	AddMaterial(MaterialName::Lambert_LightBlue, new MaterialLambert{ Elite::RGBColor{ 0.36f, 0.533f, 0.854f }, 1.f });
	AddMaterial(MaterialName::Lambert_Copper, new MaterialLambert{ Elite::RGBColor{ 0.955f, 0.638f, 0.538f }, 1.f });
	AddMaterial(MaterialName::Lambert_LightPink, new MaterialLambert{ Elite::RGBColor{ 0.674f, 0.309f, 0.776f }, 1.f });
	AddMaterial(MaterialName::Lambert_DarkPurple, new MaterialLambert{ Elite::RGBColor{ 0.294f, 0.f, 0.509f }, 1.f });
	AddMaterial(MaterialName::Lambert_LightGrey, new MaterialLambert{ Elite::RGBColor{ 0.95f, 0.95f, 0.95f }, 1.f });
	AddMaterial(MaterialName::LambertPhong_LightGreen, new Material_LambertPhong{ 1.f, Elite::RGBColor{ 0.69f, 0.68f, 0.25f }, 1.0f, 60 });

	//Week 4
	/*Colours:
	Titanium - Elite::RGBColor{ 0.542f, 0.497f, 0.449f }
	Chromium - Elite::RGBColor{ 0.549f, 0.556f, 0.554f }
	Iron - Elite::RGBColor{ 0.562f, 0.565f, 0.578f }
	Nickel - Elite::RGBColor{ 0.660f, 0.609f, 0.526f }
	Platinum - Elite::RGBColor{ 0.673f, 0.637f, 0.585f }
	Copper - Elite::RGBColor{ 0.955f, 0.638f, 0.538f }
	Palladium - Elite::RGBColor{ 0.733f, 0.697f, 0.652f }
	Mercury - Elite::RGBColor{ 0.781f, 0.780f, 0.778f }
	Brass(C260) - Elite::RGBColor{ 0.910f, 0.778f, 0.423f }
	Zinc - Elite::RGBColor{ 0.664f, 0.824f, 0.850f }
	Gold - Elite::RGBColor{ 1.000f, 0.782f, 0.344f }
	Aluminum - Elite::RGBColor{ 0.913f, 0.922f, 0.924f }
	Silver - Elite::RGBColor{ 0.972f, 0.960f, 0.915f }
	*/
	AddMaterial(MaterialName::LambertCookTorrance_dielectric_rough_copper, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.955f, 0.638f, 0.538f }, 1.0f, false });
	AddMaterial(MaterialName::LambertCookTorrance_dielectric_halfrough_copper, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.955f, 0.638f, 0.538f }, 0.6f, false });
	AddMaterial(MaterialName::LambertCookTorrance_dielectric_smooth_copper, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.955f, 0.638f, 0.538f }, 0.1f, false });
	AddMaterial(MaterialName::LambertCookTorrance_metal_rough_copper, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.955f, 0.638f, 0.538f }, 1.0f, true });
	AddMaterial(MaterialName::LambertCookTorrance_metal_halfrough_copper, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.955f, 0.638f, 0.538f }, 0.6f, true });
	AddMaterial(MaterialName::LambertCookTorrance_metal_smooth_copper, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.955f, 0.638f, 0.538f }, 0.1f, true });

	AddMaterial(MaterialName::LambertCookTorrance_dielectric_rough_silver, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.972f, 0.960f, 0.915f }, 1.0f, false });
	AddMaterial(MaterialName::LambertCookTorrance_dielectric_halfrough_silver, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.972f, 0.960f, 0.915f }, 0.6f, false });
	AddMaterial(MaterialName::LambertCookTorrance_dielectric_smooth_silver, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.972f, 0.960f, 0.915f }, 0.1f, false });
	AddMaterial(MaterialName::LambertCookTorrance_metal_rough_silver, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.972f, 0.960f, 0.915f }, 1.0f, true });
	AddMaterial(MaterialName::LambertCookTorrance_metal_halfrough_silver, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.972f, 0.960f, 0.915f }, 0.6f, true });
	AddMaterial(MaterialName::LambertCookTorrance_metal_smooth_silver, new Material_LambertCookTorrance{ Elite::RGBColor{ 0.972f, 0.960f, 0.915f }, 0.1f, true });

}

MaterialManager::~MaterialManager()
{
	for (std::pair<MaterialName, Material*> materialPair : m_pMaterials)
	{
		delete materialPair.second;
	}
	m_pMaterials.clear();
}

void MaterialManager::AddMaterial(const MaterialName name, Material* pMaterial)
{
	if (m_pMaterials.find(name) == m_pMaterials.cend())
	{
		m_pMaterials[name] = pMaterial;
	}
}

Material* MaterialManager::GetMaterial(const MaterialName name)
{
	if (m_pMaterials.find(name) == m_pMaterials.cend())
	{
		std::cerr << "Couldn't find the material, default is used!\n";
		return m_pMaterials[MaterialName::Default];
	}

	//We're sure this material exists in the map so this won't create a new pair in the map
	return m_pMaterials[name];
}

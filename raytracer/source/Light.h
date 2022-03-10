// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "EMath.h"
#include "ERGBColor.h"

class Light
{
public:
	enum class Group
	{
		none,
		directional,
		left,
		right
	};

	Light(const Elite::RGBColor& colour, const float intensity, const Group group);

	Group GetGroup() const;
	void DetermineGroup();

	bool IsEnabled() const;
	void ChangeEnable();

	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& hitPoint) const = 0;
	virtual Elite::RGBColor GetBiradiance(const Elite::FPoint3& hitPoint) const = 0;
	virtual float LambertsCosineLaw(const Elite::FVector3& hitPointNormal, const Elite::FPoint3& hitPointPoint) const = 0;
protected:
	//Datamembers - base class
	Elite::RGBColor m_Colour;
	float m_Intesity;
private:
	//Datamembers - only for base class
	Group m_Group;
	bool m_Enabled;

	//Helper functions
	virtual Group ReturnGroup() = 0;
};


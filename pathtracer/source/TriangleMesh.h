// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#pragma once
#include "Object.h"
#include "Hit.h"
#include <vector>
#include <string>
#include <Regex>

class Triangle;

struct Index3
{
	unsigned int v0, v1, v2;
};

class TriangleMesh final : public Object
{
public:
	TriangleMesh(const std::string& fileName, const MaterialName materialName, const Elite::FVector3& translation = Elite::FVector3::ZeroVector(), const float scale = 1.f, const CullMode cullMode = CullMode::noCulling);
	virtual ~TriangleMesh();

	virtual void Update(const float elapsedSec) override;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord, bool shadow) const override;

private:
	//Datamembers - derived class
	std::vector<Triangle*> m_pTriangles;

	Elite::FVector3 m_Translation;
	float m_Scale;
	CullMode m_CullMode;

	//Helper functions
	void ParseFile(const std::string& fileName);
	void ParseComment(const std::string& line, const std::regex& vertexCount, const std::regex& faceCount, std::vector<Elite::FPoint3>& vertexBuffer, std::vector<Index3>& indexBuffer);
	void ParseVertice(const std::string& line, const std::regex& vertexLine, std::vector<Elite::FPoint3>& vertexBuffer);
	void ParseFace(const std::string& line, const std::regex& faceLine, std::vector<Index3>& indexBuffer);
};


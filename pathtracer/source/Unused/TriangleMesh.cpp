// 2DAE07 - Vanden Heede, Pauline - Schoolyear 2019-2020
#include "pch.h"
#include "TriangleMesh.h"
#include "Triangle.h"
#include "SceneGraph.h"
#include <fstream>
#include <sstream>

TriangleMesh::TriangleMesh(const std::string& fileName, const MaterialName materialName, const Elite::FVector3& translation, const float scale, const CullMode cullMode)
	: Object{ Elite::FPoint3(0.f, 0.f, 0.f) , materialName }
	, m_Translation{ translation }
	, m_Scale{ scale }
	, m_CullMode{ cullMode }
{
	ParseFile(fileName);
}

TriangleMesh::~TriangleMesh()
{
	for (Triangle* pTriangle : m_pTriangles)
	{
		delete pTriangle;
		pTriangle = nullptr;
	}
	m_pTriangles.clear();
}

void TriangleMesh::Update(const float elapsedSec)
{
}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitRecord, bool shadow) const
{
	bool hit{ false };
	for(Triangle* pTriangle: m_pTriangles)
	{
		if (pTriangle->Hit(ray, hitRecord, shadow))
		{
			hit = true;
		}
	}
	return hit;
}

void TriangleMesh::ParseFile(const std::string& fileName)
{
	std::vector<Elite::FPoint3> vertexBuffer;
	std::vector<Index3> indexBuffer;

	std::ifstream objFile{};
	objFile.open(fileName, std::ios::in | std::ios::ate);

	//Load the whole file
	size_t size = size_t(objFile.tellg()); //Get the position of the latest character
	std::string stringFile(size, '\0'); //Initialise stirng with the same number of characters as in the file
	objFile.seekg(0); //Get the position of the first character again
	objFile.read(&stringFile[0], size); //Read from the file
	objFile.close(); //Close the file again

	// std::regex vertexCount("# vertex count = (\\d+)");
	// std::regex faceCount("# face count = (\\d+)");
	std::regex vertexCount("#\\s*(\\d+)\\s*vertices\\s*");
	std::regex faceCount("#\\s*(\\d+)\\s*faces");
	// std::regex vertexLine("v\\s+(-?\\d+\\.\\d+e-?\\d{3})\\s+(-?\\d+\\.\\d+e-?\\d{3})\\s+(-?\\d+.\\d+e-?\\d{3})");
	std::regex vertexLine("v\\s*(-?\\d+\\.\\d+)\\s(-?\\d+\\.\\d+)\\s(-?\\d+\\.\\d+)");
	std::regex faceLine("f\\s*(\\d+)\\s*(\\d+)\\s*(\\d+)");

	std::string line{};

	size_t begin{};
	size_t end{};
	while (begin != std::string::npos)
	{
		begin = stringFile.find_first_of("#fv", begin);
		if (begin != std::string::npos)
		{
			end = stringFile.find('\n', begin);
			line = stringFile.substr(begin, (end - begin));

			switch (line[0])
			{
			case '#':
				ParseComment(line, vertexCount, faceCount, vertexBuffer, indexBuffer);
				break;
			case 'v':
				ParseVertice(line, vertexLine, vertexBuffer);
				break;
			case 'f':
				ParseFace(line, faceLine, indexBuffer);
				break;
			}
			begin = end;
		}
	}
	
	for (size_t i{}; i < indexBuffer.size(); ++i)
	{
		m_pTriangles.push_back(new Triangle{ vertexBuffer[indexBuffer[i].v0], vertexBuffer[indexBuffer[i].v1], vertexBuffer[indexBuffer[i].v2], m_MaterialName, m_Translation, m_Scale, 0.f, true, m_CullMode });
	}
}

void TriangleMesh::ParseComment(const std::string& line, const std::regex& vertexCount, const std::regex& faceCount, std::vector<Elite::FPoint3>& vertexBuffer, std::vector<Index3>& indexBuffer)
{
	std::smatch matches{};
	if (std::regex_search(line, matches, vertexCount))
	{
		vertexBuffer.reserve(std::stoul(matches[1]));
	}
	else if (std::regex_search(line, matches, faceCount))
	{
		indexBuffer.reserve(std::stoul(matches[1]));
	}
}

void TriangleMesh::ParseVertice(const std::string& line, const std::regex& vertexLine, std::vector<Elite::FPoint3>& vertexBuffer)
{
	std::smatch matches{};
	if (std::regex_search(line, matches, vertexLine))
	{
		vertexBuffer.push_back(Elite::FPoint3{ std::stof(matches[1]), std::stof(matches[2]), std::stof(matches[3]) });
	}
}

void TriangleMesh::ParseFace(const std::string& line, const std::regex& faceLine, std::vector<Index3>& indexBuffer)
{
	std::smatch matches{};
	if (std::regex_search(line, matches, faceLine))
	{
		indexBuffer.push_back({ std::stoul(matches[1]) - 1, std::stoul(matches[2]) - 1, std::stoul(matches[3]) - 1 });
	}
}

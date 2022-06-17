#pragma once
#include <chrono>
#include <map>
#include <initializer_list>
#include <ostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "ERenderer.h"

using VectorIterator = std::vector<std::chrono::duration<double>>::iterator;
using VectorConstIterator = std::vector<std::chrono::duration<double>>::const_iterator;

class BenchmarkInterface
{
public:
	BenchmarkInterface(uint8_t nrOfTests, Elite::Renderer* const pRenderer);

	template<typename F>
	void TimeFunction(F functionPointer);

	template<typename U>
	void OutputResults(const std::string& filename, const std::string& testName, bool append = true);

private:
	std::vector<std::chrono::duration<double>> m_Timings;
	Elite::Renderer* m_pRenderer;
	uint8_t m_NrOfTests;


	template<typename U>
	std::string TimeTypeToString();
};

BenchmarkInterface::BenchmarkInterface(uint8_t nrOfTests, Elite::Renderer* const pRenderer)
	: m_NrOfTests{ nrOfTests }
	, m_pRenderer{ pRenderer }
	, m_Timings{  }
{
}

template<typename U>
inline void BenchmarkInterface::OutputResults(const std::string& fileName, const std::string& testName, bool append)
{
	using MapIterator = std::multimap<uint32_t, std::chrono::duration<float>>::iterator;

	if (m_Timings.empty())
		return;

	std::ofstream output{ };
	append ? output.open(fileName, std::ios::out | std::ios::app) : output.open(fileName, std::ios::out | std::ios::trunc);

	if (!output.is_open())
	{
		std::cerr << "Something went wrong while opening the file with fileName: " + fileName + "!\n";
		return;
	}

	output << testName + ",Time (" + TimeTypeToString<U>() + "),,,,,,,,,,Average\n";
	output << ",Timing 0,Timing 1, Timing 2, Timing 3, Timing 4, Timing 5, Timing 6, Timing 7, Timing 8, Timing 9\n";

	std::string line{};
	
	std::pair<VectorConstIterator, VectorConstIterator> minmax = std::minmax_element(m_Timings.cbegin(), m_Timings.cbegin());
	m_Timings.erase(minmax.first);
	m_Timings.erase(minmax.second);

	double totalTime = 0;
	for (auto it{ m_Timings.cbegin() }; it != m_Timings.cend(); ++it)
	{
		line += "," + std::to_string(std::chrono::duration_cast<U>(*it).count());
		totalTime += std::chrono::duration_cast<U>(*it).count();
	}
	line += ',' + std::to_string(totalTime / m_NrOfTests) + '\n';
	output << line;

	output.close();
	std::cout << "Values written to file " << fileName << std::endl;
}

template<>
inline std::string BenchmarkInterface::TimeTypeToString<std::chrono::hours>()
{
	return std::move("hours");
}
template<>
inline std::string BenchmarkInterface::TimeTypeToString<std::chrono::minutes>()
{
	return std::move("minutes");
}
template<>
inline std::string BenchmarkInterface::TimeTypeToString<std::chrono::seconds>()
{
	return std::move("seconds");
}
template<>
inline std::string BenchmarkInterface::TimeTypeToString<std::chrono::milliseconds>()
{
	return std::move("milliseconds");
}

template<>
inline std::string BenchmarkInterface::TimeTypeToString<std::chrono::microseconds>()
{
	return std::move("microseconds");
}
template<>
inline std::string BenchmarkInterface::TimeTypeToString<std::chrono::nanoseconds>()
{
	return std::move("nanoseconds");
}

//template<typename F>
//inline void BenchmarkInterface::TimeFunction(F functionPointer, std::initializer_list<std::string> rowNames)
//{
//	m_Timings.clear();
//	for (uint8_t t{ 0 }; t < m_NrOfTests; ++t)
//	{
//		functionPointer(m_Timings, rowNames);
//	}
//}

template<typename F>
inline void BenchmarkInterface::TimeFunction(F functionPointer)
{
	m_Timings.clear();
	uint8_t totalTests = m_NrOfTests + 2;
	for (uint8_t t{ 0 }; t < totalTests; ++t)
	{
		auto start = std::chrono::high_resolution_clock::now();
		functionPointer();
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> timing{ end - start };
		m_Timings.push_back(timing);
		std::cout << "Timing " << std::to_string(std::chrono::duration_cast<std::chrono::seconds>(timing).count()) << std::endl;
		std::cout << "Iteration " << std::to_string(t) << " of " << std::to_string(totalTests) << " done." << std::endl;

		std::string name{ std::to_string(t) + "_" + std::to_string(m_pRenderer->GetNrOfSamples()) + "SPP_" + std::to_string(m_pRenderer->GetDepth()) + "D_"};
#ifdef NORMAL_SAMPLING
		name += "NORMAL";
#endif
#ifdef LIGHT_ONLY_SAMPLING
		name += "IMPORTANCE";
#endif
#ifdef COMBINATION_SAMPLING
		name += "COMBINATION";
#endif

#ifdef IMPORTANCE_SAMPLING
		name += "_STRATIFIED";
#endif // DEBUG


		if (!m_pRenderer->SaveBackbufferToImage(name))
			std::cout << "Screenshot saved!" << std::endl;
		else
			std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
	}
}

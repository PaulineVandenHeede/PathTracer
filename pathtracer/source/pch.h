//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#pragma once
#include "EMath.h"
#include "ERGBColor.h"

//#define NORMAL_SAMPLING
#define IMPORTANCE_SAMPLING
//#define COMBINATION_SAMPLING
//#define STRATIFIED_SAMPLING
#define NON_STRATIFIED_SAMPLING

//#define BENCHMARKING
#define RENDER

#define SafeDelete(pObject)\
	if(pObject != nullptr)\
	{\
		delete pObject;\
		pObject = nullptr;\
	}
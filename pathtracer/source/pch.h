//Modified by: 3DAE03 - Vanden Heede, Pauline - Schoolyear 2021/2022
#pragma once
#include "EMath.h"
#include "ERGBColor.h"

#define SafeDelete(pObject)\
	if(pObject != nullptr)\
	{\
		delete pObject;\
		pObject = nullptr;\
	}
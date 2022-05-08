#pragma once
#include "EMath.h"
#include "ERGBColor.h"

#define SafeDelete(pObject)\
	if(pObject != nullptr)\
	{\
		delete pObject;\
		pObject = nullptr;\
	}
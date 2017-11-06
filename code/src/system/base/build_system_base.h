#pragma once

#ifdef BUILD_SYSTEM_BASE
	#define SYSTEM_BASE_API __declspec(dllexport)   
#else  
	#define SYSTEM_BASE_API __declspec(dllimport)   
#endif  
